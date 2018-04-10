/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 11:08:19 by mpauw             #+#    #+#             */
/*   Updated: 2018/04/10 18:07:07 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	place_buttons(t_event *event)
{
	t_button	button;
	int			i;
	int			row;

	i = 0;
	while (i < AMOUNT_BUTTONS)
	{
		row = i / AMT_B_PER_ROW;
		button.width = ((event->menu).width - SUB_MARGIN * 2) / AMT_B_PER_ROW;
		button.height = DEF_BUTTON_HEIGHT;
		button.x = SUB_MARGIN + (i % AMT_B_PER_ROW) * button.width;
		button.y = BAR_TOP_HEIGHT + row * DEF_BUTTON_HEIGHT;
		button.text = ((event->menu).strings).buttons[i];
		button.id = i + MAIN_BUTTON;
		button.img = init_image(event->mlx, button.width, button.height);
		if (i == (event->menu).now_showing)
			button.color = ALERT_COLOR;
		else
			button.color = PRIMARY_DARK;
		add_button(event, &button);
		if (!(event->menu).first)
			free(((event->menu).buttons[i]).img);
		(event->menu).buttons[i] = button;
		i++;
	}
}

static void	set_background(t_event *event)
{
	int		i;
	int		j;
	int		index;
	t_menu	*menu;

	i = 0;
	menu = &(event->menu);
	while (i < menu->height)
	{
		j = 0;
		while (j < menu->width)
		{
			index = j + i * menu->width;
			((int *)(menu->img)->img_arr)[index] = PRIMARY_COLOR;
			menu->p[index].id  = MAIN_MENU;
			menu->p[index].button = 0;
			j++;
		}
		i++;
	}
}

void	fill_menu(t_event *event)
{
	t_menu	*menu;

	set_background(event);
	menu = &(event->menu);
	mlx_put_image_to_window(event->mlx, event->win,
		(menu->img)->img_ptr, menu->x, menu->y);
	mlx_string_put(event->mlx, event->win, menu->x + MENU_MARGIN,
		menu->y + MENU_MARGIN, TEXT_DARK, event->scene_name);
	place_buttons(event);
	add_sub_menu(event);
	menu->first = 0;
}

void	init_menu(t_event *event)
{
	t_menu	*menu;

	menu = &(event->menu);
	menu->x = (event->scene).width;
	menu->y = 0;
	menu->width = MENU_WIDTH;
	menu->height = (event->scene).height;
	menu->img = init_image(event->mlx, menu->width, menu->height);
	menu->first = 1;
	menu->objects_set = 0;
	menu->lights_set = 0;
	menu->sub_tab_showing = 0;
	if (!(menu->p = (t_menu_p *)malloc(sizeof(t_menu_p) * menu->width *
				   menu->height)))
		error(1);
	if (!(menu->buttons = (t_button *)malloc(sizeof(t_button)
					* AMOUNT_BUTTONS)))
		error(1);
	if (!(menu->lights = (t_sub_m *)malloc(sizeof(t_sub_m) *
					(event->scene).amount_light)))
		error(1);
	set_strings(menu);
	set_background(event);
	menu->now_showing = MAIN_MENU;
}
