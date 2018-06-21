/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fixed_values.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 13:49:54 by mpauw             #+#    #+#             */
/*   Updated: 2018/06/21 18:40:41 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
 * Set fixed values for reflective and transparent points (work as new camera).
 */

void		set_value_refl(t_3v point, t_object *o, int r, int cam_id,
		int thread_id)
{
	t_fixed_v	*tmp;
	int			i;

	if (!(tmp = (t_fixed_v *)malloc(sizeof(t_fixed_v) * (r + 1))))
		error(1);
	i = 0;
	while (i < r)
	{
		tmp[i] = o->fixed_c[thread_id][cam_id][i];
		i++;
	}
	free(o->fixed_c[thread_id][cam_id]);
	o->fixed_c[thread_id][cam_id] = tmp;
	set_fixed_value(point, o, &(o->fixed_c[thread_id][cam_id][r]));
}

/*
 * Set fixed values for the sources.
 */

static void	set_src(t_scene *scene, t_object *o, int first)
{
	t_list		*srcs;
	t_source	*src;
	int			i;

	i = 0;
	srcs = scene->lights;
	if (first && !(o->fixed_s[scene->thread_id] =
				(t_fixed_v **)malloc(sizeof(t_fixed_v *)
				* scene->cam_set)))
		error(1);
	if (!(o->fixed_s[scene->thread_id][(scene->cam)->id] =
				(t_fixed_v *)malloc(sizeof(t_fixed_v) * scene->amount_light)))
		error(1);
	while (srcs && srcs->content)
	{
		src = (t_source *)srcs->content;
		if (src->type)
		{
			set_fixed_value(src->origin, o,
					&(o->fixed_s[scene->thread_id][(scene->cam)->id][i]));
			i++;
		}
		srcs = srcs->next;
	}
}

/*
 * Set fixed values for a camera, only allocate memory if it's the first call to
 * the function.
 */

void		init_arrays(int first, t_object *o, t_scene *scene, t_cam *cam)
{
	if (first && !(o->fixed_c[scene->thread_id] =
			(t_fixed_v **)malloc(sizeof(t_fixed_v *)
				* scene->cam_set)))
		error(1);
	if (!(o->fixed_c[scene->thread_id][cam->id] =
			(t_fixed_v *)malloc(sizeof(t_fixed_v))))
		error(1);
}

void		set_fixed_values(t_scene *scene)
{
	t_list		*objects;
	t_object	*o;
	t_cam		*cam;
	int			l;
	int			first;

	l = (scene->amount_light + scene->refl + 1) * scene->cam_set;
	cam = scene->cam;
	first = (((t_cam *)(scene->cameras)->content)->init + 1) % 2;
	while (scene->thread_id < THREADS)
	{
		objects = scene->objects;
		while (objects && objects->content)
		{
			o = (t_object *)objects->content;
			init_arrays(first, o, scene, cam);
			set_fixed_value(cam->origin, o,
					o->fixed_c[scene->thread_id][(scene->cam)->id]);
			set_src(scene, o, first);
			objects = objects->next;
		}
		scene->thread_id++;
	}
	scene->thread_id = 0;
}
