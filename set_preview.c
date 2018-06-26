/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_preview.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 14:10:17 by mpauw             #+#    #+#             */
/*   Updated: 2018/06/26 11:52:15 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	get_value(t_scene *scene, int i, int j)
{
	t_3v	p;

	p.v[0] = -(scene->width / 2);
	p.v[1] = (double)(j - scene->width / 2.0);
	p.v[2] = (double)(scene->height / 2.0 - i);
}

void		set_preview(void *arg)
{
	t_pixel		*p;
	t_event		*e;
	int			i;
	int			j;
	int			factor;

	e = (t_event*)arg;
	factor = e->scene.max_anti_a;
	i = ((e->scene.height * factor / THREADS) * e->scene.thread_id);
	while (i < (e->scene.height * factor / THREADS) * (e->scene.thread_id + 1))
	{
		j = 0;
		while (j < e->scene.width * factor)
		{
			if (!(e->scene.cam)->pixel_set[j + i * e->scene.width * factor])
				get_value(&e->scene, i, j);
			j += e->scene.step_size;
		}
		i += e->scene.step_size;
	}
	(e->scene.cam)->init = 1;
	return (NULL);
}
