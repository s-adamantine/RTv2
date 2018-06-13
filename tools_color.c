/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 14:15:10 by mpauw             #+#    #+#             */
/*   Updated: 2018/05/09 14:15:12 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
 * Get an int value for color based on a color vector.
 */

int	get_color(t_3v c)
{
	int		color;
	int		int_value;

	if (c.v[0] > 1)
		c.v[0] = 1;
	else if (c.v[0] < 0)
		c.v[0] = 0;
	if (c.v[1] > 1)
		c.v[1] = 1;
	else if (c.v[1] < 0)
		c.v[1] = 0;
	if (c.v[2] > 1)
		c.v[2] = 1;
	else if (c.v[2] < 0)
		c.v[2] = 0;
	color = c.v[0] * 0xff;
	int_value = c.v[1] * 0xff;
	color += int_value * 0x100;
	int_value = c.v[2] * 0xff;
	color += int_value * 0x10000;
	return (color);
}
