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

static void	set_fixed_value(t_3v origin, t_object *o, int i)
{
	if (i == 0)
	{
		o->dir = get_dir(o->dir, o->rotation);
		o->radius_sq = o->radius * o->radius;
	}
	o->dif_c[i] = ft_3v_subtract(origin, o->origin);
	if (o->type == 0)
		o->fixed_value[i] = ft_3v_dot_product(o->dir, o->dif_c[i]);
	else if (o->type == 1)
		o->fixed_value[i] = ft_3v_dot_product(o->dif_c[i], o->dif_c[i]);
	else if (o->type == 2 || o->type == 3)
	{
		o->fixed_vec[i] = ft_3v_subtract(o->dif_c[i],
				ft_3v_scalar(o->dir,
					ft_3v_dot_product(o->dif_c[i], o->dir)));
		o->fixed_value[i] =
			ft_3v_dot_product(o->fixed_vec[i], o->fixed_vec[i]);
	}
	if (o->type == 3)
		o->fixed_value_2[i] = ft_3v_dot_product(o->dif_c[i], o->dir);
}

void		set_value_refl(t_3v point, t_object *o, int r)
{
	set_fixed_value(point, o, r);
}

static void	set_src(t_scene *scene, t_object *o)
{
	t_list		*srcs;
	t_source	*src;
	int			i;

	i = scene->refl;
	srcs = scene->lights;
	while (srcs && srcs->content)
	{
		src = (t_source *)srcs->content;
		if (src->type)
		{
			set_fixed_value(src->origin, o, i + scene->amount_fixed *
					(scene->cam)->id);
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

	l = (scene->amount_light + scene->refl + 1) * scene->cam_set;
	scene->amount_fixed = scene->amount_light + scene->refl + 1;
	objects = scene->objects;
	cam = scene->cam;
	while (objects && objects->content)
	{
		o = (t_object *)objects->content;
		if ((scene->cam)->id == 0 && 
				!((o->fixed_value = (double *)malloc(l * sizeof(double))) &&
				(o->fixed_value_2 = (double *)malloc(l * sizeof(double))) &&
				(o->fixed_vec = (t_3v *)malloc(l * sizeof(t_3v))) &&
				(o->dif_c = (t_3v *)malloc(l * sizeof(t_3v)))))
			error(1);
		set_fixed_value(cam->origin, o, scene->amount_fixed * cam->id);
		set_src(scene, o);
		objects = objects->next;
	}
}
