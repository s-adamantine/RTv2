/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_camera_menu.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 15:14:20 by mpauw             #+#    #+#             */
/*   Updated: 2018/06/22 16:15:52 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static char *get_value(t_cam *cam, int i)
{
	if (i == 0)
		return (ft_itoa(cam->id + 1));
	if (i == 1)
		return (get_vector_string(cam->origin, 2));
	if (i == 2)
		return (get_vector_string(cam->rotation, 2));
	return (ft_itoa(cam->id + 1));
}

static int	get_text_color(t_cam *cam, t_event *event)
{
	if (cam->selected)
		return (PRIMARY);
	else if (event->id_select == cam->id + 1)
		return (SECONDARY);
	else
		return (TEXT_D);
}

static void	add_info(t_cam *cam, t_event *event, int x, int y)
{
	int		i;
	int		j;
	char	*value;
	int		color;

	i = 0;
	j = 0;
	color = get_text_color(cam, event);
	while (i < 6)
	{
		if (i == 2 || i == 3 || i > 4)
		{
			i++;
			continue ;
		}
		mlx_string_put(event->mlx, event->menu_win, x + SUB_MARGIN, y +
				SUB_MARGIN + j * MENU_LINE, color, (event->menu).info[i]);
		value = get_value(cam, i);
		mlx_string_put(event->mlx, event->menu_win, x + INFO_MARGIN,
				y + SUB_MARGIN + j * MENU_LINE, color, value);
		free(value);
		i++;
		j++;
	}
}
void	set_cam_menu(t_event *event)
{
	t_list		*lst;
	t_cam		*cam;
	int			i;

	lst = (event->scene).cameras;
	i = 0;
	while (lst && lst->content)
	{
		cam = (t_cam *)lst->content;
		add_info(cam, event, MARGIN, TOP_BAR + MARGIN + i * CAM_HEIGHT);
		i++;
		if (TOP_BAR + MARGIN + i * OBJ_HEIGHT > MENU_HEIGHT)
			break ;
		lst = lst->next;
	}
}
