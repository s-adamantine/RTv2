/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fixed_values.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 13:49:54 by mpauw             #+#    #+#             */
/*   Updated: 2018/03/21 17:44:31 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	set_fixed_values_src(t_source *src, t_object *s, int i)
{
	s->dif_c[i] = ft_3v_subtract(src->origin, s->origin);
	if (s->type == 0)
		s->fixed_value[i] = ft_3v_dot_product(s->normal, s->dif_c[i]);
	else if (s->type == 1)
		s->fixed_value[i] = ft_3v_dot_product(s->dif_c[i], s->dif_c[i]);
	else if (s->type == 2 || s->type == 3)
	{
		s->fixed_vec[i] = ft_3v_subtract(s->dif_c[i],
				ft_3v_scalar(s->rotation,
					ft_3v_dot_product(s->dif_c[i], s->rotation)));
		s->fixed_value[i] =
			ft_3v_dot_product(s->fixed_vec[i], s->fixed_vec[i]);
	}
	if (s->type == 3)
		s->fixed_value_2[i] = ft_3v_dot_product(s->dif_c[i], s->rotation);
}

static void	set_fixed_value_cam(t_scene *scene, t_object *s)
{
	s->dif_c[0] = ft_3v_subtract((scene->camera).origin, s->origin);
	s->radius_sq = s->radius * s->radius;
	if (s->type == 0)
		s->fixed_value[0] = ft_3v_dot_product(s->normal, s->dif_c[0]);
	else if (s->type == 1)
		s->fixed_value[0] = ft_3v_dot_product(s->dif_c[0], s->dif_c[0]);
	else if (s->type == 2 || s->type == 3)
	{
		s->fixed_vec[0] = ft_3v_subtract(s->dif_c[0],
				ft_3v_scalar(s->rotation,
					ft_3v_dot_product(s->dif_c[0], s->rotation)));
		s->fixed_value[0] =
			ft_3v_dot_product(s->fixed_vec[0], s->fixed_vec[0]);
	}
	if (s->type == 3)
		s->fixed_value_2[0] = ft_3v_dot_product(s->dif_c[0], s->rotation);
}

static void	set_src(t_scene *scene, t_object *s)
{
	t_list		*srcs;
	t_source	*src;
	int			i;

	srcs = scene->lights;
	i = 1;
	while (srcs && srcs->content)
	{
		src = (t_source *)srcs->content;
		set_fixed_values_src(src, s, i);
		srcs = srcs->next;
		i++;
	}
}

void	set_fixed_values(t_scene *scene)
{
	t_list		*objects;
	t_object	*s;
	int			l;

	objects = scene->objects;
	l = scene->amount_light + 1;
	while (objects && objects->content)
	{
		s = (t_object *)objects->content;
		if (!((s->fixed_value = (double *)malloc(l * sizeof(double))) &&
				(s->fixed_value_2 = (double *)malloc(l * sizeof(double))) &&
			(s->fixed_vec = (t_3v *)malloc(l * sizeof(t_3v))) &&
			(s->dif_c = (t_3v *)malloc(l * sizeof(t_3v)))))
			error(1);
		set_fixed_value_cam(scene, s);
		set_src(scene, s);
		objects = objects->next;
	}
}
