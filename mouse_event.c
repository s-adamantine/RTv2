/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 13:58:38 by mpauw             #+#    #+#             */
/*   Updated: 2018/04/12 16:46:27 by mpauw            ###   ########.fr       */
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

static void	handle_object_select(t_event *event, t_menu_p p)
{
	t_menu	*menu;
	int		i;

	menu = &(event->menu);
	i = 1;
	while (i < menu->sub_m_count)
	{
		if (p.type == (menu->sub_m[i]).type)
			(menu->sub_m[i]).selected = 0;
		if ((p.type == MAIN_BUTTON && (menu->sub_m[i]).type == SUB_MENU))
		{
			if (p.type_id == (menu->sub_m[i]).type_id)
				(menu->sub_m[i]).selected = 1;
			else
				(menu->sub_m[i]).selected = 0;
		}
		i++;
	}
	(menu->sub_m[p.id]).selected = 1;
	fill_menu(event, menu);
}

static void	menu_click(int index, t_event *event)
{
	t_menu_p	p;

	p = (event->menu).p[index];
	if (p.type == MAIN_BUTTON || p.type == TAB_BUTTON || p.type == OBJECT_MENU)
		handle_object_select(event, p);
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
	if (button == 1 && (x > (event->scene).width))
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
