/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polka_dot_it.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 16:43:29 by mpauw             #+#    #+#             */
/*   Updated: 2018/06/26 11:49:33 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_material	handle_plane(t_object o, t_3v dif)
{
	double	d_1;
	double	d_2;
	double	tmp_size;
	int		row;

	tmp_size = o.pattern.size * 100;
	d_1 = fmod(fabs(dif.v[0]) + tmp_size, o.pattern.distance)
		- tmp_size;
	row = floor((dif.v[0] + tmp_size) / o.pattern.distance);
	d_2 = fmod(fabs(dif.v[1] + row * o.pattern.os_1) + tmp_size,
			o.pattern.distance) - tmp_size;
	if (d_1 * d_1 + d_2 * d_2 < tmp_size * tmp_size)
		return (o.m2);
	return (o.m);
}

static t_material	handle_sphere(t_object o, t_3v angle)
{
	t_3v	ref;
	int		i;
	double	d;

	i = 0;
	if (!(o.pattern_id))
		return (o.m);
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

t_material			polka_dot_it(t_object o, t_3v angle, t_3v dif)
{
	if (o.type % 5 == 0)
		return (handle_plane(o, dif));
	else if (o.type == 1)
		return (handle_sphere(o, angle));
	return (o.m);
}
