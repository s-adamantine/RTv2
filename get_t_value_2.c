/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_t_value_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 11:12:11 by mpauw             #+#    #+#             */
/*   Updated: 2018/06/18 15:35:08 by sadamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	get_t_triangle(t_fixed_v f, t_3v dir)
{
	double	bottom;
	t_3v	p;
	t_3v	vp0;
	t_3v	vp1;
	t_3v	vp2;

	if ((bottom = ft_3v_dot_product(f.vec, dir)) > -0.01)
		return (-1);
	p = ft_3v_add(f.vec2, ft_3v_scalar(dir, t));
	vp0 = ft_cross_product(ft_3v_subtract(f.vertex1, f.vertex0),
		ft_3v_subtract(P, f.vertex0));
	vp1 = ft_cross_product(ft_3v_subtract(f.vertex2, f.vertex1),
		ft_3v_subtract(P, f.vertex1));
	vp2 = ft_cross_product(ft_3v_subtract(f.vertex0, f.vertex2),
		ft_3v_subtract(P, f.vertex2));
	if (ft_3v_dot_product(f.vec, vp0) < 0 || ft_3v_dot_product(f.vec, vp1) < 0
		|| ft_3v_dot_product(f.vec, vp2) < 0)
		return (-1);
	return (f.val / bottom * -1);
}
