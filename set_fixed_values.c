/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fixed_values.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 13:49:54 by mpauw             #+#    #+#             */
/*   Updated: 2018/03/22 16:53:35 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	set_fixed_value(t_3v origin, t_object *o, t_fixed_v *f)
{
	f->dir = get_dir(ft_init_3v(0.0, 0.0, 1.0), o->rotation);
	f->rad = o->radius;
	f->rad_sq = o->radius * o->radius;
	f->dif_c = ft_3v_subtract(origin, o->origin);
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
}

void		set_value_refl(t_3v point, t_object *o, int r, int cam_id)
{
	t_fixed_v	*tmp;
	int			i;

	if (!(tmp = (t_fixed_v *)malloc(sizeof(t_fixed_v) * (r + 1))))
		error(1);
	i = 0;
	while (i < r)
	{
		tmp[i] = o->fixed_c[cam_id][i];
		i++;
	}
	free(o->fixed_c[cam_id]);
	o->fixed_c[cam_id] = tmp;
	set_fixed_value(point, o, &(o->fixed_c[cam_id][r]));
}

static void	set_src(t_scene *scene, t_object *o, int first)
{
	t_list		*srcs;
	t_source	*src;
	int			i;

	i = 0;
	srcs = scene->lights;
	if (first && !(o->fixed_s = (t_fixed_v **)malloc(sizeof(t_fixed_v *)
				* scene->cam_set)))
		error(1);
	if (!(o->fixed_s[(scene->cam)->id] =
				(t_fixed_v *)malloc(sizeof(t_fixed_v) * scene->amount_light)))
		error(1);
	while (srcs && srcs->content)
	{
		src = (t_source *)srcs->content;
		if (src->type)
		{
			set_fixed_value(src->origin, o,
					&(o->fixed_s[(scene->cam)->id][i]));
			i++;
		}
		srcs = srcs->next;
	}
}

void		set_fixed_values(t_scene *scene)
{
	t_list		*objects;
	t_object	*o;
	t_cam		*cam;
	int			l;
	int			first;

	l = (scene->amount_light + scene->refl + 1) * scene->cam_set;
	objects = scene->objects;
	cam = scene->cam;
	first = (((t_cam *)(scene->cameras)->content)->init + 1) % 2;
	while (objects && objects->content)
	{
		o = (t_object *)objects->content;
		if (first && !(o->fixed_c = (t_fixed_v **)malloc(sizeof(t_fixed_v *)
						* scene->cam_set)))
			error(1);
		if (!(o->fixed_c[cam->id] = (t_fixed_v *)malloc(sizeof(t_fixed_v))))
			error(1);
		set_fixed_value(cam->origin, o, o->fixed_c[(scene->cam)->id]);
		set_src(scene, o, first);
		objects = objects->next;
	}
}
