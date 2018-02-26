/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 13:38:46 by mpauw             #+#    #+#             */
/*   Updated: 2018/02/26 15:06:29 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_3v		get_r_origin(t_object *obj, t_cam *cam)
{
	t_3v	refl_o;

	if (!cam)
		return ((obj->rel_cam).origin);
	refl_o = get_rel_origin(cam->origin, obj);
	change_dir(&refl_o, obj->rotation);
	return (refl_o);
}

static t_object	*get_vis_obj(double *s_value, t_3v dir,
		t_list *objects, t_cam *cam)
{
	double		tmp;
	t_list		*tmp_obj;
	t_object	*obj;
	t_object	*visible_object;
	t_3v		tmp_dir;

	visible_object = NULL;
	tmp_obj = objects;
	while (objects && objects->content)
	{
		obj = (t_object *)objects->content;
		tmp_dir = get_dir(dir, obj->rotation);
		if (ft_get_3v_size(tmp_dir) == 0)
			error(5);
		tmp = obj->f(obj, tmp_dir, get_r_origin(obj, cam));
		if (tmp > 0.001 && tmp < *s_value)
		{
			*s_value = tmp;
			visible_object = obj;
		}
		objects = objects->next;
	}
	objects = tmp_obj;
	return (visible_object);
}

static void		get_reflections(int r, t_pixel *p, t_scene *scene, t_3v dir)
{
	t_cam	cam;

	if (r == scene->refl)
		return ;
	p->s_value[r] = MAX_S_VALUE;
	cam.origin = (r > 0) ? p->point[r - 1] : (scene->camera).origin;
	cam.rotation = (r > 0) ? ft_zero_3v() : (scene->camera).rotation;
	p->vis_obj[r] = get_vis_obj(&(p->s_value[r]), dir, scene->objects, &cam);
	if (!(p->vis_obj[r]))
		return ;
	if (r > 0)
		p->point[r] = get_point(cam, dir, p->s_value[r]);
	else
		p->point[r] = get_point(scene->camera, p->coor, p->s_value[r]);
	p->normal[r] = get_normal(p->vis_obj[r], p->point[r]);
	if ((p->vis_obj[r])->specular > -0.001 && (p->vis_obj[r])->specular < 0.001)
		return ;
	get_reflections(r + 1, p, scene, get_reflection_vector(get_dir(p->normal[r],
					(p->vis_obj[r])->rotation), dir));
}

static void		get_value(t_scene *scene, t_pixel *p)
{
	t_3v		coor;
	t_object	*obj;

	coor = p->coor;
	change_dir(&coor, (scene->camera).rotation);
	get_reflections(0, p, scene, coor);
	if (!p->vis_obj[0])
		return ;
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
	ft_bzero(pixel->point, sizeof(t_3v *) * scene.refl);
	pixel->color = ft_zero_3v();
	(pixel->coor).v[0] = -scene.width;
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
