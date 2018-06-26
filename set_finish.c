/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_finish.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 13:23:19 by mpauw             #+#    #+#             */
/*   Updated: 2018/06/26 11:47:40 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	set_group_object(t_object *obj_to_set)
{
	obj_to_set->origin = ft_3v_scalar(obj_to_set->origin, obj_to_set->size);
	if (obj_to_set->type == 2 || obj_to_set->type == 1)
		obj_to_set->radius = obj_to_set->radius * obj_to_set->size;
	obj_to_set->rotation = ft_3v_add(obj_to_set->rotation,
			obj_to_set->group_rotation);
	obj_to_set->origin = rotate_v(obj_to_set->origin,
			obj_to_set->group_rotation);
	obj_to_set->origin = ft_3v_add(obj_to_set->origin,
			obj_to_set->group_origin);
}

static void	set_limit_object(t_list *lst, int lim_id_1, int lim_id_2,
		t_object *obj_to_set)
{
	t_list		*tmp_obj;
	t_object	*obj;
	int			set;

	tmp_obj = lst;
	set = 0;
	while (tmp_obj && tmp_obj->content)
	{
		obj = (t_object *)tmp_obj->content;
		if (obj->limit_id == lim_id_1 && ++set)
			obj_to_set->obj_lim_1 = obj;
		else if (obj->limit_id == lim_id_2 && ++set)
			obj_to_set->obj_lim_2 = obj;
		tmp_obj = tmp_obj->next;
	}
	if (set != 2)
	{
		obj_to_set->lim_by_1 = 0;
		obj_to_set->lim_by_2 = 0;
	}
}

void		set_finish(t_scene *scene)
{
	t_list		*tmp_obj;
	t_object	*obj;

	tmp_obj = scene->objects;
	while (tmp_obj && tmp_obj->content)
	{
		obj = (t_object *)tmp_obj->content;
		if (obj->lim_by_1 > 0 && obj->lim_by_2 > 0)
			set_limit_object(scene->objects, obj->lim_by_1,
					obj->lim_by_2, obj);
		if (obj->group_id > 0)
			set_group_object(obj);
		if (obj->type == 6)
			create_mesh(&(scene->objects), obj, scene);
		tmp_obj = tmp_obj->next;
	}
}
