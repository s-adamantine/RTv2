/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 08:24:38 by mpauw             #+#    #+#             */
/*   Updated: 2018/03/21 16:08:39 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		key_pressed(int key, t_event *event)
{
	if (key == ESC)
		exit(0);
	else if (key == SPACE)
		anti_aliasing(event);
	return (1);
}

int		key_hold(int key, t_event *event)
{
	if (key == KEY_W || key == KEY_S || key == KEY_A || key == KEY_D)
	{
//		if (key == KEY_W || key == KEY_S)
//			set_move(event, (key == KEY_W ? -1 : 1));
//		else
//			set_move(event, (key == KEY_A ? -2 : 2));
		event->cur_grain = (event->scene).grain;
//		raytracer(event, &(event->scene), 0);
		mlx_put_image_to_window(event->mlx, event->win,
		(event->img)->img_ptr, 0, 0);
	}
	return (1);
}
