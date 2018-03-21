/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 13:58:38 by mpauw             #+#    #+#             */
/*   Updated: 2018/03/21 16:08:16 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		drag_scene(int x, int y, t_event *event)
{
	if (event->mouse_hold)
	{
//		set_drag_angle(event, x, y);
		event->x_0 = x;
		event->y_0 = y;
		event->cur_grain = (event->scene).grain;
//		raytracer(event, &(event->scene), 0);
//		mlx_put_image_to_window(event->mlx, event->win,
//			(event->img)->img_ptr, 0, 0);
	}
	return (1);
}

int		mouse_click(int button, int x, int y, t_event *event)
{
	if (button == 1)
	{
		event->mouse_hold = 1;
		event->x_0 = x;
		event->y_0 = y;
	}
	else
		toggle_button(button, x, y, event);
	return (1);
}

int		toggle_button(int button, int x, int y, t_event *event)
{
	(void)x;
	(void)y;
	if (button == 1)
		event->mouse_hold = 0;
	return (1);
}
