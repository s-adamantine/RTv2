/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 13:38:46 by mpauw             #+#    #+#             */
/*   Updated: 2018/02/23 17:49:06 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_3v		get_r_origin(t_object *obj, t_3v *origin)
{
	t_3v	refl_o;
	int		i;

	if (!origin)
		return ((obj->rel_cam).origin);
	refl_o = *origin;
	i = 0;
	while (i < 3)
	{
		refl_o.v[i] = refl_o.v[i] - ((obj->origin).v)[i];
		i++;
	}
	i = 2;
	while (i >= 0)
	{
		ft_rotate_3v(&refl_o, i, -((obj->rotation).v)[i], 0);
		i--;
	}
	return (refl_o);
}

static t_object	*get_vis_obj(double *s_value, t_3v dir,
		t_list *objects, t_3v *origin)
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
		tmp = obj->f(obj, tmp_dir, get_r_origin(obj, origin));
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

static void		get_reflections(int r, t_pixel *p, t_scene *scene,
		t_3v dir)
{
	t_cam	origin;
	t_3v	refl_v;
	t_3v	tmp;

	if (r == scene->refl)
		return ;
	p->s_value[r] = MAX_S_VALUE;
//	printf("%f %f %f\n", dir.v[0], dir.v[1], dir.v[2]);
//	printf("%f %f %f\n\n", (p->point[r - 1]).v[0], (p->point[r - 1]).v[1], (p->point[r - 1]).v[2]);
	if (r > 0)
		p->vis_obj[r] = get_vis_obj(&(p->s_value[r]), dir, scene->objects, &(p->point[r - 1]));
	else
		p->vis_obj[r] = get_vis_obj(&(p->s_value[r]), dir, scene->objects, NULL);
	if (!(p->vis_obj[r]))
		return ;
	if (r > 0)
	{
		origin.origin = p->point[r - 1];
		origin.rotation = (p->vis_obj[r - 1])->rotation;
		p->point[r] = get_point(origin, dir, p->s_value[r]);
	}
	else
		p->point[r] = get_point(scene->camera, p->coor, p->s_value[r]);
	p->normal[r] = get_normal(p->vis_obj[r], p->point[r]);
	if ((p->vis_obj[r])->specular == 0)
		return ;
	tmp = p->normal[r];
	change_dir(&tmp, (p->vis_obj[r])->rotation);
	refl_v = get_reflection_vector(tmp, dir);
//	cohange_dir(&refl_v, (p->vis_obj[r])->rotation);
//	printf("%f %f %f\n", dir.v[0], dir.v[1], dir.v[2]);
//	printf("%f %f %f\n\n", refl_v.v[0], refl_v.v[1], refl_v.v[2]);
	get_reflections(r + 1, p, scene, refl_v);
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
