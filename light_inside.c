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

/*
 * This file should determine whether lights and cameras are inside an object,
 * or in the case of a plane behind the object. This last part is the problem
 * now, since it depends on the position of the camera. I'll skip the checking
 * for light for now, but we should revisit this part. Basically, we can very
 * much improve this by creating an array of booleans per camera, determining
 * whether a specific light has an effect. That would be much more efficient
 * than the current method.
 */

static int		check_inside(t_3v dir, t_object *obj, t_cam *cam)
{
	double		t_1;
	double		t_2;

	t_1 = obj->f(obj->fixed_c[cam->id][0], dir, 0);
	if (obj->type == 0 && t_1 < 0.999 && t_1 > 0.001)
		return (1);
	t_2 = obj->f(obj->fixed_c[cam->id][0], dir, 1);
	if (t_1 < 0.999 && t_1 > 0.001 && t_2 > 1.001)
		return (1);
	return (0);
}

static double	check_s_inside(t_source *src, t_scene *scene, t_cam *cam)
{
	t_3v		dir;
	t_list		*o_lst;
	t_object	*obj;
	int			inside;
	double		influence;

	o_lst = scene->objects;
	influence = 1.0;
	while (o_lst && o_lst->content)
	{
		dir = ft_3v_subtract(src->origin, cam->origin);	
		if (dir.v[0] == 0 && dir.v[1] == 0 && dir.v[2] == 0)
			dir.v[1] = 1;
		obj = (t_object *)o_lst->content;
		inside = check_inside(dir, obj, cam);
		if (inside)
			influence *= obj->transparent;
		o_lst = o_lst->next;
	}
	return (influence);
}

static void		check_all(t_scene *scene, t_cam *cam)
{
	t_list		*s_lst;
	t_source	*src;
	int			i;

	s_lst = scene->lights;
	i = 0;
	while (s_lst && s_lst->content)
	{
		src = (t_source *)s_lst->content;
		if (src->type != 0)
		{
			cam->light_vis[i] = check_s_inside(src, scene, cam);
			i++;
		}
		s_lst = s_lst->next;
	}
}

void			light_inside(t_scene *scene)
{
	t_cam		*cam;

	cam = scene->cam;
	if (!(cam->light_vis = (double *)malloc(sizeof(double) *
					scene->amount_light)))
		error(1);
	check_all(scene, cam);
}
