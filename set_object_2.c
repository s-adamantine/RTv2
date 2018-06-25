/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_object_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 11:20:53 by mpauw             #+#    #+#             */
/*   Updated: 2018/06/25 15:25:08 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		change_material(t_scene *scene, t_object *obj, int value, int mat)
{
	t_material	*material;
	t_list		*tmp;

	tmp = scene->materials;
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
	if (ft_strncmp(s, "triangle", 8) == 0)
	{
		obj->f = &get_t_triangle;
		obj->type = 5;
	}
	else if (ft_strncmp(s, "mesh", 4) == 0)
	{
		obj->f = &get_t_mesh;
		obj->type = 6;
	}
	else if (ft_strncmp(s, "composite", 9) == 0)
	{
		obj->f = &get_t_mesh;
		obj->type = 7;
	}
	else
		s_error("Object type is not valid");
}

void		set_object_type(char *s, t_object *obj)
{
	if (ft_strncmp(s, "plane", 5) == 0)
	{
		obj->f = &get_t_plane;
		obj->type = 0;
	}
	else if (ft_strncmp(s, "sphere", 6) == 0)
	{
		obj->f = &get_t_sphere;
		obj->type = 1;
	}
	else if (ft_strncmp(s, "cylinder", 8) == 0)
	{
		obj->f = &get_t_cylinder;
		obj->type = 2;
	}
	else if (ft_strncmp(s, "cone", 4) == 0)
	{
		obj->f = &get_t_cone;
		obj->type = 3;
	}
	else
		set_object_type_2(s, obj);
}
