/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 13:58:38 by mpauw             #+#    #+#             */
/*   Updated: 2018/02/07 15:10:20 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		drag_scene(int x, int y, t_event *event)
{
	t_scene		scene;
	t_source	cam;

	if (event->mouse_hold)
	{
		scene = event->scene;
		cam = scene.cam;
		
		event->x_0 = x;
		event->y_0 = y;
		event->cur_grain = (event->scene).grain;
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
