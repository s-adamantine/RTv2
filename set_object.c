/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_object_new.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 15:22:15 by mpauw             #+#    #+#             */
/*   Updated: 2018/05/09 14:20:09 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	init_def_object(t_object *obj, int id)
{
	t_3v	def;

	def = ft_zero_3v();
	obj->id = id;
	obj->type = 0;
	obj->f = &get_t_plane;
	obj->axis_rotation = 0;
	obj->origin = def;
	def = ft_zero_3v();
	obj->rotation = def;
	obj->radius = 1;
}

static void	set_object_type(char *s, t_object *obj, t_scene *scene)
{
	scene->amount_obj++;
	if (ft_strncmp(s, "plane", 5) == 0)
	{
		obj->f = &get_t_plane;
		obj->type  = 0;
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
		s_error("Object type is not valid");
}

static void	change_material(t_scene *scene, t_object *obj, int value, int mat)
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

static void	make_point_list(t_pattern *p)
{

	int			i;
	double		offset;
	double		

	if (!(p->point_arr = (t_3v *)malloc(sizeof(t_3v) * p->amount_points)))
		error(2);
	i = 0;
	while (i < p->amount_points)
	{
	}
}

static void	get_pattern(t_scene *scene, t_object *obj, int id)
{
	t_pattern	*p;
	t_list		*tmp;

	tmp = scene->patterns;
	while (tmp && tmp->content)
	{
		p = (t_pattern *)tmp->content;
		if (p->id == id)
		{
			obj->pattern = *p;
			break ;
		}
		tmp = tmp->next;
	}
	if (p && p->type == 1 && obj->type == 1 && p->amount_points > 0)
		make_point_list(&(obj->pattern));
}

static void	set_values_object(t_scene *scene, t_object *obj, char *s,
		char *value)
{
	if (ft_strncmp(s, "type", 4) == 0)
		set_object_type(value, obj, scene);
	else if (ft_strncmp(s, "origin", 6) == 0)
		update_vector(&(obj->origin), value);
	else if (ft_strncmp(s, "rotation", 7) == 0)
		update_vector(&(obj->rotation), value);
	else if (ft_strncmp(s, "axis_rotation", 11) == 0)
		obj->axis_rotation = ft_atod(value);
	else if (ft_strncmp(s, "radius", 6) == 0)
		obj->radius = ft_atod(value);
	else if (ft_strncmp(s, "pattern", 7) == 0)
		get_pattern(scene, obj, ft_atoi(value));
	else if (ft_strncmp(s, "material", 8) == 0)
		change_material(scene, obj, ft_atoi(value), 1);
	else if (ft_strncmp(s, "sec_material", 12) == 0)
		change_material(scene, obj, ft_atoi(value), 2);
	else
		set_values_material(&(obj->m), s, value);
}

void		set_object(t_list **objects, t_scene *scene, int id, int fd)
{
	char		*line;
	char		*s;
	char		*value;
	t_object	obj;
	int			gnl;

	init_def_object(&obj, id);
	change_material(scene, &obj, 0, 0);
	while ((gnl = get_next_line(fd, &line)) == 1)
	{
		if (*(line) == '}')
			break ;
		if (ft_isalpha(*line) || !(s = ft_brace_content(line, '{', '}')))
			error(0);
		if (!(value = ft_brace_content(s, '{', '}')))
			error(0);
		set_values_object(scene, &obj, s, value);
		free(line);
		free(s);
		free(value);
	}
	if (gnl < 0)
		error(0);
	free(line);
	ft_lstaddnewr(objects, &obj, sizeof(obj));
}
