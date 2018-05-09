/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polka_dot_it.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 16:43:29 by mpauw             #+#    #+#             */
/*   Updated: 2018/05/09 17:05:08 by mpauw            ###   ########.fr       */
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
	t_3v	angles_tmp;
	t_3v	ref;
	double	d;

	ref = ft_init_3v(o.radius, 0, 0);
	angles_tmp = angle;
	angles_tmp.v[1] = fabs(fmod(angles_tmp.v[1], (o.pattern).distance)) -
		(o.pattern).size / o.radius;
	angles_tmp.v[2] = fabs(fmod(angles_tmp.v[2], (o.pattern).distance)) -
		(o.pattern).size / o.radius;
	angles_tmp = ft_3v_scalar(angles_tmp, 1 / DEG);
	ref = ft_3v_scalar(ref, 1 / DEG);
	d = o.radius * acos(sin(ref.v[1]) * sin(angles_tmp.v[1]) + cos(ref.v[1])
			* cos(angles_tmp.v[1]) * cos(ref.v[2] - angles_tmp.v[2]));
	if (d < (o.pattern).size / o.radius)
		return (o.m2);
	return (o.m);
}

static t_material	handle_cyl_cone(t_object o, t_3v angle, t_3v dist)
{
	(void)angle;
	(void)dist;
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
