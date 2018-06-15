/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_s_values.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 13:38:46 by mpauw             #+#    #+#             */
/*   Updated: 2018/06/15 17:33:15 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
 * Gets the visible object (first, or through transparency or reflection). The
 * first if makes sure the fixed values are set for transparency and reflection.
 */

static t_object	*get_vis_obj(t_pixel *p, t_3v dir,
		t_scene *sc, t_p_info *pi)
{
	double		tmp;
	t_list		*tmp_obj;
	t_object	*obj;
	t_object	*visible_object;

	visible_object = NULL;
	tmp_obj = sc->objects;
	while (tmp_obj && tmp_obj->content)
	{
		obj = (t_object *)tmp_obj->content;
		if (p->amount_p > 0)
			set_value_refl((p->pi_arr[p->amount_p - 1])->point, obj,
					p->amount_p, (sc->cam)->id, sc->thread_id);
		tmp = obj->f(obj->fixed_c[sc->thread_id][(sc->cam)->id][p->amount_p], dir, 0, obj);
		if (tmp > 0.001 && tmp < pi->s_value)
		{
			pi->s_value = tmp;
			visible_object = obj;
		}
		tmp_obj = tmp_obj->next;
	}
	return (visible_object);
}

/*
 * t_p_info contains information for every object visible at a certain pixel. 
 * This function dynamically allocates memory, because we don't know in advance
 * how many objects will be visible.
 */

static t_p_info	*init_p_info(t_pixel *p, t_3v dir, t_scene *scene, int type)
{
	t_p_info	*pi;
	t_p_info	**tmp;
	int			i;

	if (!(tmp = (t_p_info **)malloc(sizeof(t_p_info *) * (p->amount_p + 1))))
		error (1);
	i = -1;
	while (++i < p->amount_p)
		tmp[i] = p->pi_arr[i];
	free(p->pi_arr);
	p->pi_arr = tmp;
	if (!(p->pi_arr[p->amount_p] = (t_p_info *)malloc(sizeof(t_p_info))))
		error (1);
	pi = p->pi_arr[p->amount_p];
	pi->s_value = MAX_S_VALUE;
	pi->vis_obj = get_vis_obj(p, dir, scene, pi);
	pi->type = type;
	if (!(pi->vis_obj))
	{
		free(pi);
		return (NULL);
	}
	return (pi);
}

/*
 * Recursively called function to determine all visible objects. Stops when
 * there is no visible object or the object isn't reflective or transparent.
 */

static void		get_reflections(t_pixel *p, t_scene *scene, t_3v dir, int type)
{
	t_cam		cam;
	t_3v		n_dir;
	t_p_info	*pi;
	t_p_info	*pi_prev;

	pi = init_p_info(p, dir, scene, type);
	if (!pi)
		return ;
	pi_prev = (p->amount_p > 0) ? p->pi_arr[p->amount_p - 1] : NULL;
	cam.origin = (p->amount_p > 0) ? pi_prev->point : (scene->cam)->origin;
	cam.rotation = (p->amount_p > 0) ? (pi_prev->vis_obj)->rotation :
		(scene->cam)->rotation;
	pi->point = get_point(cam.origin, dir, pi->s_value);
	pi->normal = get_normal(pi->vis_obj, pi->point);
	pi->obj_m = get_object_material(*(pi->vis_obj), pi->point);
	(p->amount_p)++;
	if (((pi->vis_obj)->m).specular > 0.001 && p->amount_p < scene->refl)
	{
		n_dir = get_reflection_vector(pi->normal, dir);
		get_reflections(p, scene, n_dir, 1);
	}
	if (((pi->vis_obj)->m).transparent > 0.001)
		get_reflections(p, scene, dir, 2);
}

/*
 * Some preparations to get the first visible object for this pixel. 
 */

static void		get_value(t_scene *scene, t_pixel *p)
{
	t_3v		dir;
	t_object	*obj;
	t_3v		color;
	t_p_info	*pi;

	p->c_per_src[0] = ft_zero_3v();
	dir = p->coor;
	dir = normalize(rotate_v(dir, (scene->cam)->rotation));
	get_reflections(p, scene, dir, 0);
	pi = p->pi_arr[0];
	if (!(pi->vis_obj))
		return ;
	obj = pi->vis_obj;
	color = (pi->obj_m).color;
	p->color = ft_init_3v((color.v)[0] * (obj->m).ambient * scene->ambient,
			(color.v)[1] * (obj->m).ambient * scene->ambient,
			(color.v)[2] * (obj->m).ambient * scene->ambient);
	p->c_per_src[0] = p->color;
}

/*
 * Initializing all variables in t_pixel.
 */

static void		setup_pixel(t_pixel *p, t_scene scene, int i, int j, int factor)
{
	if (scene.refl < 1)
		scene.refl = 1;
	if ((scene.cam)->pixel_set[j + i * scene.width * factor])
	{
		free(p->c_per_src);
		free(p->pi_arr);
	}
	if (!(p->c_per_src = (t_3v *)malloc(sizeof(t_3v)
			* (scene.amount_light + 1))))
		error(1);
	if (!(p->pi_arr = (t_p_info **)malloc(sizeof(t_p_info *))))
		error(1);
	p->color = ft_zero_3v();
	p->amount_p = 0;
	(scene.cam)->pixel_set[j + scene.width * factor * i] = 1;
	(p->coor).v[0] = -(scene.width / 2);
	(p->coor).v[1] = (double)((double)j / factor - scene.width / 2.0);
	(p->coor).v[2] = (double)(scene.height / 2.0 - (double)i / factor);
}

/*
 * Looping through pixels (based on grain size), finding visible object(s) per
 * pixel.
 */

void			*set_t_values(void *arg)
{
	t_pixel		*p;
	t_event		*e;
	int			i;
	int			j;
	int			factor;

	e = (t_event*)arg;
	factor = e->scene.max_anti_a;
	i = ((e->scene.height * factor / THREADS) * e->scene.thread_id);
	while (i < (e->scene.height * factor / THREADS)  * (e->scene.thread_id + 1))
	{
		j = 0;
		while (j < e->scene.width * factor)
		{
			if (!(e->scene.cam)->pixel_set[j + i * e->scene.width * factor])
			{
				p = &((e->scene.cam)->p_array[j + i * e->scene.width * factor]);
				setup_pixel(p, e->scene, i, j, factor);
				get_value(&e->scene, p);
			}
			j += e->scene.step_size;
		}
		i += e->scene.step_size;
	}
	(e->scene.cam)->init = 1;
	return (NULL);
}
