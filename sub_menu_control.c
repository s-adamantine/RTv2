/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_menu_control.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 11:08:33 by mpauw             #+#    #+#             */
/*   Updated: 2018/04/09 18:09:22 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	print_instructions(t_event *event)
{
	int	i;
	int	y;
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

void		set_sub_menu_pixel(t_menu *menu, t_sub_m *sub_m)
{
	int	i;
	int	j;
	int	index;

	i = 0;
	while (i < sub_m->height)
	{
		j = 0;
		while (j < sub_m->width)
		{
			((int *)(sub_m->img)->img_arr)[j + i * sub_m->width] = sub_m->color;
			index = sub_m->x + j + (sub_m->y + i) * menu->width;
			menu->p[index].button = 1;
			menu->p[index].id = sub_m->id;
			menu->p[index].color = sub_m->color;
			menu->p[index].id = sub_m->id;
			menu->p[index].button = 0;
			j++;
		}
		i++;
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
	s->img = init_image(event->mlx, s->width, s->height);
	s->color = PRIMARY_LIGHT;
	s->id = SUB_MENU;
	set_sub_menu_pixel(menu, s);
	mlx_put_image_to_window(event->mlx, event->win,
		(s->img)->img_ptr, s->x, s->y);
}

void	add_sub_menu(t_event *event)
{
	t_menu	*menu;

	menu = &event->menu;
	init_sub_menu(event, menu);
//	if (menu->now_showing == MAIN_MENU)
//		print_(event);
	if (menu->now_showing == MAN_MENU)
		print_instructions(event);
	else if (menu->now_showing == OBJECT_MENU)
		add_object_menu(event);
//	else if (menu->now_showing == LIGHT_MENU)
//		print_lights(event);
//	else if (menu->now_showing == CAM_MENU)
//		print_cam(event);
}
