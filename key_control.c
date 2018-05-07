/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 08:24:38 by mpauw             #+#    #+#             */
/*   Updated: 2018/05/07 18:08:49 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	change_grain(t_event *event, int sharper)
{
	if (sharper && ((event->scene).cam)->grain >= 2)
	{
		((event->scene).cam)->grain /= 2;
		get_s_values((void *)event);
		init_light_values((void *)event);
		turn_on_lights(event);
		mlx_put_image_to_window(event->mlx, event->win,
			(event->img).img_ptr, 0, 0);
	}
	else if (!sharper)
		((event->scene).cam)->grain *= 2;
}

int			key_pressed(int key, t_event *event)
{
	if (key == ESC)
		exit(0);
	else if (key == SPACE)
		anti_aliasing(event);
	else if (KEY_UP_TO_ZERO(key) || key == KEY_0)
		event->id_select = (key == KEY_0) ? KEY_0 : KEY_NUM_VALUE(key);
	else if (key == KEY_C || key == KEY_O || key == KEY_L)
		event->t_select = key;
	else if (key == KEY_Q && event->t_select == KEY_L)
		turn_on_lights(event);
	else if (key == KEY_Q && event->t_select == KEY_C)
		change_camera(event);
	else if (key == COMMA || key == DOT)
		change_grain(event, (key == COMMA));
	return (1);
}

int			key_hold(int key, t_event *event)
{
	if (key == KEY_W || key == KEY_S || key == KEY_A || key == KEY_D)
	{
//		if (key == KEY_W || key == KEY_S)
//			set_move(event, (key == KEY_W ? -1 : 1));
//		else
//			set_move(event, (key == KEY_A ? -2 : 2));
//		raytracer(event, &(event->scene), 0);
		mlx_put_image_to_window(event->mlx, event->win,
		(event->img).img_ptr, 0, 0);
	}
	return (1);
}
