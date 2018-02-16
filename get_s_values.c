/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 13:38:46 by mpauw             #+#    #+#             */
/*   Updated: 2018/02/07 15:58:53 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_object	*get_visible_object(double *s_value, t_3v dir,
		t_list *objects)
{
	double		tmp;
	double		size;
	t_object	*obj;
	t_object	*visible_object;
	t_3v		tmp_dir;

	visible_object = NULL;
	while (objects && objects->content)
	{
		obj = (t_object *)objects->content;
		tmp_dir = get_dir(dir, obj->rotation);
		size = ft_get_3v_size(tmp_dir);
		if (size == 0)
			error(5);
		tmp = obj->f(obj, tmp_dir, (obj->rel_cam).origin);
		if (tmp > 0 && tmp < *s_value)
		{
			*s_value = tmp;
			visible_object = obj;
		}
		objects = objects->next;
	}
	return (visible_object);
}

static void		get_value(t_scene *scene, t_pixel *p)
{
	t_list		*tmp;
	t_cam		cam;
	t_3v		coor;
	t_object	*obj;

	p->color = ft_zero_3v();
	p->s_value = MAX_S_VALUE;
	(p->coor).v[0] = -scene->width;
	coor = p->coor;
	tmp = scene->objects;
	cam = scene->camera;
	change_dir(&coor, (scene->camera).rotation);
	p->vis_obj = get_visible_object(&(p->s_value), coor, scene->objects);
	scene->objects = tmp;
	if (!p->vis_obj)
		return ;
	obj = p->vis_obj;
	p->color = ft_init_3v(((obj->color).v)[0] * obj->ambient * scene->ambient,
			((obj->color).v)[1] * obj->ambient * scene->ambient,
			((obj->color).v)[2] * obj->ambient * scene->ambient);
}

void			*get_s_values(void *event)
{
	t_pixel		*pixel;
	t_scene		scene;
	int			i;
	int			j;

	i = 0;
	scene = ((t_event *)event)->scene;
	while (i < scene.height)
	{
		j = 0;
		while (j < scene.width)
		{
			pixel = &((((t_event *)event)->p_array)[j + scene.width * i]);
			(pixel->coor).v[1] = (double)(j - scene.width / 2.0);
			(pixel->coor).v[2] = (double)(scene.height / 2.0 - i);
			get_value(&scene, pixel);
			((int *)(((t_event *)event)->img)->img_arr)[j + scene.width * i] =
				get_color(pixel->color);
			pixel->status = 1;
			j++;
		}
		i++;
	}
	return (NULL);
}
