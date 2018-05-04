/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_patterns.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 11:09:01 by mpauw             #+#    #+#             */
/*   Updated: 2018/04/18 16:26:07 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_3v	get_angle(t_object o, t_3v p)
{
	t_3v	k;
	t_3v	rot_axis;

	p = ft_3v_subtract(p, o.origin);
	p = get_rev_dir(p, o.rotation);
	k.v[0] = o.radius;
	k.v[1] = 90 - DEG * acos(p.v[2] / o.radius);
	rot_axis = ft_zero_3v();
	rot_axis.v[2] = o.axis_rotation;
	p = get_dir(p, rot_axis);
	k.v[2] = 0;
	if (p.v[0] == 0)
		return (k);
	k.v[2] = DEG * atan2(p.v[1], p.v[0]);
	return (k);
}

static double	distance_from_point(t_object o, t_3v p, t_3v k)
{
	double	d;

	p = ft_3v_scalar(p, 1 / DEG);
	k = ft_3v_scalar(k, 1 / DEG);
	d = o.radius * acos(sin(k.v[1]) * sin(p.v[1]) + cos(k.v[1]) * cos(p.v[1])
			* cos(k.v[2] - p.v[2]));
	return (d);
}

t_material		get_object_material(t_object o, t_3v p)
{
	t_3v	angles;
	t_3v	angles_tmp;
	t_3v	ref;
	
	if (o.type != 1)
		return (o.m);
	angles = get_angle(o, p);
	ref = ft_init_3v(o.radius, 0, 0);
	angles_tmp = angles;
	angles_tmp.v[1] = fabs(fmod(angles_tmp.v[1], 20)) - 10;
	angles_tmp.v[2] = fabs(fmod(angles_tmp.v[2], 20)) - 10;
	if (distance_from_point(o, angles_tmp, ref) < 10)
		return (o.m2);
	return (o.m);
}
