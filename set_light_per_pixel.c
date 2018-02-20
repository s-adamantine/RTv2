/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_light_per_pixel.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 15:42:20 by mpauw             #+#    #+#             */
/*   Updated: 2018/02/20 18:32:32 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int		light_reaches(t_3v dir, t_list *objects, int src_id,
		double *int_2)
{
	double		t_value;
	double		t_value_2;
	int			reached;
	t_list		*o_lst;
	t_object	*obj;
	t_3v		dir_a;
	t_source	*rel_src;

	o_lst = objects;
	reached = 0;
	while (o_lst && o_lst->content)
	{
		obj = (t_object *)o_lst->content;
		dir_a = get_dir(dir, obj->rotation);
		rel_src = get_source(src_id, obj->rel_lights);
		t_value = obj->f(obj, dir_a, rel_src->origin, int_2);
		if (t_value > 0.001 && t_value < 0.99999)
			return (0);
		else if (t_value > 0.99999 && t_value < 1.001 && *int_2 < 0.001)
			return (0);
		else if (t_value > 0.99999 && t_value < 1.001)
		{
			reached = 1;
			t_value_2 = *int_2;
		}
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

static void		set_light_value(t_intensity in, t_pixel *p,
		t_source l, int i)
{
	t_3v		*c;
	t_object	o;
	double		influence;

	o = *(p->vis_obj_r[i]);
	c = &(p->c_per_src[l.id - 1]);
	influence = 1.0;
	while (i > 0)
	{
		influence *= ((p->vis_obj_r)[i - 1])->specular;
		i--;
	}
	in.diff = in.diff * (l.intensity).diff;
	in.spec = in.spec * (l.intensity).spec;
	check_values(&in, o, l);
	(c->v)[0] += influence * (1 - in.spec) * in.diff * ((l.color).v)[0] * ((o.color).v)[0];
	(c->v)[1] += influence * (1 - in.spec) * in.diff * ((l.color).v)[1] * ((o.color).v)[1];
	(c->v)[2] += influence * (1 - in.spec) * in.diff * ((l.color).v)[2] * ((o.color).v)[2];
	(c->v)[0] += in.spec * ((l.color).v)[0];
	(c->v)[1] += in.spec * ((l.color).v)[1];
	(c->v)[2] += in.spec * ((l.color).v)[2];
}

static void		light_intensity(t_source src, t_pixel *p, t_event *event)
{
	t_3v		dir;
	t_scene		scene;
	t_intensity	in;
	t_cam		view;
	int			i;

	scene = event->scene;
	i = 0;
	while (i < scene.refl && p->vis_obj_r[i])
	{
		dir = ft_3v_subtract(p->point_r[i], (src.origin));
		in.diff = 0;
		in.spec = 0;
		if (i == 0)
			view = scene.camera;
		else
		{
			view.origin = p->point_r[i - 1];
			view.rotation = ft_zero_3v();
		}
		if (light_reaches(dir, scene.objects, src.id, &(p->int_2_r[i])) > 0.01)
			in = get_intensity(p->point_r[i], p->vis_obj_r[i], dir, view);
		set_light_value(in, p, src, i);
		i++;
	}
}

void		set_light_per_pixel(t_event *event, t_source src)
{
	t_pixel		*p;
	int			i;
	int			j;

	i = 0;
	while (i < (event->scene).height)
	{
		j = 0;
		while (j < (event->scene).width)
		{
			p = &((event->p_array)[j + i * (event->scene).width]);
			j++;
			if (!p->vis_obj)
				continue ;
			light_intensity(src, p, event);
		}
		i++;
	}
}
