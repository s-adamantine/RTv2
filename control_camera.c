/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_camera.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 14:12:01 by mpauw             #+#    #+#             */
/*   Updated: 2018/05/09 14:25:24 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
 * Change the camera. If it has not been initialized: initialize!
 */

static t_cam	*get_selected_cam(t_scene *scene, int id)
{
	t_list	*tmp_cam;
	t_cam	*cam;
	static int	a = 0;

	a++;
	if (id >= scene->cam_set)
		return (NULL);
	tmp_cam = scene->cameras;
	while (tmp_cam && tmp_cam->content)
	{
		cam = (t_cam *)tmp_cam->content;
		if (cam->id == id)
			return (cam);
		tmp_cam = tmp_cam->next;
	}
	return (NULL);
}

void			change_camera(t_event *event)
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
		set_t_values(event);
		init_light_values((void *)event);
	}
	turn_on_lights(event);
	event->redraw = 1;
}
