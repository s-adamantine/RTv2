/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refraction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroguszk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 11:37:43 by jroguszk          #+#    #+#             */
/*   Updated: 2018/06/15 11:37:44 by jroguszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	ft_swap_double(double *a, double *b)
{
	double	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

static double	ft_clamp(double min, double max, double x)
{
	if (x - min < 0.001)
		return (min);
	else if (x - max > 0.001)
		return (max);
	else
		return (x);
}

void	refraction(t_p_info	*pi, t_3v *dir, double entry_refraction, t_pixel *p, t_scene *scene)
{
	double	cosi;
	double	index;
	double	k;
	double	n1;
	double	n2;
	t_3v	n;

	n1 = entry_refraction;
	n2 = (pi->obj_m).refractive_index;
	n = ft_init_3v(pi->normal.v[0], pi->normal.v[1], pi->normal.v[2]);
	cosi = ft_clamp(-1.0, 1.0, ft_3v_dot_product(pi->normal, *dir));
	if (cosi < 0.0)
		cosi = cosi * -1.0;
	else
	{
		ft_swap_double(&n1, &n2);
		n = ft_3v_scalar(n, -1);
	}
	index = n1 / n2;
	k = 1.0 - index * index * (1.0 - cosi * cosi);
	fresnal(pi, n1, n2, cosi, k);
	if (k < 0.0)
	{
		*dir = get_reflection_vector(n, *dir);
		get_reflections(p, scene, *dir, 1, n1);
	}
	else
	{
		*dir = ft_3v_add(ft_3v_scalar(*dir, index),
			ft_3v_scalar(n, index * cosi - sqrt(k)));
		get_reflections(p, scene, *dir, 2, n1);
	}
}

void	fresnal(t_p_info *pi, double n1, double n2, double cosi, double cost)
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
		rs = ((n2 * cosi) - (n1 * cost))
			/ ((n2 * cosi) + (n1 * cost));
		rp = ((n1 * cosi) - (n2 * cost))
			/ ((n1 * cosi) + (n2 * cost));
		pi->fresnal_specular = (rs * rs + rp * rp) / 2;
		pi->fresnal_transparent = 1 - pi->fresnal_specular;
	}
}