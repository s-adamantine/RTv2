/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_t_value.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 14:19:43 by mpauw             #+#    #+#             */
/*   Updated: 2018/06/26 11:50:08 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double			get_nearest_intersection(double a, double b, double d, int alt)
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

static double	in_limits(double *abcd, t_object *obj, t_fixed_v f, t_3v dir)
{
	abcd[2] = get_nearest_intersection(abcd[0], abcd[1], abcd[3], 0);
	if (abcd[2] > 0.001 && (abcd[2] = within_limits(obj, get_point(f.origin,
						dir, abcd[2]), abcd[2])) > 0)
		return (abcd[2]);
	else
	{
		abcd[2] = get_nearest_intersection(abcd[0], abcd[1], abcd[3], 1);
		if (abcd[2] > 0.001)
			return (within_limits(obj, get_point(f.origin, dir, abcd[2]),
						abcd[2]));
	}
	return (-1);
}

double			get_t_cylinder(t_fixed_v f, t_3v dir, int alt, t_object *obj)
{
	double	abcd[4];
	t_3v	tmp;

	(void)alt;
	if (!(obj->visible))
		return (-1);
	tmp = ft_3v_subtract(dir, ft_3v_scalar(f.dir,
					ft_3v_dot_product(dir, f.dir)));
	abcd[0] = ft_3v_dot_product(tmp, tmp);
	abcd[1] = 2 * ft_3v_dot_product(tmp, f.vec);
	abcd[2] = f.val - f.rad_sq;
	abcd[3] = abcd[1] * abcd[1] - 4 * abcd[0] * abcd[2];
	if (abcd[3] < 0.0001)
		return (-1);
	return (in_limits(abcd, obj, f, dir));
}

double			get_t_cone(t_fixed_v f, t_3v dir, int alt, t_object *obj)
{
	double	abcd[4];
	t_3v	tmp;

	(void)alt;
	if (!(obj->visible))
		return (-1);
	tmp = ft_3v_subtract(dir,
			ft_3v_scalar(f.dir, ft_3v_dot_product(dir, f.dir)));
	abcd[0] = cos(f.rad) * cos(f.rad) * ft_3v_dot_product(tmp, tmp);
	abcd[1] = 2 * cos(f.rad) * cos(f.rad) *
		ft_3v_dot_product(tmp, f.vec);
	abcd[2] = cos(f.rad) * cos(f.rad) * f.val;
	abcd[3] = ft_3v_dot_product(dir, f.dir);
	abcd[0] -= sin(f.rad) * sin(f.rad) * abcd[3] * abcd[3];
	abcd[1] -= 2 * sin(f.rad) * sin(f.rad) * abcd[3] * f.val_2;
	abcd[2] -= sin(f.rad) * sin(f.rad) * f.val_2 * f.val_2;
	abcd[3] = abcd[1] * abcd[1] - 4 * abcd[0] * abcd[2];
	if (abcd[3] < 0.0001)
		return (-1);
	return (in_limits(abcd, obj, f, dir));
}
