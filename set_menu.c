/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_menu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 12:22:49 by mpauw             #+#    #+#             */
/*   Updated: 2018/06/26 11:51:34 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	print_instructions(t_event *event)
{
	int		i;
	int		y;
	t_menu	*menu;

	i = 0;
	menu = &(event->menu);
	y = TOP_BAR + MARGIN + SUB_MARGIN;
	while (i < AMOUNT_INSTRUCTIONS)
	{
		mlx_string_put(event->mlx, event->menu_win, MARGIN + SUB_MARGIN,
			y, TEXT_D, menu->man[i]);
		i++;
		y += MENU_LINE;
	}
}

void		set_menu(t_event *event)
{
	int		i;
	int		j;
	t_img	*img;

	img = &(event->menu_img);
	i = -1;
	while (++i < MENU_HEIGHT)
	{
		j = -1;
		while (++j < MENU_WIDTH)
		{
			if (i < TOP_BAR)
				((int *)(img->img_arr))[j + i * img->size_line_int] = PRIMARY;
			else if (i < TOP_BAR + MARGIN || i > MENU_HEIGHT - MARGIN
					|| j < MARGIN || j > MENU_WIDTH - MARGIN)
				((int *)(img->img_arr))[j + i * img->size_line_int] = GRAY;
			else
				((int *)(img->img_arr))[j + i * img->size_line_int] = TEXT_L;
		}
	}
	mlx_put_image_to_window(event->mlx, event->menu_win,
		(event->menu_img).img_ptr, 0, 0);
	mlx_string_put(event->mlx, event->menu_win,
			MARGIN, MARGIN, TEXT_L, event->scene.name);
}

void		change_menu(t_event *event)
{
	set_menu(event);
	if (event->instructions)
		print_instructions(event);
	else if (event->t_select == KEY_O)
		set_object_menu(event);
	else if (event->t_select == KEY_L)
		set_light_menu(event);
	else if (event->t_select == KEY_C)
		set_cam_menu(event);
}

void		init_menu(t_event *event)
{
	event->instructions = 1;
	set_strings(&(event->menu));
	set_menu(event);
	change_menu(event);
}
