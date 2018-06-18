/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_limits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 14:52:50 by mpauw             #+#    #+#             */
/*   Updated: 2018/06/18 14:26:27 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	within_planes(t_object *p1, t_object *p2, t_3v point)
{
	t_3v	dir;
	double	tmp;
	double	val;
	t_3v	dif_c;

	dir = ft_3v_subtract(point, p1->origin);
	dif_c = ft_3v_subtract(p2->origin, p1->origin);
	val = ft_3v_dot_product(p1->dir, dif_c);
	if (fabs((tmp = ft_3v_dot_product(dir, p1->dir))) < 0.00001)
		return (-1);
	if ((val / tmp) < 0)
		return (-1);
	dir = ft_3v_subtract(point, p2->origin);
	dif_c = ft_3v_subtract(p1->origin, p2->origin);
	val = ft_3v_dot_product(p2->dir, dif_c);
	if (fabs((tmp = ft_3v_dot_product(dir, p2->dir))) < 0.00001)
		return (-1);
	if ((val / tmp) < 0)
		return (-1);
	return (1);
}

double	within_limits(t_object *obj, t_3v point, double b)
{
	int	c;

	if (!(obj->visible))
		return (-1);
	if (obj->lim_by_1 <= 0 || obj->lim_by_2 <= 0)
		return (b);
	c = within_planes(obj->obj_lim_1, obj->obj_lim_2, point);
	if (c > 0)
		return (b);
	else
		return (-3);
}
