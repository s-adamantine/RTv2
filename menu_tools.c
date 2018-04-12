/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 16:38:21 by mpauw             #+#    #+#             */
/*   Updated: 2018/04/11 16:25:34 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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
			((int *)(sub_m->img).img_arr)[j + i * sub_m->width] = sub_m->color;
			index = sub_m->x + j + (sub_m->y + i) * (menu->sub_m[0]).width;
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

void	set_sub_tab_number(t_sub_m *parent, t_sub_m *child, int i)
{
	int	height;

	height = parent->height - DEF_BUTTON_HEIGHT - 2 * SUB_MARGIN;
	if (child->height + SUB_MARGIN == 0)
		error(6);
	parent->per_tab = height / (child->height + SUB_MARGIN);
	parent->tab_amount = ceil(((double)(i + 1)) / parent->per_tab);
	child->sub_tab = i / parent->per_tab;
	child->position = i % parent->per_tab;
}
