/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_click.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 18:01:45 by mpauw             #+#    #+#             */
/*   Updated: 2018/04/13 17:25:38 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
/*
static void	set_children_showing(t_menu *menu, int id)
{
	t_sub_m	*s;
	t_sub_m	*child;
	int		i;

	s = (menu->sub_m)[id];
	i = 0;
	while (i < s->child_count)
	{
		child = (menu->sub_m)[s->child_id[i]];
		if (s->sub_tab_showing == child->sub_tab)
			child->showing = 1;
		i++;
	}
}

static void	set_parents_showing(t_menu *menu, int id)
{
	if (id == 0)
		return ;
	((menu->sub_m)[id])->showing = 1;
	set_parents_showing(menu, ((menu->sub_m)[id])->parent_id);
}
*/
static void	handle_button_click(t_event *event, t_menu_p p)
{
	t_menu	*menu;
	int		i;

	menu = &(event->menu);
	i = 1;
	while (i < menu->sub_m_count)
	{
		if (p.type == (menu->sub_m[i])->type)
			(menu->sub_m[i])->selected = 0;
		i++;
	}
	if (p.type == TAB_BUTTON)
		menu->sub_tab_showing = p.type_id;
	else if (p.type == MAIN_BUTTON)
	{
		menu->sub_m_showing = p.type_id;
		menu->sub_tab_showing = 0;
	}
	(menu->sub_m[p.id])->selected = 1;
	fill_menu(event, menu);
}

void		menu_click(int index, t_event *event)
{
	t_menu_p	p;

	p = (event->menu).p[index];
	if (p.type == MAIN_BUTTON || p.type == TAB_BUTTON || p.type == OBJECT_MENU)
		handle_button_click(event, p);
}
