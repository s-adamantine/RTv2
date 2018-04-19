/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_movement.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 16:15:17 by mpauw             #+#    #+#             */
/*   Updated: 2018/03/21 15:56:16 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	set_drag_angle(t_event *event, int x, int y)
{
	t_cam		*cam;
	t_3v		new_rot;
	double		d;

	cam = (event->scene).cam;
	d = sqrt((cam->origin).v[0] * (cam->origin).v[0] + (cam->origin).v[1]
			* (cam->origin).v[1] + (cam->origin).v[2] * (cam->origin).v[2]);
	new_rot.v[1] = DEG * (atan(event->y_0 / d) - atan(y / d));
	new_rot.v[2] = DEG * (atan(event->x_0 / d) - atan(x / d));
	new_rot.v[1] = fmod((cam->rotation).v[1], 360);
	new_rot.v[2] = fmod((cam->rotation).v[2], 360);
}
/*
void	set_move(t_event *event, int move)
{
	int			i;
	t_3v		dir;
	t_cam		*cam;
	t_list		*lst;
	t_object	*object;

	if (abs(move) == 1)
		dir = ft_init_3v(1, 0, 0);
	else
		dir = ft_init_3v(0, 0.5, 0);
	cam = (event->scene).cam;
	i = 2;
	while (i >= 0)
	{
		ft_rotate_3v(&dir, i, -((cam->rotation).v[i]), 0);
		i--;
	}
	ft_3v_scalar_p(&dir, move * 20);
	cam->origin = ft_3v_add(cam->origin, dir);
	lst = (event->scene).objects;
	while (lst && lst->content)
	{
		object = (t_object *)(lst->content);
		rotate_object(object, &(event->scene), 1);
		lst = lst->next;
	}
}
*/
