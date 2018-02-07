/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_movement.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 16:15:17 by mpauw             #+#    #+#             */
/*   Updated: 2018/02/07 17:00:08 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	set_drag_angle(t_event *event, int x, int y)
{
	t_cam		*cam;
	int			dif_y;
	int			dif_x;
	t_list		*lst;
	t_object	*object;

	cam = &((event->scene).camera);
	dif_x = event->x_0 - x;
	dif_y = event->y_0 - y;
	(cam->rotation).v[1] += RAD_TO_DEG * atan(dif_y / ((cam->origin).v[0]));
	(cam->rotation).v[2] += RAD_TO_DEG * atan(dif_x / ((cam->origin).v[0]));
	lst = (event->scene).objects;
	while (lst && lst->content)
	{
		object = (t_object *)(lst->content);
		rotate_object(object, &(event->scene), 1);
		lst = lst->next;
	}
}
