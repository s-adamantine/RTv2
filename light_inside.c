/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_inside.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 12:03:49 by mpauw             #+#    #+#             */
/*   Updated: 2018/03/22 17:41:34 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	behind_plane(t_object *obj, t_source *src, t_scene *scene)
{
	t_3v	dir;
	double	t_value;

	dir = ft_3v_subtract(src->origin, (scene->cam)->origin);
	t_value = obj->f(obj, dir, 0);
	if (t_value < 1 && t_value > 0)
		return (1);
	return (0);
}

static int	s_in_object(t_object *obj, t_source *src)
{
	t_3v	tmp_dir;
	int		intersections;
	int		rotated;

	intersections = 0;
	rotated = 0;
	while (intersections < 3)
	{
		tmp_dir = get_dir(ft_get_3v_unit(intersections), obj->rotation);
		if (rotated)
			tmp_dir = get_dir(tmp_dir, ft_init_3v(45, 45, 45));
		if (obj->f(obj, tmp_dir, src->id + 1) != -1)
			intersections++;
		else if (rotated)
			return (0);
		else if (++rotated)
			intersections = 0;
	}
	return (1);
}

void	check_s_inside(int *inside_obj, t_source *src,
		t_scene *scene, int b)
{
	t_object	*obj;
	t_list		*tmp;
	int			i;

	tmp = scene->objects;
	i = 0;
	while (tmp && tmp->content)
	{
		obj = (t_object *)tmp->content;
		if (obj->type != 0 && s_in_object(obj, src))
			inside_obj[i] = 1;
		else if (obj->type == 0 && b != -1 &&
				behind_plane(obj, src, scene))
			inside_obj[i] = 1;
		else
			inside_obj[i] = 0;
		tmp = tmp->next;
		i++;
	}
}

void		*light_inside(void *arg)
{
	t_scene		*scene;
	t_list		*s_lst;
	t_cam		*cam;
	t_source	*src;

	scene = &(((t_event *)arg)->scene);
	s_lst = scene->lights;
	cam = scene->cam;
	while (s_lst && s_lst->content)
	{
		src = (t_source *)s_lst->content;
		if (!(src->inside_obj = (int *)malloc(sizeof(int) * scene->amount_obj)))
			error(1);
		check_s_inside(src->inside_obj, src, scene, src->id);
		s_lst = s_lst->next;
	}
	if (!(cam->inside_obj = (int *)malloc(sizeof(int) * scene->amount_obj)))
		error(1);
	check_s_inside(cam->inside_obj, src, scene, -1);
	return (NULL);
}
