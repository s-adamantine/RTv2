/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 17:46:56 by mpauw             #+#    #+#             */
/*   Updated: 2018/02/26 13:31:09 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_source	init_source(t_source *o_source, t_object *object)
{
	t_source	source;

	source.origin = get_rel_origin(o_source->origin, object);
	change_dir(&(source.origin), object->rotation);
	source.id = o_source->id;
	source.origin_o = &(o_source->origin);
	return (source);
}

static void		rotate_sources(t_object *object, t_scene *scene)
{
	t_source	source;
	t_source	*o_source;
	t_list		*lst;

	lst = scene->lights;
	while (lst && lst->content)
	{
		o_source = (t_source *)(lst->content);
		source = init_source(o_source, object);
		ft_lstaddnewr(&(object->rel_lights), &source, sizeof(source));
		lst = lst->next;
	}
}

void			rotate_object(t_object *object, t_scene *scene, int only_cam)
{
	int			i;
	t_source	rel_cam_src;
	t_source	o_cam_src;

	i = 0;
	if (!object || !scene)
		error(0);
	if (!only_cam && !(object->rel_lights = ft_lstnew(NULL, 0)))
		error(1);
	while (i < 3)
	{
		ft_rotate_3v(&(object->normal), i, ((object->rotation).v)[i], 0);
		i++;
	}
	o_cam_src.origin = (scene->camera).origin;
	o_cam_src.rotation = (scene->camera).rotation;
	o_cam_src.id = (scene->camera).id;
	rel_cam_src = init_source(&o_cam_src, object);
	(object->rel_cam).origin = rel_cam_src.origin;
	(object->rel_cam).rotation = rel_cam_src.rotation;
	(object->rel_cam).id = rel_cam_src.id;
	if (!only_cam)
		rotate_sources(object, scene);
}
