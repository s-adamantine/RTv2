/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_camera.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 14:12:01 by mpauw             #+#    #+#             */
/*   Updated: 2018/06/26 11:48:53 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** Change the camera. If it has not been initialized: initialize!
*/

static t_cam	*get_selected_cam(t_scene *scene, int id)
{
	t_list		*tmp_cam;
	t_cam		*cam;
	static int	a = 0;

	a++;
	if (id >= scene->cam_set)
		return (NULL);
	tmp_cam = scene->cameras;
	while (tmp_cam && tmp_cam->content)
	{
		cam = (t_cam *)tmp_cam->content;
		if (cam->id == id)
		{
			(scene->cam)->selected = 0;
			cam->selected = 1;
			return (cam);
		}
		tmp_cam = tmp_cam->next;
	}
	return (NULL);
}

void			change_camera(t_event *event)
{
	t_scene	*scene;

	scene = &(event->scene);
	if ((scene->cam)->id == event->id_select - 1
		|| event->id_select > scene->cam_set || event->id_select == 0)
		return ;
	if (!(scene->cam = get_selected_cam(scene, event->id_select - 1)))
		return ;
	if (!((scene->cam)->init))
	{
		if (!((scene->cam)->p_array = (t_pixel *)malloc(sizeof(t_pixel)
					* scene->width * scene->height *
					scene->max_anti_a * scene->max_anti_a)) ||
				!((scene->cam)->pixel_set = (int *)malloc(sizeof(int)
					* scene->width * scene->height
					* scene->max_anti_a * scene->max_anti_a)))
			error(1);
		ft_bzero((scene->cam)->pixel_set, sizeof(int) * scene->width
			* scene->height * scene->max_anti_a * scene->max_anti_a);
		set_fixed_values(scene);
		create_threads(event, set_t_values);
		init_light_values((void *)event);
	}
	turn_on_lights(event);
	event->redraw = 1;
}
