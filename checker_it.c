/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_it.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 16:32:22 by mpauw             #+#    #+#             */
/*   Updated: 2018/05/09 16:32:47 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_material	handle_plane(t_object o, t_3v dif)
{
	double	dist_1;
	double	dist_2;

	dist_1 = fabs(fmod(dif.v[1], (o.pattern).distance));
	dist_2 = fabs(fmod(dif.v[2], (o.pattern).distance));
	printf("%f %f\n", dist_1, dist_2);
	if (dist_1 < 15 && dist_2 < 15)
		return (o.m2);
	return (o.m);
}
