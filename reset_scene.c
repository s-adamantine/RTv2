/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 17:27:16 by mpauw             #+#    #+#             */
/*   Updated: 2018/06/22 17:36:50 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	reset_pixels((void) *arg)
{
	t_pixel		*p;
	t_event		*e;
	int			i;
	int			j;
	int			factor;

	e = (t_event*)arg;
	factor = e->scene.max_anti_a;
	i = ((e->scene.height * factor / THREADS) * e->scene.thread_id);
	while (i < (e->scene.height * factor / THREADS)  * (e->scene.thread_id + 1))
	{
		j = 0;
		while (j < e->scene.width * factor)
		{
			if (!(e->scene.cam)->pixel_set[j + i * e->scene.width * factor])
			{
				p = &((e->scene.cam)->p_array[j + i * e->scene.width * factor]);
				reset_pixel(p, e->scene, i, j, factor);
			}
			j++;
		}
		i++;
	}
	return (NULL);
}

void			*reset_scene(t_event *event)
{
	reset_fixed_values(event);
	reset_pixels((void *)event);
}
