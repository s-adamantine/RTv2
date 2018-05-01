/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_light_per_pixel.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 15:42:20 by mpauw             #+#    #+#             */
/*   Updated: 2018/03/22 17:53:41 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int		light_reaches(t_3v dir, t_list *objects, int cam,
		int fixed_val_id)
{
	double		t_value;
	int			reached;
	t_list		*o_lst;
	t_object	*obj;

	o_lst = objects;
	reached = 0;
	while (o_lst && o_lst->content)
	{
		obj = (t_object *)o_lst->content;
		t_value = obj->f(obj->fixed_s[cam][fixed_val_id], dir, 0);
		if (t_value > 0.001 && t_value < 0.99999 && obj->transparent < 0.001)
			return (0);
		else if (t_value > 0.999999 && t_value < 1.000001)
			reached = 1;
		o_lst = o_lst->next;
	}
	return (reached);
}

static void		check_values(t_intensity *in, t_object o, t_source l)
{
	if (in->diff > 1)
		in->diff = 1;
	if (in->spec > 1)
		in->spec = 1;
	if (((o.color).v)[0] > 1 || ((o.color).v)[1] > 1 || ((o.color).v)[2] > 1
			|| ((o.color).v)[0] < 0 || ((o.color).v)[1] < 0
			|| ((o.color).v)[2] < 0 || ((l.color).v)[0] > 1
			|| ((l.color).v)[1] > 1 || ((l.color).v)[2] > 1
			|| ((l.color).v)[0] < 0 || ((l.color).v)[1] < 0
			|| ((l.color).v)[2] < 0)
		error(4);
}

static double	get_influence(t_pixel *p, int i)
{
	double	influence;

	influence = 1 - ((p->pi_arr[i])->vis_obj)->transparent;
	if ((p->pi_arr[i])->type == 2)
	{
		while (i > 0)
		{
			if ((p->pi_arr[i - 1])->type % 2 == 0)
				influence *= ((p->pi_arr[i - 1])->vis_obj)->transparent;
			i--;
		}
	}
	else if ((p->pi_arr[i])->type == 1)
	{
		while (i > 0)
		{
			if ((p->pi_arr[i - 1])->type < 2)
				influence *= ((p->pi_arr[i - 1])->vis_obj)->specular;
			i--;
		}
	}
	return (influence);
}

static double	set_light_value(t_intensity in, t_pixel *p,
		t_source l, int i)
{
	t_3v		*c;
	t_object	o;
	double		influence;

	o = *((p->pi_arr[i])->vis_obj);
	c = &(p->c_per_src[l.id]);
	influence = get_influence(p, i);
	in.diff = in.diff * (l.intensity).diff;
	in.spec = in.spec * (l.intensity).spec;
	check_values(&in, o, l);
	in.diff *= (influence * (1 - in.spec));
	in.spec *= influence;
	(c->v)[0] += in.diff * ((l.color).v)[0] * ((o.color).v)[0];
	(c->v)[1] += in.diff * ((l.color).v)[1] * ((o.color).v)[1];
	(c->v)[2] += in.diff * ((l.color).v)[2] * ((o.color).v)[2];
	(c->v)[0] += in.spec * ((l.color).v)[0];
	(c->v)[1] += in.spec * ((l.color).v)[1];
	(c->v)[2] += in.spec * ((l.color).v)[2];
	return ((c->v)[0] + (c->v)[1] + (c->v)[2]);
}

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
		if (!(pi->vis_obj))
			break ;
		dir = ft_3v_subtract(pi->point, src.origin);
		in.diff = 0;
		in.spec = 0;
		if (light_reaches(dir, scene->objects, (scene->cam)->id,
					src.id - 1) > 0.01)
			in = get_intensity(pi, dir, *(scene->cam), src.id - 1);
		set_light_value(in, p, src, r);
		r++;
	}
}

void		set_light_per_pixel(t_event *event, t_source src)
{
	t_pixel		*p;
	int			i;
	int			j;

	i = 0;
//	printf("%f\n", ((event->scene).cam)->light_vis[src.id - 1]);
	while (i < (event->scene).height)
	{
		j = 0;
		while (j < (event->scene).width)
		{
			p = &((((event->scene).cam)->p_array)[j + i *
					(event->scene).width]);
			p->c_per_src[src.id] = ft_zero_3v();
			j++;
			if (!(p->pi_arr[0])->vis_obj)
				continue ;
			light_intensity(src, p, &(event->scene));
		}
		i++;
	}
}
