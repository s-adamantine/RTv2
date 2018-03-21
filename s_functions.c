/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_functions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 16:47:11 by mpauw             #+#    #+#             */
/*   Updated: 2018/03/21 17:44:34 by mpauw            ###   ########.fr       */
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
		return (-2);
	if (t_1 < 0.001)
		return (t_2);
	if (t_2 < 0.001)
		return (t_1);
	return ((t_1 < t_2) ? t_1 : t_2);
}

double	get_s_cylinder(t_object *s, t_3v dir, int i)
{
	double	a;
	double	b;
	double	c;
	double	d;
	t_3v	tmp;

	tmp = ft_3v_subtract(dir, ft_3v_scalar(s->rotation,
					ft_3v_dot_product(dir, s->rotation)));
	a = ft_3v_dot_product(tmp, tmp);
	b = 2 * ft_3v_dot_product(tmp, s->fixed_vec[i]);
	c = s->fixed_value[i] - s->radius_sq;
	d = b * b - 4 * a * c;
	if (d < 0.0001)
		return (-1);
	return (get_nearest_intersection(a, b, d));
}

double	get_s_sphere(t_object *s, t_3v dir, int i)
{
	double	a;
	double	b;
	double	c;
	double	d;

	if (s->type != 1)
		return (-1);
	a = ft_3v_dot_product(dir, dir);
	b = 2 * ft_3v_dot_product(dir, s->dif_c[i]);
	c = s->fixed_value[i] - s->radius_sq;
	d = b * b - 4 * a * c;
	if (d < 0.0001)
		return (-1);
	return (get_nearest_intersection(a, b, d));
}

double	get_s_plane(t_object *s, t_3v dir, int i)
{
	double	to_return;
	double	tmp;

	if ((tmp = ft_3v_dot_product(dir, s->normal)) < 0.0001)
		return (-1);
	to_return = s->fixed_value[i] / tmp;
	if (to_return > 0.0001)
		return (to_return);
	return (-1);
}

double	get_s_cone(t_object *s, t_3v dir, int i)
{
	double	a;
	double	b;
	double	c;
	double	d;
	t_3v	tmp;

	tmp = ft_3v_subtract(dir,
			ft_3v_scalar(s->rotation, ft_3v_dot_product(dir, s->rotation)));
	tmp = dir;
	printf("%f %f %f\n", (s->fixed_vec[i]).v[0], (s->fixed_vec[i]).v[1], (s->fixed_vec[i]).v[2]); 
	printf("%f %f %f\n", tmp.v[0], tmp.v[1], tmp.v[2]); 
	printf("%f\n", s->fixed_value_2[i]);
	/*
	a = cos(s->radius) * cos(s->radius) * ft_3v_dot_product(tmp, tmp);
	b = 2 * cos(s->radius) * cos(s->radius) *
		ft_3v_dot_product(tmp, s->fixed_vec[i]);
	c = cos(s->radius) * cos(s->radius) * s->fixed_value[i];
	d = ft_3v_dot_product(dir, s->rotation);
	a -= sin(s->radius) * sin(s->radius) * d * d;
	b -= 2 * sin(s->radius) * sin(s->radius) * d * s->fixed_value_2[i];
	c -= sin(s->radius) * sin(s->radius) * s->fixed_value_2[i]
		* s->fixed_value_2[i];
	*/
	a = cos(s->radius) * cos(s->radius) * ft_3v_dot_product(tmp, tmp);
	b = 2 * cos(s->radius) * cos(s->radius) * ft_3v_dot_product(tmp, (s->fixed_vec[i]));
	c = cos(s->radius) * cos(s->radius) * ft_3v_dot_product((s->fixed_vec[i]), (s->fixed_vec[i]));
	d = b * b - 4 * a * c;
	printf("%f %f %f %f\n", a, b, c, d);
	if (d < 0.0001)
		return (-1);
	return (get_nearest_intersection(a, b, d));
}
