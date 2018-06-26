/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_s_values.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 13:38:46 by mpauw             #+#    #+#             */
/*   Updated: 2018/06/26 11:30:34 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** Some preparations to get the first visible object for this pixel.
*/

static void		get_value(t_scene scene, t_pixel *p)
{
	t_3v		dir;
	t_object	*obj;
	t_3v		color;
	t_p_info	*pi;

	p->c_per_src[0] = ft_zero_3v();
	dir = p->coor;
	dir = normalize(rotate_v(dir, (scene.cam)->rotation));
	p->type = 0;
	p->index_refract = 1.0;
	get_reflections(p, scene, dir);
	pi = p->pi_arr[0];
	if (!(pi->vis_obj))
		return ;
	obj = pi->vis_obj;
	color = (pi->obj_m).color;
	p->c_per_src[0] = ft_init_3v((color.v)[0] * (pi->obj_m).ambient
			* scene.ambient, (color.v)[1] * (pi->obj_m).ambient * scene.ambient,
			(color.v)[2] * (pi->obj_m).ambient * scene.ambient);
}

/*
** Initializing all variables in t_pixel.
*/

static void		setup_pixel(t_pixel *p, t_scene scene, int i, int j)
{
	if (scene.refl < 0)
		scene.refl = 0;
	if (!(p->c_per_src = (t_3v *)malloc(sizeof(t_3v)
			* (scene.amount_light + 1))))
		error(1);
	if (!(p->pi_arr = (t_p_info **)malloc(sizeof(t_p_info *))))
		error(1);
	p->color = ft_zero_3v();
	p->amount_p = 0;
	p->amount_refl = 0;
	(scene.cam)->pixel_set[j + scene.width * scene.max_anti_a * i] = 1;
	(p->coor).v[0] = -(scene.width / 2);
	(p->coor).v[1] = (double)((double)j / scene.max_anti_a - scene.width
			/ 2.0);
	(p->coor).v[2] = (double)(scene.height / 2.0 - (double)i
			/ scene.max_anti_a);
	get_value(scene, p);
}

/*
** Looping through pixels (based on grain size), finding visible object(s) per
** pixel.
*/

void			*set_t_values(void *arg)
{
	t_pixel		*p;
	t_event		*e;
	int			i;
	int			j;
	int			factor;

	e = (t_event *)arg;
	factor = e->scene.max_anti_a;
	i = ((e->scene.height * factor / THREADS) * e->scene.thread_id);
	while (i < (e->scene.height * factor / THREADS) * (e->scene.thread_id + 1))
	{
		j = 0;
		while (j < e->scene.width * factor)
		{
			if (!(e->scene.cam)->pixel_set[j + i * e->scene.width * factor])
			{
				p = &((e->scene.cam)->p_array[j + i * e->scene.width * factor]);
				setup_pixel(p, e->scene, i, j);
			}
			j += e->scene.step_size;
		}
		i += e->scene.step_size;
	}
	(e->scene.cam)->init = 1;
	return (NULL);
}
