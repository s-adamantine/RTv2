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

/*
 * Based on transparency/specular reflection, determine how much influence this
 * object has on the color of this pixel.
 */

double	get_influence(t_pixel *p, int i)
{
	double	influence;
	influence = 1 - (((p->pi_arr[i])->vis_obj)->m).transparent;

	if ((p->pi_arr[i])->type == 2)
	{
		while (i > 0)
		{
			if ((p->pi_arr[i - 1])->type % 2 == 0)
			{
				influence *= ((((p->pi_arr[i - 1])->vis_obj)->m).transparent
					* p->pi_arr[i - 1]->fresnal_transparent);
			}
			i--;
		}
	}
	else if ((p->pi_arr[i])->type == 1)
	{
 		while (i > 0)
	 	{
			if ((p->pi_arr[i - 1])->type < 2)
				influence *= get_influence_specular(p, i);
			i--;
		}
	}
	return (influence);
}

double	get_influence_specular(t_pixel *p, int i)
{
	if ((((p->pi_arr[i - 1])->vis_obj)->m).transparent > 0.001
		&& ((p->pi_arr[i - 1])->is_inside == 1 ||
			(((p->pi_arr[i - 1])->vis_obj)->m).specular < 0.001))
		return ((p->pi_arr[i - 1])->fresnal_specular);
	else if ((((p->pi_arr[i - 1])->vis_obj)->m).transparent > 0.001 &&
		(((p->pi_arr[i - 1])->vis_obj)->m).specular > 0.001)
		return ((((p->pi_arr[i - 1])->vis_obj)->m).specular
			* (p->pi_arr[i - 1])->fresnal_specular);
	else
		return ((((p->pi_arr[i - 1])->vis_obj)->m).specular);
}