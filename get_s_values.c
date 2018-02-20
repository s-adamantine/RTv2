/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 13:38:46 by mpauw             #+#    #+#             */
/*   Updated: 2018/02/20 18:57:43 by mpauw            ###   ########.fr       */
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
		if (tmp > 0.001 && tmp < *s_value)
		{
			*s_value = tmp;
			visible_object = obj;
		}
		objects = objects->next;
	}
	return (visible_object);
}

static void		get_reflections(int refl, t_pixel *p, t_scene *scene,
		t_3v dir)
{
	t_list	*tmp;
	t_cam	origin;

	if (refl == scene->refl)
		return ;
	tmp = scene->objects;
	p->s_value[refl] = MAX_S_VALUE;
	p->vis_obj[refl] = get_visible_object(&(p->s_value[refl]),
			dir, scene->objects);
	scene->objects = tmp;
	if (!(p->vis_obj[refl]))
		return ;
	origin.origin = (p->point)[refl - 1];
	origin.rotation = ft_zero_3v();
	p->point[refl] = get_point(origin, dir, p->s_value[refl]);
	p->normal[refl] = get_normal(p->vis_obj[refl], p->point[refl]);
	if ((p->vis_obj[refl])->specular == 0)
		return ;
	get_reflections(refl + 1, p, scene,
			get_reflection_vector(p->normal[refl], dir));
}

static void		get_value(t_scene *scene, t_pixel *p)
{
	t_list		*tmp;
	t_3v		coor;
	t_object	*obj;

	(p->coor).v[0] = -scene->width;
	coor = p->coor;
	tmp = scene->objects;
	change_dir(&coor, (scene->camera).rotation);
	p->s_value[0] = MAX_S_VALUE;
	p->vis_obj[0] = get_visible_object(&(p->s_value[0]), coor, scene->objects);
	scene->objects = tmp;
	if (!p->vis_obj[0])
		return ;
	p->point[0] = get_point(scene->camera, p->coor, p->s_value[0]); 
	p->normal[0] = get_normal(p->vis_obj[0], p->point[0]);
	if ((p->vis_obj[0])->specular > 0)
		get_reflections(1, p, scene, get_reflection_vector(p->normal[0], coor));
	obj = p->vis_obj[0];
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
	if (!(pixel->vis_obj = (t_object **)malloc(sizeof(t_object *)
					* scene.refl)))
		error(1);
	if (!(pixel->s_value = (double *)malloc(sizeof(double) * scene.refl)))
		error(1);
	if (!(pixel->point = (t_3v *)malloc(sizeof(t_3v) * scene.refl)))
		error(1);
	if (!(pixel->normal = (t_3v *)malloc(sizeof(t_3v) * scene.refl)))
		error(1);
	ft_bzero(pixel->c_per_src, sizeof(t_3v) * scene.amount_light);
	ft_bzero(pixel->vis_obj, sizeof(t_object *) * scene.refl);
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
