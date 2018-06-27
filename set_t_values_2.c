/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_t_values_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 10:15:04 by mpauw             #+#    #+#             */
/*   Updated: 2018/06/27 14:51:26 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** Gets the visible object (first, or through transparency or reflection). The
** first if makes sure the fixed values are set for transparency and reflection.
*/

static void		get_vis_obj(t_pixel *p, t_3v dir, t_scene sc, t_p_info *pi)
{
	double		tmp;
	int			var[3];
	t_list		*tmp_obj;
	t_object	*obj;
	t_object	*visible_object;

	visible_object = NULL;
	tmp_obj = sc.objects;
	pi->has_vis_obj = 0;
	while (tmp_obj && tmp_obj->content)
	{
		obj = (t_object *)tmp_obj->content;
		set_var(var, p->amount_p, (sc.cam)->id, sc.thread_id);
		if (p->amount_p > 0)
			set_value_refl((p->pi_arr[p->amount_p - 1])->point, obj, var);
		tmp = obj->f(obj->fixed_c[sc.thread_id][(sc.cam)->id][p->amount_p],
				dir, 0, obj);
		if (tmp > 0.001 && tmp < pi->s_value)
		{
			pi->s_value = tmp;
			pi->has_vis_obj = 1;
			pi->vis_obj = obj;
		}
		tmp_obj = tmp_obj->next;
	}
}

/*
** t_p_info contains information for every object visible at a certain pixel.
** This function dynamically allocates memory, because we don't know in advance
** how many objects will be visible.
*/

static t_p_info	*init_p_info(t_pixel *p, t_3v dir, t_scene scene, int type)
{
	t_p_info	*pi;
	t_p_info	**tmp;
	int			i;

	if (!(tmp = (t_p_info **)malloc(sizeof(t_p_info *) * (p->amount_p + 1))))
		error(1);
	i = -1;
	while (++i < p->amount_p)
		tmp[i] = p->pi_arr[i];
	free(p->pi_arr);
	p->pi_arr = tmp;
	if (!(p->pi_arr[p->amount_p] = (t_p_info *)malloc(sizeof(t_p_info))))
		error(1);
	pi = p->pi_arr[p->amount_p];
	pi->s_value = MAX_S_VALUE;
	get_vis_obj(p, dir, scene, pi);
	pi->type = type;
	pi->fresnal_transparent = 1.0;
	pi->fresnal_specular = 1.0;
	pi->is_inside = 0;
	if (!(pi->has_vis_obj))
		return (NULL);
	pi->beer = ft_init_3v(pi->vis_obj->m.beer.v[0],
		pi->vis_obj->m.beer.v[1], pi->vis_obj->m.beer.v[2]);
	return (pi);
}

static void		refrect_or_reflect(t_pixel *p, t_scene scene, t_3v dir,
		t_p_info *pi)
{
	t_3v		n_dir;

	if (((pi->vis_obj)->m).transparent > 0.001 && p->amount_p < 6)
		refraction(pi, &dir, p, scene);
	if ((((pi->vis_obj)->m).specular > 0.001 && p->amount_refl < scene.refl))
	{
		n_dir = get_reflection_vector(pi->normal, dir);
		p->type = 1;
		get_reflections(p, scene, n_dir);
	}
}

/*
** Recursively called function to determine all visible objects. Stops when
** there is no visible object or the object isn't reflective or transparent.
*/

void			get_reflections(t_pixel *p, t_scene scene, t_3v dir)
{
	t_cam		cam;
	t_p_info	*pi;
	t_p_info	*pi_prev;

	pi = init_p_info(p, dir, scene, p->type);
	if (!pi)
		return ;
	pi_prev = (p->amount_p > 0) ? p->pi_arr[p->amount_p - 1] : NULL;
	cam.origin = (p->amount_p > 0) ? pi_prev->point : (scene.cam)->origin;
	cam.rotation = (p->amount_p > 0) ? (pi_prev->vis_obj)->rotation :
		(scene.cam)->rotation;
	pi->point = get_point(cam.origin, dir, pi->s_value);
	pi->normal = get_normal(pi->vis_obj, pi->point);
	pi->obj_m = get_object_material(*(pi->vis_obj), pi->point, scene);
	(p->amount_p)++;
	if (p->type == 1)
		(p->amount_refl)++;
	if ((pi->s_value > 0.001 && pi->s_value < 1.0)
		|| (pi_prev != NULL && (pi_prev->vis_obj)->id != (pi->vis_obj)->id))
		p->index_refract = ((pi->vis_obj)->m).refractive_index;
	else
		p->index_refract = 1.0;
	refrect_or_reflect(p, scene, dir, pi);
}
