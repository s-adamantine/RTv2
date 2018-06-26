/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 14:35:35 by mpauw             #+#    #+#             */
/*   Updated: 2018/06/26 14:44:26 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	loop_hook(t_event *event)
{
	if (event->redraw)
	{
		mlx_put_image_to_window(event->mlx, event->win,
			(event->img).img_ptr, 0, 0);
		event->redraw = 0;
	}
	return (1);
}

void		init_loop(t_event *event)
{
	mlx_key_hook(event->win, &key_pressed, event);
	mlx_key_hook(event->menu_win, &key_pressed, event);
	mlx_loop_hook(event->mlx, &loop_hook, event);
	mlx_loop(event->mlx);
}

void		init_image(void *mlx, int width_scr, int height_scr, t_img *img)
{
	int		bpp;
	int		size_line;
	int		endian;

	img->img_ptr = mlx_new_image(mlx, width_scr, height_scr);
	img->width = width_scr;
	img->height = height_scr;
	img->img_arr = mlx_get_data_addr(img->img_ptr, &bpp, &size_line, &endian);
	img->bpp = bpp;
	img->size_line = size_line;
	img->size_line_int = size_line / (bpp / 8);
	img->endian = endian;
}

t_event		get_event(t_scene scene)
{
	t_event	event;

	event.mlx = mlx_init();
	event.sub_menu = 0;
	event.win = mlx_new_window(event.mlx, scene.width,
			scene.height, scene.name);
	event.menu_win = mlx_new_window(event.mlx, MENU_WIDTH, MENU_HEIGHT, "Menu");
	event.scene = scene;
	init_image(event.mlx, scene.width, scene.height, &(event.img));
	init_image(event.mlx, MENU_WIDTH, MENU_HEIGHT, &(event.menu_img));
	event.t_select = KEY_L;
	event.id_select = KEY_0;
	event.redraw = 0;
	if (!((scene.cam)->p_array = (t_pixel *)malloc(sizeof(t_pixel) *
					scene.width * scene.height * scene.max_anti_a *
					scene.max_anti_a)) || !((scene.cam)->pixel_set =
					(int *)malloc(sizeof(int) * scene.width * scene.height *
						scene.max_anti_a * scene.max_anti_a)))
		error(1);
	ft_bzero((scene.cam)->pixel_set, sizeof(int) * scene.width * scene.height *
			scene.max_anti_a * scene.max_anti_a);
	(scene.cam)->selected = 1;
	return (event);
}
