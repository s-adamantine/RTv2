/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 13:38:46 by mpauw             #+#    #+#             */
/*   Updated: 2018/04/18 11:51:11 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_object	*get_vis_obj(t_pixel *p, t_3v dir,
		t_scene *scene, t_p_info *pi)
{
	double		tmp;
	t_list		*tmp_obj;
	t_object	*obj;
	t_object	*visible_object;

	visible_object = NULL;
	tmp_obj = scene->objects;
	while (tmp_obj && tmp_obj->content)
	{
		obj = (t_object *)tmp_obj->content;
		if (p->amount_p > 0)
			set_value_refl((p->pi_arr[p->amount_p - 1])->point, obj,
					p->amount_p, (scene->cam)->id);
		tmp = obj->f(obj->fixed_c[(scene->cam)->id][p->amount_p], dir, 0);
		if (tmp > 0.001 && tmp < pi->s_value)
		{
			pi->s_value = tmp;
			visible_object = obj;
		}
		tmp_obj = tmp_obj->next;
	}
	return (visible_object);
}

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
	pi->point = get_point(cam, dir, pi->s_value);
	pi->normal = get_normal(pi->vis_obj, pi->point);
	(p->amount_p)++;
	if ((pi->vis_obj)->specular > 0.001 && p->amount_p < scene->refl)
	{
		n_dir = get_reflection_vector(pi->normal, dir);
		get_reflections(p, scene, n_dir, 1);
	}
	if ((pi->vis_obj)->transparent > 0.001)
		get_reflections(p, scene, dir, 2);
}

static void		get_value(t_scene *scene, t_pixel *p)
{
	t_3v		dir;
	t_object	*obj;
	t_p_info	*pi;

	dir = p->coor;
	dir = normalize(get_dir(dir, (scene->cam)->rotation));
	get_reflections(p, scene, dir, 0);
	pi = p->pi_arr[0];
	if (!(pi->vis_obj))
		return ;
	obj = pi->vis_obj;
	p->color = ft_init_3v(((obj->color).v)[0] * obj->ambient * scene->ambient,
			((obj->color).v)[1] * obj->ambient * scene->ambient,
			((obj->color).v)[2] * obj->ambient * scene->ambient);
	p->c_per_src[0] = p->color;
}

static void		setup_pixel(t_pixel *pixel, t_scene scene)
{
	if (scene.refl < 1)
		scene.refl = 1;
	if (!(pixel->c_per_src = (t_3v *)malloc(sizeof(t_3v)
					* (scene.amount_light + 1))))
		error(1);
	if (!(pixel->pi_arr = (t_p_info **)malloc(sizeof(t_p_info *))))
		error(1);
	ft_bzero(pixel->c_per_src, sizeof(t_3v) * scene.amount_light);
	pixel->color = ft_zero_3v();
	pixel->amount_p = 0;
	(pixel->coor).v[0] = -(scene.width / 2);
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
			pixel = &((scene.cam)->p_array[j + scene.width * i]);
			setup_pixel(pixel, scene);
			(pixel->coor).v[1] = (double)(j - scene.width / 2.0);
			(pixel->coor).v[2] = (double)(scene.height / 2.0 - i);
			get_value(&scene, pixel);
			((int *)(((t_event *)arg)->img).img_arr)
				[j + scene.width * i] = get_color(pixel->color);
			j++;
		}
		i++;
	}
	(scene.cam)->init = 1;
	return (NULL);
}
