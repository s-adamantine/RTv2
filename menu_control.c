/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 11:08:19 by mpauw             #+#    #+#             */
/*   Updated: 2018/04/11 19:14:41 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	place_sub_m(t_event *event, t_sub_m *s, t_menu *menu)
{
	int		i;
	int		j;
	int		index;

	i = 0;
	while (i < s->height)
	{
		j = 0;
		while (j < s->width)
		{
			index = j + i * s->width;
			((int *)(s->img).img_arr)[index] = s->color;
			menu->p[index].id  = s->id;
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(event->mlx, event->win,
		(s->img).img_ptr, s->x, s->y);
}

void	fill_menu(t_event *event, t_menu *menu)
{
	int		i;
	t_sub_m	*s;

	i = 0;
	add_sub_menu(event);
	while (i < menu->sub_m_count)
	{
		s = &(menu->sub_m[i]);
		if (s->showing)
		{
			place_sub_m(event, s, menu);
//			if (s->strings)
//				place_sub_strings(event, s);
		}
		i++;
	}
}

int		init_sub_menu(t_menu *menu, int parent_id)
{
	t_sub_m	parent;
	t_sub_m	sub;

	sub.id = menu->sub_m_count;
	sub.showing = 0;
	sub.first = 1;
	sub.type = 0;
	if (parent_id > 0)
	{
		parent = menu->sub_m[parent_id];
		sub.x = parent.x;
		sub.y = parent.y;
		sub.width = parent.width;
		sub.height = parent.height;
		sub.color = parent.color;
		sub.strings = NULL;
		sub.img = parent.img;
		sub.parent_id = parent_id;
	}
	ft_realloc(((void **)&(menu->sub_m)), menu->sub_m_count * sizeof(t_sub_m),
			(menu->sub_m_count + 1) * sizeof(t_sub_m));
	menu->sub_m[menu->sub_m_count] = sub;
	(menu->sub_m_count)++;
	return (sub.id);
}

void	init_menu(t_event *event)
{
	t_menu	*menu;
	t_sub_m	*s;

	menu = &(event->menu);
	menu->sub_m = NULL;
	menu->sub_m_count = 0;
	init_sub_menu(menu, 0);
	s = &(menu->sub_m[0]);
	s->id = 0;
	s->showing = 1;
	s->first = 1;
	s->parent_id = -1;
	s->x = (event->scene).width;
	s->y = 0;
	s->width = MENU_WIDTH;
	s->height = (event->scene).height;
	s->color = PRIMARY_COLOR;
	s->strings = NULL;
	init_image(event->mlx, s->width, s->height, &(s->img));
	if (!(menu->p = (t_menu_p *)malloc(sizeof(t_menu_p) * s->width *
				   s->height)))
		error(1);
}
