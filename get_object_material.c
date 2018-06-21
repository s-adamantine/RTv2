/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_object_material.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 14:27:04 by mpauw             #+#    #+#             */
/*   Updated: 2018/06/21 16:10:19 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_3v	get_angle(t_object o, t_3v p)
{
	t_3v	k;
	t_3v	rot_axis;

	if (o.type == 0)
		return (p);
	p = rotate_v_inv(p, o.rotation);
	k.v[0] = o.radius;
	if (o.type == 1)
		k.v[1] = M_PI / 2 - acos(p.v[2] / o.radius);
	else if (o.type == 2)
		k.v[1] = p.v[2];
	else
		k.v[1] = p.v[2] / cos(o.radius);
	rot_axis = ft_zero_3v();
	rot_axis.v[2] = o.axis_rotation;
	p = rotate_v(p, rot_axis);
	k.v[2] = 0;
	if (p.v[0] == 0)
		return (k);
	k.v[2] = atan2(p.v[1], p.v[0]);
	return (k);
}

t_material	get_object_material(t_object o, t_3v p)
{
	t_3v	dif;
	t_3v	angle;

	dif = ft_3v_subtract(p, o.origin);
	angle = get_angle(o, dif);
	if ((o.pattern).type == 1)
		return (polka_dot_it(o, angle, dif));
	else if ((o.pattern).type == 2)
		return (stripe_it(o, angle, dif));
	return (o.m);
}
