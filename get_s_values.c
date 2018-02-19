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

static t_object	*get_visible_object(double *s_value, double *int_2,  t_3v dir,
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
		tmp = obj->f(obj, tmp_dir, (obj->rel_cam).origin, int_2);
		if (tmp > 0.001 && tmp < *s_value)
		{
			*s_value = tmp;
			visible_object = obj;
		}
		objects = objects->next;
	}
	return (visible_object);
}

static void		get_reflections(int reflection, t_pixel *p, t_scene *scene,
		t_3v dir)
{
	t_list	*tmp;
	t_cam	origin;
	t_3v	normal;

	if (reflection == scene->refl)
		return ;
	tmp = scene->objects;
	p->s_value_r[reflection] = MAX_S_VALUE;
	p->vis_obj_r[reflection] = get_visible_object(&(p->s_value_r[reflection]),
			&(p->int_2_r[reflection]), dir, scene->objects);
	scene->objects = tmp;
	if (!(p->vis_obj_r[reflection]))
		return ;
	origin.origin = (p->point_r)[reflection - 1];
	origin.rotation = ft_zero_3v();
	p->point_r[reflection] = get_point(origin, dir, p->s_value_r[reflection]);
	normal = get_normal(p->vis_obj_r[reflection], p->point_r[reflection]);
	if ((p->vis_obj_r[reflection])->specular == 0)
		return ;
	get_reflections(reflection + 1, p, scene,
			get_reflection_vector(normal, dir));
}

static void		get_value(t_scene *scene, t_pixel *p)
{
	t_list		*tmp;
	t_3v		coor;
	t_3v		normal;
	t_object	*obj;

	p->s_value = MAX_S_VALUE;
	(p->coor).v[0] = -scene->width;
	coor = p->coor;
	tmp = scene->objects;
	change_dir(&coor, (scene->camera).rotation);
	p->vis_obj = get_visible_object(&(p->s_value), &(p->int_2),
			coor, scene->objects);
	scene->objects = tmp;
	if (!p->vis_obj)
		return ;
	p->point = get_point(scene->camera, p->coor, p->s_value); 
	p->vis_obj_r[0] = p->vis_obj;
	p->point_r[0] = p->point;
	p->s_value_r[0] = p->s_value;
	p->int_2_r[0] = p->int_2;
	normal = get_normal(p->vis_obj, p->point);
	if ((p->vis_obj)->specular > 0)
		get_reflections(1, p, scene, get_reflection_vector(normal, coor));
	obj = p->vis_obj;
	p->color = ft_init_3v(((obj->color).v)[0] * obj->ambient * scene->ambient,
			((obj->color).v)[1] * obj->ambient * scene->ambient,
			((obj->color).v)[2] * obj->ambient * scene->ambient);
}

static void		setup_pixel(t_pixel *pixel, t_scene scene)
{
	if (scene.refl < 1)
		scene.refl = 1;
	if (!(pixel->c_per_src = (t_3v *)malloc(sizeof(t_3v) * scene.amount_light)))
		error(1);
	if (!(pixel->vis_obj_r = (t_object **)malloc(sizeof(t_object *)
					* scene.refl)))
		error(1);
	if (!(pixel->s_value_r = (double *)malloc(sizeof(double) * scene.refl)))
		error(1);
	if (!(pixel->int_2_r = (double *)malloc(sizeof(double) * scene.refl)))
		error(1);
	if (!(pixel->point_r = (t_3v *)malloc(sizeof(t_3v) * scene.refl)))
		error(1);
	ft_bzero(pixel->c_per_src, sizeof(t_3v) * scene.amount_light);
	pixel->color = ft_zero_3v();
}

void			*get_s_values(void *arg)
{
	t_pixel		*pixel;
	t_scene		scene;
	int			i;
	int			j;

	i = 0;
	scene = ((t_event *)arg)->scene;
	while (i < scene.height)
	{
		j = 0;
		while (j < scene.width)
		{
			pixel = &((((t_event *)arg)->p_array)[j + scene.width * i]);
			setup_pixel(pixel, scene);
			(pixel->coor).v[1] = (double)(j - scene.width / 2.0);
			(pixel->coor).v[2] = (double)(scene.height / 2.0 - i);
			get_value(&scene, pixel);
			j++;
		}
		i++;
	}
	return (NULL);
}
