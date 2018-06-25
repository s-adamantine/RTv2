/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_t_value_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 11:12:11 by mpauw             #+#    #+#             */
/*   Updated: 2018/06/25 12:03:38 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	get_t_plane(t_fixed_v f, t_3v dir, int alt, t_object *obj)
{
	double	c;
	double	tmp;

	if (!(obj->visible))
		return (-1);
	(void)alt;
	if (fabs((tmp = ft_3v_dot_product(dir, f.dir))) < 0.00001)
		return (-1);
	c = -(f.val / tmp);
	if (c > 0.0001)
		return (within_limits(obj, get_point(f.origin, dir, c), c));
	return (-1);
}

double	get_t_sphere(t_fixed_v f, t_3v dir, int alt, t_object *obj)
{
	double	a;
	double	b;
	double	c;
	double	d;

	if (!(obj->visible))
		return (-1);
	a = ft_3v_dot_product(dir, dir);
	b = 2 * ft_3v_dot_product(dir, f.dif_c);
	c = f.val - f.rad_sq;
	d = b * b - 4 * a * c;
	if (d < 0.0001)
		return (-1);
	c = get_nearest_intersection(a, b, d, alt);
	if (c > 0.001 && (c = within_limits(obj, get_point(f.origin, dir, c),
					c)) > 0)
		return (within_limits(obj, get_point(f.origin, dir, c), c));
	else
	{
		c = get_nearest_intersection(a, b, d, 1);
		if (c > 0.001)
			return (within_limits(obj, get_point(f.origin, dir, c), c));
	}
	return (-1);
}

double	get_t_triangle(t_fixed_v f, t_3v dir, int alt, t_object *obj)
{
	double	bottom;
	t_3v	p;
	t_3v	vp0;
	t_3v	vp1;
	t_3v	vp2;

	(void)alt;
	(void)obj;
	if ((bottom = ft_3v_dot_product(f.vec, dir)) > -0.01)
		return (-1);
	p = ft_3v_add(f.vec2, ft_3v_scalar(dir, f.val / bottom * -1));
	vp0 = ft_cross_product(ft_3v_subtract(f.vertex1, f.vertex0),
		ft_3v_subtract(p, f.vertex0));
	vp1 = ft_cross_product(ft_3v_subtract(f.vertex2, f.vertex1),
		ft_3v_subtract(p, f.vertex1));
	vp2 = ft_cross_product(ft_3v_subtract(f.vertex0, f.vertex2),
		ft_3v_subtract(p, f.vertex2));
	if (ft_3v_dot_product(f.vec, vp0) < 0 || ft_3v_dot_product(f.vec, vp1) < 0
		|| ft_3v_dot_product(f.vec, vp2) < 0)
		return (-1);
	return (f.val / bottom * -1);
}

double	get_t_mesh(t_fixed_v f, t_3v dir, int alt)
{
	(void)f;
	(void)dir;
	(void)alt;
	return (-1);
}
