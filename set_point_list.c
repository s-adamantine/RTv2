/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_point_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 09:32:03 by mpauw             #+#    #+#             */
/*   Updated: 2018/06/26 11:52:12 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	set_point_list(t_pattern *p)
{
	int			i;
	double		tmp;
	double		offset;
	double		increment;
	int			ran;

	ran = p->amount_points * ((double)rand() / (double)RAND_MAX);
	if (!(p->points_arr = (t_3v *)malloc(sizeof(t_3v) * p->amount_points)))
		error(2);
	offset = 2.0 / p->amount_points;
	increment = M_PI * (3.0 - sqrt(5.0));
	i = 0;
	while (i < p->amount_points)
	{
		(p->points_arr[i]).v[0] = 1;
		(p->points_arr[i]).v[1] = (M_PI / 2) - acos(((i * offset) - 1) +
				(offset / 2));
		tmp = ((i + ran) % p->amount_points) * increment;
		(p->points_arr[i]).v[2] = atan2(sin(tmp), cos(tmp));
		i++;
	}
}
