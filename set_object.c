/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_object_new.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 15:22:15 by mpauw             #+#    #+#             */
/*   Updated: 2018/06/25 15:58:25 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		init_def_object(t_object *obj, int id, t_scene *scene,
		t_object *parent)
{
	if (parent)
		parent->is_group_main = 1;
	obj->group_id = (parent) ? parent->group_id : 0;
	obj->group_rotation = (parent) ? parent->rotation : ft_zero_3v();
	obj->group_origin = (parent) ? parent->origin : ft_zero_3v();
	obj->size = (parent) ? parent->size : 1.0;
	obj->id = id;
	obj->type = 0;
	obj->f = &get_t_plane;
	obj->axis_rotation = 0;
	obj->origin = ft_zero_3v();
	obj->origin_2 = ft_init_3v(1.0, 0.0, 0.0);
	obj->origin_3 = ft_init_3v(0.0, 1.0, 0.0);
	obj->is_group_main = 0;
	obj->rotation = ft_zero_3v();
	obj->axis_rotation = 0;
	obj->radius = 1;
	obj->pattern_id = 0;
	obj->lim_by_1 = 0;
	obj->lim_by_2 = 0;
	obj->limit_id = 0;
	obj->visible = 1;
	obj->path = NULL;
	change_material(scene, obj, 0, 0);
	scene->amount_obj++;
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
			obj->pattern_id = id;
			break ;
		}
		tmp = tmp->next;
	}
}

static void	set_values_object_2(t_scene *scene, t_object *obj, char *s,
		char *value)
{
	if (ft_strncmp(s, "sec_material", 12) == 0)
		change_material(scene, obj, ft_atoi(value), 2);
	else if (ft_strncmp(s, "limited_by_1", 12) == 0)
		obj->lim_by_1 = ft_atoi(value) + (obj->group_id * LIMIT_CORR);
	else if (ft_strncmp(s, "limited_by_2", 12) == 0)
		obj->lim_by_2 = ft_atoi(value) + (obj->group_id * LIMIT_CORR);
	else if (ft_strncmp(s, "limit_id", 8) == 0)
		obj->limit_id = ft_atoi(value) + (obj->group_id * LIMIT_CORR);
	else if (ft_strncmp(s, "group_id", 8) == 0)
		obj->group_id = ft_atoi(value);
	else if (ft_strncmp(s, "is_group_main", 13) == 0)
		(obj->is_group_main)++;
	else if (ft_strncmp(s, "visible", 7) == 0)
		obj->visible = ft_atoi(value);
	else if (ft_strncmp(s, "path", 4) == 0)
		obj->path = ft_strdup(value);
	else if (ft_strncmp(s, "size", 4) == 0)
		obj->size = ft_atod(value);
	else
		set_values_material(&(obj->m), s, value);
}

static void	set_values_object(t_scene *scene, t_object *obj, char *s,
		char *value)
{
	if (ft_strncmp(s, "type", 4) == 0)
		set_object_type(value, obj);
	else if (ft_strncmp(s, "origin_2", 8) == 0)
		update_vector(&(obj->origin_2), value);
	else if (ft_strncmp(s, "origin_3", 8) == 0)
		update_vector(&(obj->origin_3), value);
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
	else
		set_values_object_2(scene, obj, s, value);
}

void		set_object(t_scene *scene, int id, int fd, t_object *parent)
{
	char		*line;
	char		*s;
	char		*value;
	t_object	obj;
	int			gnl;

	init_def_object(&obj, id, scene, parent);
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
	check_for_composite(scene, &obj);
	ft_lstaddnewr(&(scene->objects), &obj, sizeof(obj));
}
