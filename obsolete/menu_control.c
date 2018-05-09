/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 11:08:19 by mpauw             #+#    #+#             */
/*   Updated: 2018/04/13 17:25:35 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	place_sub_m(t_event *event, t_sub_m *s, t_menu *menu)
{
	int		i;
	int		j;

	i = 0;
	while (i < s->height)
	{
		j = 0;
		while (j < s->width)
		{
			if (j < s->edge_thickness || j >= s->width - s->edge_thickness ||
					i < s->edge_thickness || i >= s->height - s->edge_thickness)
				((int *)(s->img).img_arr)[j + i * s->width] = s->edge_color;
			else if (s->selected)
				((int *)(s->img).img_arr)[j + i * s->width] = s->color_selected;
			else
				((int *)(s->img).img_arr)[j + i * s->width] = s->color;
			menu->p[(j + s->x) + (i + s->y) * MENU_WIDTH].id  = s->id;
			menu->p[(j + s->x) + (i + s->y) * MENU_WIDTH].type_id  = s->type_id;
			menu->p[(j + s->x) + (i + s->y) * MENU_WIDTH].type  = s->type;
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(event->mlx, event->win,
			(s->img).img_ptr, s->x + (event->scene).width, s->y);
}

void	fill_menu(t_event *event, t_menu *menu)
{
	int		i;
	t_sub_m	*s;

	i = 0;
	while (i < menu->sub_m_count)
	{
		s = menu->sub_m[i];
		if (s->showing)
			place_sub_m(event, s, menu);
		else if (i > 0 && menu->sub_m_showing ==
				(menu->sub_m[s->parent_id])->type_id
				&& (s->sub_tab == -1 || s->sub_tab == menu->sub_tab_showing))
			place_sub_m(event, s, menu);
		i++;
	}
}

int		init_sub_menu(t_menu *menu, int parent_id)
{
	t_sub_m	*sub;

	if (!(sub = (t_sub_m *)malloc(sizeof(t_sub_m))))
		error(1);
	ft_realloc(((void **)&(menu->sub_m)), menu->sub_m_count * sizeof(t_sub_m *),
		(menu->sub_m_count + 1) * sizeof(t_sub_m *));
	menu->sub_m[menu->sub_m_count] = sub;
	sub->id = menu->sub_m_count;
	sub->showing = 0;
	sub->type = 0;
	sub->edge_thickness = 0;
	sub->selected = 0;
	sub->child_count = 0;
	sub->child_id = NULL;
	sub->parent_id = parent_id;
	(menu->sub_m_count)++;
	return (sub->id);
}

void	init_menu(t_event *event)
{
	t_menu	*menu;
	t_sub_m	*s;

	menu = &(event->menu);
	menu->sub_m = NULL;
	menu->sub_m_count = 0;
	menu->sub_m_showing = 0;
	menu->sub_tab_showing = 0;
	init_sub_menu(menu, -1);
	s = menu->sub_m[0];
	s->id = 0;
	s->showing = 1;
	s->parent_id = -1;
	s->x = 0;
	s->y = 0;
	s->width = MENU_WIDTH;
	s->height = (event->scene).height;
	s->color = PRIMARY_COLOR;
	s->color_selected = PRIMARY_COLOR;
	s->strings = NULL;
	init_image(event->mlx, s->width, s->height, &(s->img));
	if (!(menu->p = (t_menu_p *)malloc(sizeof(t_menu_p) * s->width *
				   s->height)))
		error(1);
	add_sub_menu(event);
}
