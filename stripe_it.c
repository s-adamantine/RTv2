/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stripe_it.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 16:11:17 by mpauw             #+#    #+#             */
/*   Updated: 2018/06/21 18:24:52 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_material	handle_plane(t_object o, t_3v dif)
{
	double	d_1;
	double	d_2;
	double	tmp_size;

	tmp_size = o.pattern.size;
	d_1 = fmod(fabs(dif.v[0] + dif.v[1] * o.pattern.os_1) + tmp_size / 2,
			o.pattern.distance);
	d_2 = fmod(fabs(dif.v[0] + dif.v[1] * o.pattern.os_2) + tmp_size / 2,
			o.pattern.distance);
	if (d_1 < tmp_size || d_2 < tmp_size)
		return (o.m2);
	return (o.m);
}

static t_material	handle_cyl_cone(t_object o, t_3v angle, t_3v dif)
{
	double	d_1;
	double	tmp_size;

	tmp_size = o.pattern.size;
	d_1 = fmod(fabs(angle.v[2] + dif.v[2] * o.pattern.os_1 / 100.0) +
			tmp_size / 2, o.pattern.distance);
	if (d_1 < tmp_size)
		return (o.m2);
	return (o.m);
}

t_material	stripe_it(t_object o, t_3v angle, t_3v dif)
{
	if (o.type == 0)
		return (handle_plane(o, dif));
	else if (o.type == 1)
		return (handle_cyl_cone(o, angle, dif));
	else if (o.type == 2 || o.type == 3)
		return (handle_cyl_cone(o, angle, dif));
	return (o.m);
}
