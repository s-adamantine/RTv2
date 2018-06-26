/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refraction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroguszk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 11:37:43 by jroguszk          #+#    #+#             */
/*   Updated: 2018/06/26 11:51:19 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		beer(t_p_info *pi)
{
	if (pi->beer.v[0] < 0.99 && pi->beer.v[1] < 0.99 && pi->beer.v[2] < 0.99)
	{
		pi->beer = ft_3v_scalar(pi->beer, -1.0);
		pi->beer.v[0] = (exp(pi->beer.v[0] * (pi->s_value / 70)));
		pi->beer.v[1] = (exp(pi->beer.v[1] * (pi->s_value / 70)));
		pi->beer.v[2] = (exp(pi->beer.v[2] * (pi->s_value / 70)));
	}
}

static void		fresnal(t_p_info *pi, double *n_value, double cosi,
		double cost)
{
	double	rs;
	double	rp;

	if (cost < 0.0)
	{
		pi->fresnal_specular = 1.0;
		pi->fresnal_transparent = 0.0;
	}
	else
	{
		rs = ((n_value[1] * cosi) - (n_value[0] * cost))
			/ ((n_value[1] * cosi) + (n_value[0] * cost));
		rp = ((n_value[0] * cosi) - (n_value[1] * cost))
			/ ((n_value[0] * cosi) + (n_value[1] * cost));
		pi->fresnal_specular = (rs * rs + rp * rp) / 2;
		pi->fresnal_transparent = 1 - pi->fresnal_specular;
	}
}

static void		call_recursion(t_scene scene, t_pixel *p, t_3v *dir,
		double *n_value)
{
	if (n_value[2] < 0.0)
	{
		if (p->amount_refl < scene.refl)
		{
			p->type = 1;
			p->index_refract = n_value[0];
			get_reflections(p, scene, *dir);
		}
	}
	else
	{
		p->type = 2;
		p->index_refract = n_value[0];
		get_reflections(p, scene, *dir);
	}
}

void			refraction(t_p_info *pi, t_3v *dir, t_pixel *p, t_scene scene)
{
	double	cosi;
	double	index;
	double	n_value[3];
	t_3v	n;

	n_value[0] = p->index_refract;
	n_value[1] = (pi->obj_m).refractive_index;
	n = ft_init_3v(pi->normal.v[0], pi->normal.v[1], pi->normal.v[2]);
	cosi = ft_clamp(-1.0, 1.0, ft_3v_dot_product(pi->normal, *dir));
	if (cosi < 0.0)
		cosi = cosi * -1.0;
	else
	{
		pi->is_inside = 1;
		ft_swap_double(&n_value[0], &n_value[1]);
		n = ft_3v_scalar(n, -1);
		beer(pi);
	}
	index = n_value[0] / n_value[1];
	n_value[2] = 1 - index * index * (1.0 - cosi * cosi);
	fresnal(pi, n_value, cosi, n_value[2]);
	*dir = (n_value[2] < 0.0) ? get_reflection_vector(n, *dir) :
		ft_3v_add(ft_3v_scalar(*dir, index), ft_3v_scalar(n, index * cosi
					- sqrt(n_value[2])));
	call_recursion(scene, p, dir, n_value);
}
