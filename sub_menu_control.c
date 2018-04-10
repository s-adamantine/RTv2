/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_menu_control.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 11:08:33 by mpauw             #+#    #+#             */
/*   Updated: 2018/04/10 18:25:26 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	print_instructions(t_event *event)
{
	int		i;
	int		y;
	t_menu	*menu;

	i = 0;
	menu = &(event->menu);
	y = SUB_MENU_Y + SUB_MARGIN;
	while (i < AMOUNT_INSTRUCTIONS)
	{
		mlx_string_put(event->mlx, event->win, menu->x + MENU_MARGIN,
			y, TEXT_DARK, (menu->strings).man[i]);
		i++;
		y += MENU_LINE;
	}
}

static void	init_sub_menu(t_event *event, t_menu *menu)
{
	t_sub_m	*s;

	s = &(menu->sub_m);
	s->x = menu->x + SUB_MARGIN;
	s->y = SUB_MENU_Y;
	s->height = menu->height - (SUB_MENU_Y + SUB_MARGIN * 2);
	s->width = menu->width - 2 * SUB_MARGIN;
	if (!menu->first)
		free(s->img);
	s->img = init_image(event->mlx, s->width, s->height);
	s->color = PRIMARY_LIGHT;
	s->id = SUB_MENU;
	s->tab_amount = 0;
	set_sub_menu_pixel(menu, s);
	mlx_put_image_to_window(event->mlx, event->win,
		(s->img)->img_ptr, s->x, s->y);
}

static void	add_tab_buttons(t_event *event, t_sub_m s)
{
	t_button	button;
	int			i;

	i = 0;
	while (i < s.tab_amount)
	{
		button.width = TAB_BUTTON_WIDTH;
		button.height = DEF_BUTTON_HEIGHT;
		button.x = s.width / 2 - (s.tab_amount * button.width / 2) +
			i * button.width;;
		button.y = s.height;
		button.text = ft_itoa(i + 1);
		button.id = i + TAB_BUTTON;
		button.img = init_image(event->mlx, button.width, button.height);
		if (i == (event->menu).sub_tab_showing)
			button.color = ALERT_COLOR;
		else
			button.color = PRIMARY_DARK;
		add_button(event, &button);
		i++;
	}
}

void	add_sub_menu(t_event *event)
{
	t_menu	*menu;

	menu = &(event->menu);
	init_sub_menu(event, menu);
//	if (menu->now_showing == MAIN_MENU)
//		print_(event);
	if (menu->now_showing == MAN_MENU)
		print_instructions(event);
	else if ((event->menu).now_showing == OBJECT_MENU)
		add_object_menu(event);
//		add_object_menu(event);
//	else if (menu->now_showing == LIGHT_MENU)
//		print_lights(event);
//	else if (menu->now_showing == CAM_MENU)
//		print_cam(event);
	add_tab_buttons(event, menu->sub_m);
}
