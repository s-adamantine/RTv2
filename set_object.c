/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_object_new.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 15:22:15 by mpauw             #+#    #+#             */
/*   Updated: 2018/02/07 15:25:44 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	init_def_object(t_object *object, int id)
{
	t_3v	def;

	def = ft_zero_3v();
	object->id = id;
	object->type = 0;
	object->origin = def;
	def = ft_zero_3v();
	object->rotation = def;
	object->radius = RADIUS;
	object->diffuse = ALBEDO;
	def = ft_init_3v(1.0, 1.0, 0.0);
	object->color = def;
	def = ft_init_3v(0.0, 1.0, 0.0);
	object->normal = def;
}

static void	set_det(t_object *object, t_scene *scene)
{
	scene->amount_obj++;
	rotate_object(object, scene, 0);
	if (object->type == 0)
		object->f = &get_s_plane;
	else if (object->type == 1)
		object->f = &get_s_sphere;
	else if (object->type == 2)
		object->f = &get_s_cylinder;
	else if (object->type == 3)
		object->f = &get_s_cone;
}

static int	get_object_type(char *s)
{
	int		to_return;

	to_return = -1;
	if (ft_strncmp(s, "plane", 5) == 0)
		to_return = 0;
	else if (ft_strncmp(s, "sphere", 6) == 0)
		to_return = 1;
	else if (ft_strncmp(s, "cylinder", 8) == 0)
		to_return = 2;
	else if (ft_strncmp(s, "cone", 4) == 0)
		to_return = 3;
	else
		s_error("Object type is not valid");
	return (to_return);
}

static void	set_values_object(t_object *obj, char *s, char *value)
{
	double	*tmp;

	if (ft_strncmp(s, "type", 4) == 0)
		obj->type = get_object_type(value);
	else if (ft_strncmp(s, "origin", 6) == 0)
		update_vector(&(obj->origin), value);
	else if (ft_strncmp(s, "rotation", 7) == 0)
		update_vector(&(obj->rotation), value);
	else if (ft_strncmp(s, "color", 5) == 0)
		update_vector(&(obj->color), value);
	else if (ft_strncmp(s, "radius", 6) == 0)
		obj->radius = ft_atod(value);
	else if (ft_strncmp(s, "reflection", 10) == 0)
	{
		if (!(tmp = (double *)malloc(4 * sizeof(double))))
			error(0);
		get_doubles_from_line(tmp, value, 4);
		obj->ambient = tmp[0];
		obj->diffuse = tmp[1];
		obj->specular = tmp[2];
		obj->shininess = tmp[3];
		free(tmp);
	}
}

void		set_object(t_list **objects, t_scene *scene, int id, int fd)
{
	char		*line;
	char		*s;
	char		*value;
	t_object	object;
	int			gnl;

	init_def_object(&object, id);
	while ((gnl = get_next_line(fd, &line)) == 1)
	{
		if (*(line) == '}')
			break ;
		if (ft_isalpha(*line) || !(s = ft_brace_content(line, '{', '}')))
			error(0);
		if (!(value = ft_brace_content(s, '{', '}')))
			error(0);
		set_values_object(&object, s, value);
		free(line);
		free(s);
		free(value);
	}
	if (gnl < 0)
		error(0);
	set_det(&object, scene);
	free(line);
	ft_lstaddnewr(objects, &object, sizeof(object));
}
