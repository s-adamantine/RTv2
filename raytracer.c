/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 13:38:46 by mpauw             #+#    #+#             */
/*   Updated: 2018/02/02 12:08:52 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_object	*get_visible_object(double *s_value, t_3v dir, int src_id,
		t_list *objects)
{
	double		tmp;
	t_object	*obj;
	t_object	*visible_object;
	t_source	*src;
	t_3v		tmp_dir;

	visible_object = NULL;
	while (objects && objects->content)
	{
		obj = (t_object *)objects->content;
		tmp_dir = get_dir(dir, obj->rotation);
		if (src_id == 0)
			src = &(obj->rel_cam);
		else
			src = get_source(src_id, obj->rel_lights);
		tmp = obj->f(obj, tmp_dir, src->origin);
		if (tmp > 0 && tmp < *s_value)
		{
			*s_value = tmp;
			visible_object = obj;
		}
		objects = objects->next;
	}
	return (visible_object);
}

static void		get_pixel_value(t_scene *scene, t_3v pixel, int *pix_v)
{
	t_list		*tmp;
	t_source	cam;
	double		s_value;
	t_object	*obj;
	t_3v		point;

	tmp = scene->objects;
	s_value = MAX_S_VALUE;
	cam = scene->camera;
	(pixel.v)[0] -= ((cam.origin).v)[0];
	(pixel.v)[1] -= ((cam.origin).v)[1];
	(pixel.v)[2] -= ((cam.origin).v)[2];
	change_dir(&pixel, (scene->camera).rotation);
	obj = get_visible_object(&s_value, pixel, 0, scene->objects);
	scene->objects = tmp;
	if (obj)
	{
		point = cam.origin;
		ft_3v_scalar(&pixel, s_value);
		(point.v)[0] += (pixel.v)[0];
		(point.v)[1] += (pixel.v)[1];
		(point.v)[2] += (pixel.v)[2];
		*pix_v = (get_light_value(point, scene, scene->lights, obj));
	}
}

void			raytracer(t_event *event, t_scene *scene)
{
	t_img		*img;
	t_3v		pixel;
	int			i;
	int			j;
	int			pix_val;

	img = event->img;
	i = -1;
	while (++i < img->height)
	{
		j = -1;
		while (++j < img->width)
		{
			pix_val = BG_COLOR;
			(pixel.v)[0] = 0.0;
			(pixel.v)[1] = (double)(j - img->width / 2.0);
			(pixel.v)[2] = (double)(img->height / 2.0 - i);
			get_pixel_value(scene, pixel, &pix_val);
			((int *)img->img_arr)[j + i * img->size_line_int] = pix_val;
		}
	}
}
