/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_mesh.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadamant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 21:59:09 by sadamant          #+#    #+#             */
/*   Updated: 2018/06/26 16:11:06 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	create_triangle(t_list **objects, t_object *parent, t_scene *scene,
		t_3v *coordinates)
{
	t_object	obj;

	parent->group_id = check_for_composite(scene, parent);
	init_def_object(&obj, scene->amount_obj, scene, parent);
	obj.type = 5;
	obj.f = &get_t_triangle;
	obj.m = parent->m;
	obj.m2 = parent->m2;
	obj.pattern = parent->pattern;
	obj.origin = rotate_v(coordinates[0], obj.group_rotation);
	obj.origin_2 = rotate_v(coordinates[1], obj.group_rotation);
	obj.origin_3 = rotate_v(coordinates[2], obj.group_rotation);
	free(coordinates);
	ft_lstaddnewr(objects, &obj, sizeof(obj));
}

void		create_mesh(t_list **objects, t_object *parent, t_scene *scene)
{
	int		i;
	t_3v	**coordinates;

	i = 0;
	coordinates = read_obj_file(parent->path, 0);
	while (coordinates[i])
	{
		create_triangle(objects, parent, scene, coordinates[i]);
		i++;
	}
	free(coordinates);
}
