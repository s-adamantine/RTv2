/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 14:03:26 by mpauw             #+#    #+#             */
/*   Updated: 2018/05/07 18:14:35 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	change_camera(t_event *event)
{
	t_scene	*scene;
	t_cam	*cam;

	scene = &(event->scene);
	if ((scene->cam)->id == event->id_select - 1)
		return ;
	if (!(cam = get_selected_cam(scene, event->id_select - 1)))
		return ;
	scene->cam = cam;
	if (!(cam->init))
	{
		if (!(cam->p_array = (t_pixel *)malloc(sizeof(t_pixel)
					* scene->width * scene->height)) ||
				!(cam->pixel_set = (int *)malloc(sizeof(int)
					* scene->width * scene->height)))
			error(1);
		ft_bzero(cam->pixel_set, sizeof(int) * scene->width * scene->height);
		set_fixed_values(scene);
		light_inside(scene);
		get_s_values(event);
		init_light_values((void *)event);
	}
	turn_on_lights(event);
	event->redraw = 1;
}
