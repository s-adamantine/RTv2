/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_light_value.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 18:31:47 by mpauw             #+#    #+#             */
/*   Updated: 2018/02/02 12:01:03 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static double		light_reaches(t_3v dir, t_list *objects, int src_id)
{
	double		t_value;
	t_list		*o_lst;
	t_object	*obj;
	t_3v		dir_a;
	t_source	*rel_src;

	o_lst = objects;
	while (o_lst && o_lst->content)
	{
		obj = (t_object *)o_lst->content;
		dir_a = get_dir(dir, obj->rotation);
		rel_src = get_source(src_id, obj->rel_lights);
		t_value = obj->f(obj, dir_a, rel_src->origin);
		if (t_value > 0.001 && t_value < 0.99999)
			return (0);
		o_lst = o_lst->next;
	}
	return (1);
}

static void			update_color(t_intensity intensity, t_3v *color,
		t_object *o, t_source l)
{
	intensity.diff = intensity.diff * (l.intensity).diff;
	intensity.spec = intensity.spec * (l.intensity).spec;
	if (intensity.diff > 1)
		intensity.diff = 1;
	if (intensity.spec > 1)
		intensity.spec = 1;
	if (((o->color).v)[0] > 1 || ((o->color).v)[1] > 1 || ((o->color).v)[2] > 1
			|| ((o->color).v)[0] < 0 || ((o->color).v)[1] < 0
			|| ((o->color).v)[2] < 0 || ((l.color).v)[0] > 1
			|| ((l.color).v)[1] > 1 || ((l.color).v)[2] > 1
			|| ((l.color).v)[0] < 0 || ((l.color).v)[1] < 0
			|| ((l.color).v)[2] < 0)
		error(4);
	(color->v)[0] += intensity.diff * ((l.color).v)[0] * ((o->color).v)[0];
	(color->v)[1] += intensity.diff * ((l.color).v)[1] * ((o->color).v)[1];
	(color->v)[2] += intensity.diff * ((l.color).v)[2] * ((o->color).v)[2];
	(color->v)[0] += intensity.spec * ((l.color).v)[0];
	(color->v)[1] += intensity.spec * ((l.color).v)[1];
	(color->v)[2] += intensity.spec * ((l.color).v)[2];
}

int					get_light_value(t_3v point, t_scene *scene, t_list *sources,
		t_object *obj)
{
	t_list		*s_lst;
	t_source	*src;
	t_3v		dir;
	t_3v		color;
	t_intensity	intensity;

	s_lst = sources;
	color = ft_init_3v(((obj->color).v)[0] * obj->ambient * scene->ambient,
			((obj->color).v)[1] * obj->ambient * scene->ambient,
			((obj->color).v)[2] * obj->ambient * scene->ambient);
	while (s_lst && s_lst->content)
	{
		src = (t_source *)s_lst->content;
		dir = ft_3v_subtract(point, (src->origin));
		if (light_reaches(dir, scene->objects, src->id) > 0.01)
		{
			intensity = get_intensity(point, obj, dir, scene->camera);
			update_color(intensity, &color, obj, *src);
		}
		s_lst = s_lst->next;
	}
	return (get_color((color.v)[0], (color.v)[1], (color.v)[2]));
}
