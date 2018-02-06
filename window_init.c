/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 17:10:12 by mpauw             #+#    #+#             */
/*   Updated: 2018/02/06 09:28:36 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_img	*init_image(void *mlx, int width_scr, int height_scr)
{
	t_img	*img;
	int		bpp;
	int		size_line;
	int		endian;

	if (!(img = (t_img *)malloc(sizeof(t_img))))
		error(errno);
	img->img_ptr = mlx_new_image(mlx, width_scr, height_scr);
	img->width = width_scr;
	img->height = height_scr;
	img->img_arr = mlx_get_data_addr(img->img_ptr, &bpp, &size_line, &endian);
	img->bpp = bpp;
	img->size_line = size_line;
	img->size_line_int = size_line / (bpp / 8);
	img->endian = endian;
	return (img);
}

static int		loop_hook(t_event *event)
{
	if ((event->scene).grain >= 2)
	{
		(event->scene).grain /= 2;
		raytracer(event, &(event->scene), 1);
		mlx_put_image_to_window(event->mlx, event->win,
			(event->img)->img_ptr, 0, 0);
	}
	return (1);
}

void			init_loop(t_event *event)
{
	mlx_key_hook(event->win, &key_pressed, event);
	mlx_loop_hook(event->mlx, &loop_hook, event);
	mlx_loop(event->mlx);
}

t_event			init_window(t_scene scene)
{
	t_event	event;

	event.mlx = mlx_init();
	event.win = mlx_new_window(event.mlx, scene.width,
			scene.height, scene.name);
	event.scene_name = scene.name;
	event.scene = scene;
	event.img = init_image(event.mlx, scene.width, scene.height);
	return (event);
}
