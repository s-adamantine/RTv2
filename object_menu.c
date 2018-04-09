/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_menu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 17:51:37 by mpauw             #+#    #+#             */
/*   Updated: 2018/04/09 19:02:23 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static char	*get_value(t_object *obj, int i)
{
	char	*value;
	int		j;
	t_3v	v;

	j = 0;
	value = ft_strdup("");
	if (i == 0 || i == 1 || i == 3)
	{
		v = (i == 0) ? obj->origin : obj->rotation;
		v = (i == 3) ? obj->color : v;
		while (j < 3)
		{
			value = ft_strcat(value, ft_itoa((int)v.v[j]));
			value = ft_strcat(value, ft_strdup(" "));
			j++;
		}
	}
	else if (i == 2)
		value = ft_itoa(obj->radius);
	else if (i == 4)
		value = ft_itoa(obj->id);
	return (value);
}

static void	add_info(t_object *obj, t_event *event, int x, int y)
{
	int		i;

	i = 0;
	while (i < AMOUNT_INFO)
	{
		mlx_string_put(event->mlx, event->win, x + SUB_SUB_MARGIN,
				y + SUB_MARGIN + (i + 1) * MENU_LINE, TEXT_LIGHT,
				ft_strcat(ft_strdup(((event->menu).strings).info[i]),
					get_value(obj, i)));
		i++;
	}
}

static void	create_obj_sub_menu(t_object *obj, t_event *event, int i)
{
	t_sub_m	*s;
	t_sub_m	*menu;

	menu = &((event->menu).sub_m);
	s = &(((event->menu).objects)[i]);
	s->height = 125;
	s->width = menu->width - 2 * SUB_SUB_MARGIN;
	s->x = menu->x + SUB_SUB_MARGIN;
	s->y = menu->y + SUB_SUB_MARGIN + i * (s->height + SUB_SUB_MARGIN);
	s->img = init_image(event->mlx, s->width, s->height);
	s->color = PRIMARY_COLOR;
	s->id = obj->id;
	set_sub_menu_pixel(&(event->menu), s);
	mlx_put_image_to_window(event->mlx, event->win,
		(s->img)->img_ptr, s->x, s->y);
	mlx_string_put(event->mlx, event->win, s->x + SUB_SUB_MARGIN, s->y +
			SUB_SUB_MARGIN, TEXT_LIGHT,
			((event->menu).strings).types[obj->type]);
	add_info(obj, event, s->x, s->y);
}

void		add_object_menu(t_event *event)
{
	t_list		*lst;
	t_object	*obj;
	int			i;

	lst = (event->scene).objects;
	i = 0;
	while (lst && lst->content)
	{
		obj = (t_object *)lst->content;
		create_obj_sub_menu(obj, event, i);
		i++;
		lst = lst->next;
	}
}
