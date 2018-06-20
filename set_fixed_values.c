/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fixed_values.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 13:49:54 by mpauw             #+#    #+#             */
/*   Updated: 2018/06/20 16:55:25 by sadamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
 * The fixed values are values that are specific for every object, relative to
 * a camera, light source or reflection/transparent point. Instead of
 * calculating them at every pixel, we fix them for every object.
 */

static void	set_fixed_value(t_3v origin, t_object *o, t_fixed_v *f)
{
	f->dir = rotate_v(ft_init_3v(0.0, 0.0, 1.0), o->rotation);
	o->dir = f->dir;
	f->rad = o->radius;
	f->rad_sq = o->radius * o->radius;
	f->dif_c = ft_3v_subtract(origin, o->origin);
	f->origin = origin;
	if (o->type == 0)
		f->val = ft_3v_dot_product(f->dir, f->dif_c);
	else if (o->type == 1)
		f->val = ft_3v_dot_product(f->dif_c, f->dif_c);
	else if (o->type == 2 || o->type == 3)
	{
		f->vec = ft_3v_subtract(f->dif_c, ft_3v_scalar(f->dir,
					ft_3v_dot_product(f->dif_c, f->dir)));
		f->val = ft_3v_dot_product(f->vec, f->vec);
	}
	if (o->type == 3)
		f->val_2 = ft_3v_dot_product(f->dif_c, f->dir);
	if (o->type == 5)
	{
		f->vec = ft_cross_product(ft_3v_subtract(o->origin_2, o->origin),
		 		ft_3v_subtract(o->origin_3, o->origin)); //the normal
		f->vec = normalize(f->vec);
		f->vec2 = origin; //used so that I can pass in the camera into get_t_triangle
		//f->val is the top value
		f->val = ft_3v_dot_product(f->vec, f->dif_c);
		f->vertex0 = o->origin;
		f->vertex1 = o->origin_2;
		f->vertex2 = o->origin_3;
		f->val_2 = ft_3v_area(f->vertex0, f->vertex1, f->vertex2) / 2; //the area of the triangle
	}
}

/*
 * Set fixed values for reflective and transparent points (work as new camera).
 */

void		set_value_refl(t_3v point, t_object *o, int r, int cam_id, int thread_id)
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
	if (first && !(o->fixed_s[scene->thread_id] = (t_fixed_v **)malloc(sizeof(t_fixed_v *)
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
			if (first && !(o->fixed_c[scene->thread_id] = (t_fixed_v **)malloc(sizeof(t_fixed_v *)
							* scene->cam_set)))
				error(1);
			if (!(o->fixed_c[scene->thread_id][cam->id] = (t_fixed_v *)malloc(sizeof(t_fixed_v))))
				error(1);
			set_fixed_value(cam->origin, o, o->fixed_c[scene->thread_id][(scene->cam)->id]);
			set_src(scene, o, first);
			objects = objects->next;
		}
		scene->thread_id++;
	}
	scene->thread_id = 0;
}
