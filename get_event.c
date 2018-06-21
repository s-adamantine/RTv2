/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 14:35:35 by mpauw             #+#    #+#             */
/*   Updated: 2018/05/09 14:36:53 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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
	mlx_loop_hook(event->mlx, &loop_hook, event);
	mlx_mouse_hook(event->win, &mouse_click, event);
//	mlx_hook(event->win, MOTION_NOTIFY, POINTER_MOTION_MASK,
//			&drag_scene, event);
	// mlx_hook(event->win, BUTTON_RELEASE, BUTTON_RELEASE_MASK,
	// 		&toggle_button, event);
	mlx_hook(event->win, KEY_PRESS, KEY_PRESS_MASK,
			&key_hold, event);
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
	event.win = mlx_new_window(event.mlx, scene.width,
			scene.height, scene.name);
	event.scene = scene;
	init_image(event.mlx, scene.width, scene.height, &(event.img));
	event.mouse_hold = 0;
	event.t_select = KEY_L;
	event.id_select = KEY_0;
	event.redraw = 0;
	if (!((scene.cam)->p_array = (t_pixel *)malloc(sizeof(t_pixel)
				* scene.width * scene.height * scene.max_anti_a * scene.max_anti_a)) ||
			!((scene.cam)->pixel_set = (int *)malloc(sizeof(int)
				* scene.width * scene.height * scene.max_anti_a * scene.max_anti_a)))
		error(1);
	ft_bzero((scene.cam)->pixel_set, sizeof(int) * scene.width * scene.height * scene.max_anti_a * scene.max_anti_a);
	return (event);
}
