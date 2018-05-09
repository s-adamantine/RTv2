/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_anti_a.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 14:24:17 by mpauw             #+#    #+#             */
/*   Updated: 2018/05/09 14:24:18 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int		take_average(t_event *event, t_scene scene, int vert, int hor)
{
	int		i;
	int		j;
	int		k;
	int		index;
	t_3v	color;

	i = -1;
	index = scene.anti_a * hor + scene.anti_a * vert * scene.width;
	color = ft_zero_3v();
	while (++i < scene.anti_a)
	{
		j = -1;
		while (++j < scene.anti_a)
		{
			k = -1;
			while (++k < 3)
			{
				color.v[k] = (color.v[k] * (j * scene.anti_a + i) + ((unsigned
					char *)(event->img).img_arr)[(index + j + i * scene.width)
						* 4 + k]) / 255 * (j * scene.anti_a + i + 1);
			}
		}
		i++;
	}
	return (get_color(color));
}

static void		reset(t_scene *scene, t_scene tmp, t_event *event, t_img img)
{
	scene->width = tmp.width;
	scene->height = tmp.height;
	scene->grain = tmp.grain;
	event->img = img;
}

static t_scene	set(t_scene *scene, t_event *event, t_img *img)
{
	t_scene	tmp;

	tmp.width = scene->width;
	tmp.height = scene->height;
	tmp.grain = scene->grain;
	init_image(event->mlx, tmp.width, tmp.height, img);
	scene->width *= scene->anti_a;
	scene->height *= scene->anti_a;
	scene->grain = 1;
	init_image(event->mlx, scene->width, scene->height, &(event->img));
	return (tmp);
}

void			anti_aliasing(t_event *event)
{
	t_scene	tmp;
	int		i;
	int		j;
	t_img	old_img;

	tmp = set(&(event->scene), event, &old_img);
	i = 0;
	while (i < tmp.height)
	{
		j = 0;
		while (j < tmp.width)
		{
			((int *)(old_img.img_arr))[j + i * tmp.width] = take_average(event, event->scene, i, j);
			j++;
		}
		i++;
	}
	reset(&(event->scene), tmp, event, old_img);
	mlx_put_image_to_window(event->mlx, event->win,
			old_img.img_ptr, 0, 0);
}
