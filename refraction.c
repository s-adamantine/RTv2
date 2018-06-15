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

t_3v	refraction(t_p_info	*pi, t_3v dir, double entry_refraction)
{
	double	cosi;
	double	index;
	double	k;
	t_3v	n;

	n = ft_init_3v(pi->normal.v[0], pi->normal.v[1], pi->normal.v[2]);
	cosi = ft_3v_dot_product(pi->normal, dir);
	if (cosi > 1.0)
		cosi = 1.0;
	if (cosi < -1.0)
		cosi = -1.0;
	if (cosi < 0.0)
		cosi = -cosi;
	else
	{
		ft_swap_double(&entry_refraction, &(pi->obj_m).refractive_index);
		n = ft_3v_scalar(pi->normal, -1);
	}
	index = entry_refraction / (pi->obj_m).refractive_index;
	k = 1.0 - index * index * (1.0 - cosi * cosi);
	return (k < 0.0 ? ft_init_3v(0.0, 0.0, 0.0) :
		ft_3v_add(ft_3v_scalar(dir, index),
			ft_3v_scalar(n, index * cosi - sqrt(k))));
}