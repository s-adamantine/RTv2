/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_functions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 16:47:11 by mpauw             #+#    #+#             */
/*   Updated: 2018/02/20 18:39:08 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static double	get_nearest_intersection(double a, double b, double d)
{
	double	t_1;
	double	t_2;

	t_1 = (-b + sqrt(d)) / (2 * a);
	t_2 = (-b - sqrt(d)) / (2 * a);
	if (t_1 < 0.001 && t_2 < 0.001)
		return (-1);
	if (t_1 < 0.001)
		return (t_2);
	if (t_2 < 0.001)
		return (t_1);
	return ((t_1 < t_2) ? t_1 : t_2);
}

double	get_s_cylinder(t_object *s, t_3v dir, t_3v src_o)
{
	double	a;
	double	b;
	double	c;
	double	d;

	if (s->type != 2)
		return (-1);
	a = (dir.v)[0] * (dir.v)[0] + (dir.v)[1] * (dir.v)[1];
	b = (dir.v)[0] * (src_o.v)[0] + (dir.v)[1] * (src_o.v)[1];
	b = 2 * b;
	c = (src_o.v)[0] * (src_o.v)[0] + (src_o.v)[1] * (src_o.v)[1] -
		s->radius * s->radius;
	d = b * b - 4 * a * c;
	if (d < 0.0001)
		return (-1);
	return (get_nearest_intersection(a, b, d));
}

double	get_s_sphere(t_object *s, t_3v dir, t_3v src_o)
{
	double	a;
	double	b;
	double	c;
	double	d;

	if (s->type != 1)
		return (-1);
	a = ft_3v_dot_product(dir, dir);
	b = 2 * ft_3v_dot_product(dir, src_o);
	c = ft_3v_dot_product(src_o, src_o) - s->radius * s->radius;
	d = b * b - 4 * a * c;
	if (d < 0)
		return (-1);
	return (get_nearest_intersection(a, b, d));
}

double	get_s_plane(t_object *s, t_3v dir, t_3v src_o)
{
	double	to_return;

	if (s->type != 0)
		return (-1);
	if ((dir.v)[1] == 0)
		return (-1);
	to_return = -((src_o.v)[1] / (dir.v)[1]);
	if (to_return > 0.0001)
		return (to_return);
	return (-1);
}

double	get_s_cone(t_object *s, t_3v dir, t_3v src_o)
{
	double	a;
	double	b;
	double	c;
	double	d;
	double	angle;

	if (s->type != 3)
		return (-1);
	angle = s->radius;
	a = cos(angle) * cos(angle) * ((dir.v)[0] * (dir.v)[0] +
				(dir.v)[1] * (dir.v)[1]) - sin(angle) *
		sin(angle) * (dir.v)[2] * (dir.v)[2];
	b = 2 * (cos(angle) * cos(angle) * ((dir.v)[0] * (src_o.v)[0] +
				(dir.v)[1] * (src_o.v)[1]) - sin(angle) *
			sin(angle) * (dir.v)[2] * (src_o.v)[2]);
	c = cos(angle) * cos(angle) * ((src_o.v)[0] * (src_o.v)[0] +
		(src_o.v)[1] * (src_o.v)[1]) - sin(angle) * sin(angle) *
		(src_o.v)[2] * (src_o.v)[2];
	d = b * b - 4 * a * c;
	if (d < 0)
		return (-1);
	return (get_nearest_intersection(a, b, d));
}
