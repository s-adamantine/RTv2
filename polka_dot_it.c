/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polka_dot_it.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 16:43:29 by mpauw             #+#    #+#             */
/*   Updated: 2018/06/11 11:29:22 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_material	handle_plane(t_object o, t_3v dif)
{
	double	dist_1;
	double	dist_2;
	double	corr_size;
	double	corr_dist;

	corr_size = (o.pattern).size / 10;
	corr_dist = (o.pattern).distance * 10;
	dist_1 = fabs(fmod(dif.v[1], corr_dist)) - corr_dist / 2;
	dist_2 = fabs(fmod(dif.v[2], corr_dist)) - corr_dist / 2;
	dist_1 = sqrt(dist_1 * dist_1 + dist_2 * dist_2);
	if (dist_1 < corr_size)
		return (o.m2);
	return (o.m);
}

static t_material	handle_sphere(t_object o, t_3v angle)
{
	t_3v	ref;
	int		i;
	double	d;

	i = 0;
	while (i < (o.pattern).amount_points)
	{
		ref = (o.pattern).points_arr[i];
		d = acos(sin(ref.v[1]) * sin(angle.v[1]) + cos(ref.v[1])
			* cos(angle.v[1]) * cos(ref.v[2] - angle.v[2]));
		if (d < (o.pattern).size)
			return (o.m2);
		i++;
	}
	return (o.m);
}

static t_material	handle_cyl_cone(t_object o, t_3v angle, t_3v dist)
{
	t_3v	ref;
	t_3v	angle_tmp;

	(void)angle_tmp;
	(void)dist;
	(void)angle;
	if (o.type == 2)
		ref = ft_init_3v(o.radius, 0.0, 0.0);
	else
		ref = ft_init_3v(o.radius, (o.pattern).distance, 0.0);
	return (o.m);
}

t_material		polka_dot_it(t_object o, t_3v angle, t_3v dif)
{
	if (o.type == 0)
		return (handle_plane(o, dif));
	else if (o.type == 1)
		return (handle_sphere(o, angle));
	else if (o.type == 2 || o.type == 3)
		return (handle_cyl_cone(o, angle, dif));
	return (o.m);
}
