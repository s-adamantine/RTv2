/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 13:58:38 by mpauw             #+#    #+#             */
/*   Updated: 2018/04/11 16:24:55 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			drag_scene(int x, int y, t_event *event)
{
	if (event->mouse_hold)
	{
		set_drag_angle(event, x, y);
		event->x_0 = x;
		event->y_0 = y;
//		event->cur_grain = (event->scene).grain;
//		raytracer(event, &(event->scene), 0);
//		mlx_put_image_to_window(event->mlx, event->win,
//			(event->img).img_ptr, 0, 0);
	}
	return (1);
}

static void	menu_click(int index, t_event *event)
{
	t_menu_p	p;

	p = (event->menu).p[index];
}

int			toggle_button(int button, int x, int y, t_event *event)
{
	(void)x;
	(void)y;
	if (button == 1)
		event->mouse_hold = 0;
	return (1);
}

int			mouse_click(int button, int x, int y, t_event *event)
{
	if (x > (event->scene).width)
		menu_click((x - (event->scene.width) + y *
					((event->menu).sub_m[0]).width), event);
	else if (button == 1)
	{
		event->mouse_hold = 1;
		event->x_0 = x;
		event->y_0 = y;
	}
	else
		toggle_button(button, x, y, event);
	return (1);
}
