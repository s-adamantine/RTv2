/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_light_per_pixel.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 15:42:20 by mpauw             #+#    #+#             */
/*   Updated: 2018/05/09 15:41:09 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
 * Get type of material light reaches, based on pattern. If transparent: deal
 * with it.
 */

static void		get_light_color(t_object *obj, t_3v point, t_source *src)
{
	t_material	m;

	if ((obj->pattern).type == 0)
	{
		(src->tmp_color).v[0] *= (obj->m).transparent * ((obj->m).color).v[0];
		(src->tmp_color).v[1] *= (obj->m).transparent * ((obj->m).color).v[1];
		(src->tmp_color).v[2] *= (obj->m).transparent * ((obj->m).color).v[2];
		return ;
	}	
	m = get_object_material(*obj, point);
	(src->tmp_color).v[0] *= m.transparent * (m.color).v[0];
	(src->tmp_color).v[1] *= m.transparent * (m.color).v[1];
	(src->tmp_color).v[2] *= m.transparent * (m.color).v[2];
}

/*
 * Does the light reach the visible object (after passing through transparent
 * objects or not).
 */

static double	light_reaches(t_3v dir, t_list *objects, int cam,
		t_source *src)
{
	double		t_value;
	double		reached;
	t_list		*o_lst;
	t_object	*obj;

	o_lst = objects;
	reached = 0;
	while (o_lst && o_lst->content)
	{
		obj = (t_object *)o_lst->content;
		t_value = obj->f(obj->fixed_s[cam][src->id - 1], dir, 0);
		if (t_value > 0.001 && t_value < 0.99999)
			get_light_color(obj, get_point(src->origin, dir, t_value), src);
		else if (t_value > 0.999999 && t_value < 1.000001)
			reached = 1;
		o_lst = o_lst->next;
	}
	return (reached);
}

/*
 * Make sure color values don't exceed 1.
 */

static void		check_values(t_intensity *in, t_3v o, t_source l)
{
	if (in->diff > 1)
		in->diff = 1;
	if (in->spec > 1)
		in->spec = 1;
	if ((o.v)[0] > 1 || (o.v)[1] > 1 || (o.v)[2] > 1
			|| (o.v)[0] < 0 || (o.v)[1] < 0
			|| (o.v)[2] < 0 || ((l.tmp_color).v)[0] > 1
			|| ((l.tmp_color).v)[1] > 1 || ((l.tmp_color).v)[2] > 1
			|| ((l.tmp_color).v)[0] < 0 || ((l.tmp_color).v)[1] < 0
			|| ((l.tmp_color).v)[2] < 0)
		error(4);
}

/*
 * Based on transparency/specular reflection, determine how much influence this
 * object has on the color of this pixel.
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
				influence *= (((p->pi_arr[i - 1])->vis_obj)->m).transparent;
			i--;
		}
	}
	else if ((p->pi_arr[i])->type == 1)
	{
		while (i > 0)
		{
			if ((p->pi_arr[i - 1])->type < 2)
				influence *= (((p->pi_arr[i - 1])->vis_obj)->m).specular;
			i--;
		}
	}
	return (influence);
}

/*
 * Change the value for this specific light based on intensity, influence,
 * color, etc..
 */

static double	set_light_value(t_intensity in, t_pixel *p,
		t_source l, int i)
{
	t_3v		*c;
	t_3v		o;
	double		influence;

	o = ((p->pi_arr[i])->obj_m).color;
	c = &(p->c_per_src[l.id]);
	influence = get_influence(p, i);
	if (((p->pi_arr[i])->vis_obj)->from_inside)
		influence *= ((p->pi_arr[i])->obj_m).transparent;
	in.diff = in.diff * (l.intensity).diff;
	in.spec = in.spec * (l.intensity).spec;
	check_values(&in, o, l);
	in.diff *= (influence * (1 - in.spec));
	in.spec *= influence;
	(c->v)[0] += in.diff * ((l.tmp_color).v)[0] * (o.v)[0];
	(c->v)[1] += in.diff * ((l.tmp_color).v)[1] * (o.v)[1];
	(c->v)[2] += in.diff * ((l.tmp_color).v)[2] * (o.v)[2];
	(c->v)[0] += in.spec * ((l.tmp_color).v)[0];
	(c->v)[1] += in.spec * ((l.tmp_color).v)[1];
	(c->v)[2] += in.spec * ((l.tmp_color).v)[2];
	return ((c->v)[0] + (c->v)[1] + (c->v)[2]);
}

/*
 * For all objects involved in this pixel, update the light value at this pixel
 * for this specific source.
 */

static void		light_intensity(t_source src, t_pixel *p, t_scene *scene)
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
		in.diff = 0;
		in.spec = 0;
		if (light_reaches(dir, scene->objects, (scene->cam)->id, &src) > 0.01)
			in = get_intensity(pi, dir, *(scene->cam), src.id - 1);
		set_light_value(in, p, src, r);
		r++;
	}
}

/*
 * For this specific source, loop through all the pixels to see what its
 * influence is.
 */

void		set_light_per_pixel(t_event *event, t_source src)
{
	t_pixel		*p;
	t_scene		scene;
	int			i;
	int			j;

	i = 0;
	scene = event->scene;
	while (i < scene.height)
	{
		j = 0;
		while (j < scene.width)
		{
			p = &(((scene.cam)->p_array)[j + i * scene.width]);
			p->c_per_src[src.id] = ft_zero_3v();
			light_intensity(src, p, &scene);
			j += (scene.cam)->grain;
		}
		i += (scene.cam)->grain;
	}
}
