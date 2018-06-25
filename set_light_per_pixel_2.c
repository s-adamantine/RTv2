/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_light_per_pixel_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 11:03:55 by mpauw             #+#    #+#             */
/*   Updated: 2018/06/25 19:35:25 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double			get_influence_specular(t_pixel *p, int i)
{
	if ((((p->pi_arr[i - 1])->vis_obj)->m).transparent > 0.001
		&& ((p->pi_arr[i - 1])->is_inside == 1 ||
			(((p->pi_arr[i - 1])->vis_obj)->m).specular < 0.001))
		return ((p->pi_arr[i - 1])->fresnal_specular);
	else if ((((p->pi_arr[i - 1])->vis_obj)->m).transparent > 0.001 &&
		(((p->pi_arr[i - 1])->vis_obj)->m).specular > 0.001)
		return ((((p->pi_arr[i - 1])->vis_obj)->m).specular
			* (p->pi_arr[i - 1])->fresnal_specular);
	else
		return ((((p->pi_arr[i - 1])->vis_obj)->m).specular);
}

/*
** Get type of material light reaches, based on pattern. If transparent: deal
** with it.
*/

static void		get_light_color(t_object *obj, t_3v point, t_source *src,
	t_scene *scene)
{
	t_material	m;

	if ((obj->pattern).type == 0)
	{
		(src->tmp_color).v[0] = .5 * (1 - (obj->m).transparent) *
			((obj->m).color).v[0] + (obj->m).transparent * src->tmp_color.v[0];
		(src->tmp_color).v[1] = .5 * (1 - (obj->m).transparent) *
			((obj->m).color).v[1] + (obj->m).transparent * src->tmp_color.v[1];
		(src->tmp_color).v[2] = .5 * (1 - (obj->m).transparent) *
			((obj->m).color).v[2] + (obj->m).transparent * src->tmp_color.v[2];
		(src->tmp_color).v[0] *= (obj->m).transparent * ((obj->m).color).v[0];
		(src->tmp_color).v[1] *= (obj->m).transparent * ((obj->m).color).v[1];
		(src->tmp_color).v[2] *= (obj->m).transparent * ((obj->m).color).v[2];
		return ;
	}
	m = get_object_material(*obj, point, *scene);
	(src->tmp_color).v[0] = .5 * (1 - m.transparent) * (m.color).v[0] +
		m.transparent * src->tmp_color.v[0];
	(src->tmp_color).v[1] = .5 * (1 - m.transparent) * (m.color).v[1] +
		m.transparent * src->tmp_color.v[1];
	(src->tmp_color).v[2] = .5 * (1 - m.transparent) * (m.color).v[2] +
		m.transparent * src->tmp_color.v[2];
	(src->tmp_color).v[0] *= m.transparent;
	(src->tmp_color).v[1] *= m.transparent;
	(src->tmp_color).v[2] *= m.transparent;
}

/*
** Does the light reach the visible object (after passing through transparent
** objects or not).
*/

double			light_reaches(t_3v d, t_scene *scene, t_source *src)
{
	double		t_1;
	double		reached;
	t_list		*o_lst;
	t_object	*obj;

	o_lst = scene->objects;
	reached = 0;
	while (o_lst && o_lst->content)
	{
		obj = (t_object *)o_lst->content;
		t_1 = obj->f(obj->fixed_s[scene->thread_id][scene->cam->id]
				[src->id - 1], d, 0, obj);
		if (t_1 > 0.001 && t_1 < 0.99999 && obj->visible)
			get_light_color(obj, get_point(src->origin, d, t_1), src, scene);
		else if (t_1 > 0.999999 && t_1 < 1.000001)
			reached = 1;
		o_lst = o_lst->next;
	}
	return (reached);
}
