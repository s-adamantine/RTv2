/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_object_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 11:20:53 by mpauw             #+#    #+#             */
/*   Updated: 2018/06/26 11:51:56 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		change_material(t_scene *scene, t_object *obj, int value, int mat)
{
	t_material	*material;
	t_list		*tmp;

	tmp = scene->materials;
	if (obj->m.id == 0)
		obj->m = *((t_material *)tmp->content);
	if (obj->m2.id == 0)
		obj->m2 = *((t_material *)tmp->content);
	while (tmp && tmp->content)
	{
		material = (t_material *)tmp->content;
		if (material->id == value)
		{
			if (mat == 0 || mat == 1)
				obj->m = *material;
			if (mat == 0 || mat == 2)
				obj->m2 = *material;
			break ;
		}
		tmp = tmp->next;
	}
}

static void	set_object_type_2(char *s, t_object *obj)
{
	if (ft_strcmp(s, "triangle") == 0)
	{
		obj->f = &get_t_triangle;
		obj->type = 5;
	}
	else if (ft_strcmp(s, "mesh") == 0)
	{
		obj->f = &get_t_mesh;
		obj->type = 6;
	}
	else if (ft_strcmp(s, "composite") == 0)
	{
		obj->f = &get_t_mesh;
		obj->type = 7;
	}
	else
		s_error("Object type is not valid");
}

void		set_object_type(char *s, t_object *obj)
{
	if (ft_strcmp(s, "plane") == 0)
	{
		obj->f = &get_t_plane;
		obj->type = 0;
	}
	else if (ft_strcmp(s, "sphere") == 0)
	{
		obj->f = &get_t_sphere;
		obj->type = 1;
	}
	else if (ft_strcmp(s, "cylinder") == 0)
	{
		obj->f = &get_t_cylinder;
		obj->type = 2;
	}
	else if (ft_strcmp(s, "cone") == 0)
	{
		obj->f = &get_t_cone;
		obj->type = 3;
	}
	else
		set_object_type_2(s, obj);
}
