/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_object_menu.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 13:39:34 by mpauw             #+#    #+#             */
/*   Updated: 2018/06/22 17:05:34 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static char *get_value(t_object *obj, int i)
{
	t_3v	tmp;

	if (i == 0)
		return (ft_itoa(obj->id + 1));
	if (i == 1)
		return (get_vector_string(obj->origin, 2));
	if (i == 2)
		return (get_vector_string(obj->rotation, 2));
	if (i == 3)
		return (ft_dtoa(obj->radius, 2));
	if (i == 4)
		return (get_vector_string(obj->m.color, 2));
	tmp.v[0] = obj->m.ambient;
	tmp.v[1] = obj->m.diffuse;
	tmp.v[2] = obj->m.specular;
	return (get_vector_string(tmp, 2));
}

static void	add_info(t_object *obj, t_event *event, int x, int y)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	j = 1;
	mlx_string_put(event->mlx, event->menu_win, x + SUB_MARGIN,
			y + SUB_MARGIN, TEXT_D, (event->menu).types[obj->type]);
	while (i < AMOUNT_INFO)
	{
		if ((i == 3 && obj->type == 0) || i > 5)
		{
			i++;
			continue ;
		}
		mlx_string_put(event->mlx, event->menu_win, x + SUB_MARGIN,
				y + SUB_MARGIN + j * MENU_LINE, TEXT_D,
				(event->menu).info[i]);
		value = get_value(obj, i);
		mlx_string_put(event->mlx, event->menu_win, x + INFO_MARGIN,
				y + SUB_MARGIN + j * MENU_LINE, TEXT_D, value);
		free(value);
		i++;
		j++;
	}
}
void	set_object_menu(t_event *event)
{
	t_list		*lst;
	t_object	*obj;
	int			i;

	lst = (event->scene).objects;
	i = 0;
	while (lst && lst->content)
	{
		obj = (t_object *)lst->content;
		add_info(obj, event, MARGIN, TOP_BAR + MARGIN + i * OBJ_HEIGHT);
		i++;
		if (TOP_BAR + 2 * MARGIN + (i + 1) * OBJ_HEIGHT > MENU_HEIGHT)
			break ;
		lst = lst->next;
	}
}
