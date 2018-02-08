/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_movement.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 16:15:17 by mpauw             #+#    #+#             */
/*   Updated: 2018/02/08 12:13:37 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_3v	get_angle(t_event *event, int x, int y)
{
	double	d;
	t_3v	rotation;
	t_3v	origin;

	origin = ((event->scene).camera).origin;
	d = sqrt(origin.v[0] * origin.v[0] + origin.v[1] * origin.v[1] +
			origin.v[2] * origin.v[2]);
	rotation.v[0] = 0;
	rotation.v[1] = DEG * (atan(event->y_0 / d) - atan(y / d));
	rotation.v[2] = DEG * (atan(event->x_0 / d) - atan(x / d));
	return (rotation);
}

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
	printf("%f %f\n", (cam->rotation).v[1], (cam->rotation).v[2]);
	cam->rotation = ft_3v_add(get_angle(event, x, y), cam->rotation);	
	(cam->rotation).v[1] = fmod((cam->rotation).v[1], 360);
	(cam->rotation).v[2] = fmod((cam->rotation).v[2], 360);
	lst = (event->scene).objects;
	printf("%f %f\n\n", (cam->rotation).v[1], (cam->rotation).v[2]);
	while (lst && lst->content)
	{
		object = (t_object *)(lst->content);
		rotate_object(object, &(event->scene), 1);
		lst = lst->next;
	}
}
