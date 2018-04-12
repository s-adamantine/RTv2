/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_menu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 17:51:37 by mpauw             #+#    #+#             */
/*   Updated: 2018/04/11 17:35:30 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
/*
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
*/
static void	create_obj_sub_menu(t_object *obj, t_event *event, int i,
		t_sub_m *s)
{
	t_menu	*menu;
	t_sub_m	*parent;

	menu = &(event->menu);
	parent = &(menu->sub_m[s->parent_id]);
	s->height = OBJ_SUB_M_HEIGHT;
	set_sub_tab_number(parent, s, i);
	s->width = parent->width - 2 * SUB_SUB_MARGIN;
	s->x = parent->x + SUB_SUB_MARGIN;
	s->y = parent->y + SUB_SUB_MARGIN + s->position
		* (s->height + SUB_SUB_MARGIN);
	init_image(event->mlx, s->width, s->height, &(s->img));
	s->color = PRIMARY_LIGHT;
	s->type = OBJECT_MENU;
	s->type_id = obj->id;
	set_sub_menu_pixel(&(event->menu), s);
}

void		add_object_menu(t_event *event, t_sub_m parent, t_menu *menu)
{
	t_list		*lst;
	t_object	*obj;
	int			i;
	int			id;

	lst = (event->scene).objects;
	i = 0;
	while (lst && lst->content)
	{
		obj = (t_object *)lst->content;
		id = init_sub_menu(menu, parent.id);
		create_obj_sub_menu(obj, event, i, &(menu->sub_m[id]));
		i++;
		lst = lst->next;
	}
}
