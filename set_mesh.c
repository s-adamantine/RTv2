/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_mesh.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadamant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 21:59:09 by sadamant          #+#    #+#             */
/*   Updated: 2018/06/18 21:59:16 by sadamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	create_triangle(t_list **objects, t_object *parent, t_scene *scene, t_3v *coordinates)
{
	t_object	obj;

	scene->amount_obj++;
	init_def_object(&obj, scene->amount_obj);
	//inherit all previous properties from parent
	obj.type = 5;
	obj.f = &get_t_triangle;
	obj.m = parent->m;
	obj.m2 = parent->m2;
	obj.pattern = parent->pattern;
	obj.origin = coordinates[0];
	obj.origin_2 = coordinates[1];
	obj.origin_3 = coordinates[2];
	printf("origin: %f %f %f\n", coordinates[0].v[0], coordinates[0].v[1], coordinates[0].v[2]);
	printf("origin2: %f %f %f\n", coordinates[1].v[0], coordinates[1].v[1], coordinates[1].v[2]);
	printf("origin3: %f %f %f\n\n", coordinates[2].v[0], coordinates[2].v[1], coordinates[2].v[2]);
	ft_lstaddnewr(objects, &obj, sizeof(obj));
}

void	create_mesh(t_list **objects, t_object *parent, t_scene *scene)
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
