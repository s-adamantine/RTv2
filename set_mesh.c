/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_mesh.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadamant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 21:59:09 by sadamant          #+#    #+#             */
/*   Updated: 2018/06/25 15:00:47 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	create_triangle(t_list **objects, t_object *parent, t_scene *scene,
		t_3v *coordinates)
{
	t_object	obj;

	scene->amount_obj++;
	init_def_object(&obj, scene->amount_obj, scene, NULL);
	obj.type = 5;
	obj.f = &get_t_triangle;
	obj.m = parent->m;
	obj.m2 = parent->m2;
	obj.pattern = parent->pattern;
	obj.origin = coordinates[0];
	obj.origin_2 = coordinates[1];
	obj.origin_3 = coordinates[2];
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
}
