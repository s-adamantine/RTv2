/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_movement.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 16:15:17 by mpauw             #+#    #+#             */
/*   Updated: 2018/02/08 13:42:35 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	set_drag_angle(t_event *event, int x, int y)
{
	t_cam		*cam;
	t_list		*lst;
	t_object	*object;
	double		d;
	int			z_neg;

	cam = &((event->scene).camera);
	d = sqrt((cam->origin).v[0] * (cam->origin).v[0] + (cam->origin).v[1]
			* (cam->origin).v[1] + (cam->origin).v[2] * (cam->origin).v[2]);
	z_neg = 1;
	if (fmod((cam->rotation).v[2], 360) > 90 && fmod((cam->rotation).v[2], 360)
			< 270)
		z_neg = -1;
	(cam->rotation).v[1] += z_neg * DEG * (atan(event->y_0 / d) - atan(y / d));
	(cam->rotation).v[2] += DEG * (atan(event->x_0 / d) - atan(x / d));
	(cam->rotation).v[1] = fmod((cam->rotation).v[1], 360);
	(cam->rotation).v[2] = fmod((cam->rotation).v[2], 360);
	lst = (event->scene).objects;
	while (lst && lst->content)
	{
		object = (t_object *)(lst->content);
		rotate_object(object, &(event->scene), 1);
		lst = lst->next;
	}
}


