/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_light_per_pixel.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 15:42:20 by mpauw             #+#    #+#             */
/*   Updated: 2018/06/25 19:35:29 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** Make sure color values don't exceed 1.
*/

static void		check_values(t_intensity *in, t_3v o, t_source l, t_p_info *pi)
{
	if (in->spec > 1)
		in->spec = 1;
	if (((o.v)[0] * pi->beer.v[0]) > 1 || ((o.v)[1] * pi->beer.v[1]) > 1
			|| ((o.v)[2] * pi->beer.v[2]) > 1
			|| ((o.v)[0] * pi->beer.v[0]) < 0 || ((o.v)[1] * pi->beer.v[1]) < 0
			|| ((o.v)[2] * pi->beer.v[2]) < 0 || ((l.tmp_color).v)[0] > 1
			|| ((l.tmp_color).v)[1] > 1 || ((l.tmp_color).v)[2] > 1
			|| ((l.tmp_color).v)[0] < 0 || ((l.tmp_color).v)[1] < 0
			|| ((l.tmp_color).v)[2] < 0)
		error(4);
}

/*
** Based on transparency/specular reflection, determine how much influence this
** object has on the color of this pixel.
*/

static double	get_influence(t_pixel *p, int i)
{
	double	influence;

	influence = 1 - (((p->pi_arr[i])->vis_obj)->m).transparent;
	if ((p->pi_arr[i])->type == 2)
	{
		while (i > 0)
		{
			if ((p->pi_arr[i - 1])->type % 2 == 0)
			{
				influence *= ((((p->pi_arr[i - 1])->vis_obj)->m).transparent
					* p->pi_arr[i - 1]->fresnal_transparent);
			}
			i--;
		}
	}
	else if ((p->pi_arr[i])->type == 1)
	{
		while (i > 0)
		{
			if ((p->pi_arr[i - 1])->type < 2)
				influence *= get_influence_specular(p, i);
			i--;
		}
	}
	return (influence);
}

/*
** Change the value for this specific light based on intensity, influence,
** color, etc..
*/

static double	set_light_value(t_intensity in, t_pixel *p,
		t_source l, int i)
{
	t_3v		*c;
	t_3v		o;
	t_p_info	*pi;
	double		influence;

	pi = p->pi_arr[i];
	o = (pi->obj_m).color;
	c = &(p->c_per_src[l.id]);
	influence = get_influence(p, i);
	if ((pi->vis_obj)->type % 5 && ft_3v_dot_product(pi->dir, pi->normal) > 0)
		influence *= (pi->obj_m).transparent;
	in.diff = in.diff * (l.intensity).diff;
	in.spec = in.spec * (l.intensity).spec;
	check_values(&in, o, l, pi);
	in.diff *= (influence * (1 - in.spec));
	in.spec *= influence;
	(c->v)[0] += in.diff * ((l.tmp_color).v)[0] * ((o.v)[0] * pi->beer.v[0]);
	(c->v)[1] += in.diff * ((l.tmp_color).v)[1] * ((o.v)[1] * pi->beer.v[1]);
	(c->v)[2] += in.diff * ((l.tmp_color).v)[2] * ((o.v)[2] * pi->beer.v[2]);
	(c->v)[0] += in.spec * ((l.tmp_color).v)[0];
	(c->v)[1] += in.spec * ((l.tmp_color).v)[1];
	(c->v)[2] += in.spec * ((l.tmp_color).v)[2];
	return ((c->v)[0] + (c->v)[1] + (c->v)[2]);
}

/*
** For all objects involved in this pixel, update the light value at this pixel
** for this specific source.
*/

static void		light_intensity(t_source src, t_pixel *p, t_scene *scene,
		t_event *e)
{
	t_3v			dir;
	t_intensity		in;
	int				r;
	t_p_info		*pi;

	r = 0;
	while (r < p->amount_p)
	{
		pi = p->pi_arr[r];
		src.tmp_color = src.color;
		if (!(pi->vis_obj))
			break ;
		dir = ft_3v_subtract(pi->point, src.origin);
		pi->dir = dir;
		in.diff = 0;
		in.spec = 0;
		if (light_reaches(dir, scene, &src) > 0.01)
			in = get_intensity(pi, dir, *(scene->cam), src.id - 1);
		(e->src)->max_intensity = ((e->src)->max_intensity > in.diff) ?
			(e->src)->max_intensity : in.diff;
		set_light_value(in, p, src, r);
		r++;
	}
}

/*
** For this specific source, loop through all the pixels to see what its
** influence is.
*/

void			*set_light_per_pixel(void *event)
{
	t_pixel		*p;
	t_event		*e;
	int			i;
	int			j;

	e = (t_event *)event;
	i = ((e->scene.height * e->scene.max_anti_a / THREADS) *
			e->scene.thread_id);
	while (i < (e->scene.height * e->scene.max_anti_a / THREADS)
			* (e->scene.thread_id + 1))
	{
		j = 0;
		while (j < e->scene.width * e->scene.max_anti_a)
		{
			p = &(((e->scene.cam)->p_array)[j + i * e->scene.width
					* e->scene.max_anti_a]);
			p->c_per_src[e->src->id] = ft_zero_3v();
			light_intensity(*e->src, p, &(e->scene), e);
			j += e->scene.step_size;
		}
		i += e->scene.step_size;
	}
	return (NULL);
}
