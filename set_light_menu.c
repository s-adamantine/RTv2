/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_light_menu.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 15:55:21 by mpauw             #+#    #+#             */
/*   Updated: 2018/06/26 12:53:53 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static char	*get_value(t_source *src, int i)
{
	if (i == 0)
		return (ft_itoa(src->id));
	if (i == 1)
		return (get_vector_string(src->origin, 2));
	if (i == 4)
		return (get_vector_string(src->color, 2));
	if (i == 6)
		return (ft_itoa(((int)(src->intensity).diff)));
	if (i == 7)
		return (ft_itoa(((int)(src->intensity).spec)));
	return (ft_itoa(src->id));
}

static int	get_text_color(t_source *src, t_event *event)
{
	if (event->id_select == src->id)
		return (PRIMARY);
	if (src->on)
		return (SECONDARY);
	else
		return (GRAY_2);
}

static void	add_info(t_source *src, t_event *event, int x, int y)
{
	int		i;
	int		j;
	char	*value;
	int		color;

	i = 0;
	j = 0;
	color = get_text_color(src, event);
	while (i < AMOUNT_INFO)
	{
		if (i == 2 || i == 3 || i == 5)
		{
			i++;
			continue ;
		}
		mlx_string_put(event->mlx, event->menu_win, x + SUB_MARGIN, y +
				SUB_MARGIN + j * MENU_LINE, color, (event->menu).info[i]);
		value = get_value(src, i);
		mlx_string_put(event->mlx, event->menu_win, x + INFO_MARGIN,
				y + SUB_MARGIN + j * MENU_LINE, color, value);
		free(value);
		i++;
		j++;
	}
}

void		set_light_menu(t_event *event)
{
	t_list		*lst;
	t_source	*src;
	int			i;

	lst = (event->scene).lights;
	i = 0;
	while (lst && lst->content)
	{
		src = (t_source *)lst->content;
		if (src->type)
		{
			add_info(src, event, MARGIN, TOP_BAR + MARGIN + i * LIGHT_HEIGHT);
			i++;
			if (TOP_BAR + MARGIN + i * OBJ_HEIGHT > MENU_HEIGHT)
				break ;
		}
		lst = lst->next;
	}
}
