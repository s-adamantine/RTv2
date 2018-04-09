/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_button.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 14:13:52 by mpauw             #+#    #+#             */
/*   Updated: 2018/04/09 17:15:22 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	set_menu_pixel(t_menu *menu, int i, int j, t_button *b)
{
	int	index;

	index = j + i * menu->width;
	menu->p[index].button = 1;
	menu->p[index].id = b->id;
	menu->p[index].color = b->color;
}

void	add_button(t_event *event, t_button *b)
{
	t_menu	*menu;
	int		*img_arr;
	int		i;
	int		j;

	menu = &(event->menu);
	i = 0;
	img_arr = ((int *)(b->img)->img_arr);	
	while (i < b->height)
	{
		j = 0;
		while (j < b->width)
		{
			img_arr[j + i * b->width] = b->color;
			if (i < 1 || j < 1 || i > b->height - 2 || j > b->width - 2)
				img_arr[j + i * b->width] = TEXT_LIGHT;
			set_menu_pixel(menu, b->y + i, b->x + j, b);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(event->mlx, event->win,
		(b->img)->img_ptr, menu->x + b->x, menu->y + b->y);
	mlx_string_put(event->mlx, event->win, menu->x + b->x + SUB_SUB_MARGIN,
			menu->y + b->y + SUB_SUB_MARGIN, TEXT_LIGHT, b->text);
}
