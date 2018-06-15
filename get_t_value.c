/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_t_value.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 14:19:43 by mpauw             #+#    #+#             */
/*   Updated: 2018/06/15 17:33:14 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static double	get_nearest_intersection(double a, double b, double d, int alt)
{
	double	t_1;
	double	t_2;

	t_1 = (-b + sqrt(d)) / (2 * a);
	t_2 = (-b - sqrt(d)) / (2 * a);
	if (t_1 < 0.001 && t_2 < 0.001)
		return (-2);
	if (t_1 < 0.001)
		return (t_2);
	if (t_2 < 0.001)
		return (t_1);
	if (alt == 0)
		return ((t_1 < t_2) ? t_1 : t_2);
	else
		return ((t_1 < t_2) ? t_2 : t_1);
}

double	get_t_plane(t_fixed_v f, t_3v dir, int alt, t_object *obj)
{
	double	to_return;
	double	tmp;

	if (!(obj->visible))
		return (-1);
	(void)alt;
	if (fabs((tmp = ft_3v_dot_product(dir, f.dir))) < 0.00001)
		return (-1);
	to_return = -(f.val / tmp);
	if (to_return > 0.0001 && within_limits(obj, get_point(f.origin, dir, to_return)) > 0)
		return (to_return);
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
	if (c > 0.001 && within_limits(obj, get_point(f.origin, dir, c)) > 0)
		return (c);
	else
	{
		c = get_nearest_intersection(a, b, d, 1);
		if (c > 0.001 && within_limits(obj, get_point(f.origin, dir, c)) > 0)
			return (c);
	}
	return (-1);
}

double	get_t_cylinder(t_fixed_v f, t_3v dir, int alt, t_object *obj)
{
	double	a;
	double	b;
	double	c;
	double	d;
	t_3v	tmp;

	if (!(obj->visible))
		return (-1);
	tmp = ft_3v_subtract(dir, ft_3v_scalar(f.dir,
					ft_3v_dot_product(dir, f.dir)));
	a = ft_3v_dot_product(tmp, tmp);
	b = 2 * ft_3v_dot_product(tmp, f.vec);
	c = f.val - f.rad_sq;
	d = b * b - 4 * a * c;
	if (d < 0.0001)
		return (-1);
	c = get_nearest_intersection(a, b, d, alt);
	if (c > 0.001 && within_limits(obj, get_point(f.origin, dir, c)) > 0)
		return (c);
	else
	{
		c = get_nearest_intersection(a, b, d, 1);
		if (c > 0.001 && within_limits(obj, get_point(f.origin, dir, c)) > 0)
			return (c);
	}
	return (-1);
}

double	get_t_cone(t_fixed_v f, t_3v dir, int alt, t_object *obj)
{
	double	a;
	double	b;
	double	c;
	double	d;
	t_3v	tmp;

	if (!(obj->visible))
		return (-1);
	tmp = ft_3v_subtract(dir,
			ft_3v_scalar(f.dir, ft_3v_dot_product(dir, f.dir)));
	a = cos(f.rad) * cos(f.rad) * ft_3v_dot_product(tmp, tmp);
	b = 2 * cos(f.rad) * cos(f.rad) *
		ft_3v_dot_product(tmp, f.vec);
	c = cos(f.rad) * cos(f.rad) * f.val;
	d = ft_3v_dot_product(dir, f.dir);
	a -= sin(f.rad) * sin(f.rad) * d * d;
	b -= 2 * sin(f.rad) * sin(f.rad) * d * f.val_2;
	c -= sin(f.rad) * sin(f.rad) * f.val_2 * f.val_2;
	d = b * b - 4 * a * c;
	if (d < 0.0001)
		return (-1);
	c = get_nearest_intersection(a, b, d, alt);
	if (c > 0.001 && within_limits(obj, get_point(f.origin, dir, c)) > 0)
		return (c);
	else
	{
		c = get_nearest_intersection(a, b, d, 1);
		if (c > 0.001 && within_limits(obj, get_point(f.origin, dir, c)) > 0)
			return (c);
	}
	return (-1);
}
