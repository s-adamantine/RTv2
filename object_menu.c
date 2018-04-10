/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_menu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 17:51:37 by mpauw             #+#    #+#             */
/*   Updated: 2018/04/10 18:21:25 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static char *get_value(t_object *obj, int i)
{
	t_3v	tmp;

	if (i == 0)
		return (get_vector_string(obj->origin, 2));
	if (i == 1)
		return (get_vector_string(obj->rotation, 2));
	if (i == 2)
		return (ft_dtoa(obj->radius, 2));
	if (i == 3)
		return (get_vector_string(obj->color, 2));
	if (i == 4)
		return (ft_itoa(obj->id));
	tmp.v[0] = obj->ambient;
	tmp.v[1] = obj->diffuse;
	tmp.v[2] = obj->specular;
	return (get_vector_string(tmp, 2));
}

static void	add_info(t_object *obj, t_event *event, int x, int y)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	j = 0;
	while (i < AMOUNT_INFO)
	{
		if ((i == 1 && obj->type == 1) || (i == 2 && obj->type == 0))
		{
			i++;
			continue ;
		}
		mlx_string_put(event->mlx, event->win, x + SUB_SUB_MARGIN,
				y + SUB_MARGIN + (j + 1) * MENU_LINE, TEXT_LIGHT,
				((event->menu).strings).info[i]);
		value = get_value(obj, i);
		mlx_string_put(event->mlx, event->win, x + INFO_MARGIN,
				y + SUB_MARGIN + (j + 1) * MENU_LINE, TEXT_LIGHT, value);
		free(value);
		i++;
		j++;
	}
}

static void	create_obj_sub_menu(t_object *obj, t_event *event, int i)
{
	t_sub_m	*s;
	t_sub_m	*menu;

	menu = &((event->menu).sub_m);
	s = &(((event->menu).objects)[i]);
	if ((event->menu).objects_set)
	{
		set_sub_tab_number(menu, s, i);
		return ;
	}
	s->height = 125;
	set_sub_tab_number(menu, s, i);
	s->width = menu->width - 2 * SUB_SUB_MARGIN;
	s->x = menu->x + SUB_SUB_MARGIN;
	s->y = menu->y + SUB_SUB_MARGIN + s->position
		* (s->height + SUB_SUB_MARGIN);
	s->img = init_image(event->mlx, s->width, s->height);
	s->color = PRIMARY_COLOR;
	s->id = obj->id;
	set_sub_menu_pixel(&(event->menu), s);
}

static void	put_sub_sub_to_window(t_event *event, t_object *obj, int i)
{
	t_sub_m		*s;

	s = &(((event->menu).objects)[i]);
	if ((event->menu).sub_tab_showing != s->sub_tab)
		return ;
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
	t_menu		*menu;
	static int	first = 1;

	lst = (event->scene).objects;
	i = 0;
	menu = &(event->menu);
	if (first && !(menu->objects = (t_sub_m *)malloc(sizeof(t_sub_m) *
					(event->scene).amount_obj)))
		error(1);
	while (lst && lst->content)
	{
		obj = (t_object *)lst->content;
		create_obj_sub_menu(obj, event, i);
		put_sub_sub_to_window(event, obj, i);
		i++;
		lst = lst->next;
	}
	first = 0;
	menu->objects_set = 1;
}
