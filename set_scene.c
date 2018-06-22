/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicola <nicola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 16:41:28 by mpauw             #+#    #+#             */
/*   Updated: 2018/06/21 18:25:58 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	init_def_scene(t_scene *scene)
{
	if (!(scene->objects = ft_lstnew(NULL, 0)) ||
			!(scene->lights = ft_lstnew(NULL, 0)) ||
			!(scene->cameras = ft_lstnew(NULL, 0)) ||
			!(scene->patterns = ft_lstnew(NULL, 0)) ||
			!(scene->materials = ft_lstnew(NULL, 0)))
		error(1);
	scene->name = "Default Scene";
	scene->amount_obj = 0;
	scene->amount_light = 0;
	scene->width = 1080;
	scene->height = 800;
	scene->wait = 0.5;
	scene->refl = 2;
	scene->filter = 0;
	scene->cam_set = 0;
	scene->ambient = 0.5;
	scene->grain = 1;
	scene->anti_a = 1;
	scene->max_anti_a = 2;
	scene->step_size = scene->grain > 1 ? scene->grain :
		scene->anti_a;
	scene->source_id = 0;
	scene->thread_id = 0;
	scene->set = 0;
	set_material(scene);
	set_pattern(scene);
}

void		set_scene(int fd, t_scene *scene)
{
	char	*line;
	int		gnl;

	init_def_scene(scene);
	while ((gnl = get_next_line(fd, &line)) == 1)
	{
		if (ft_strncmp(line, "render {", 8) == 0)
			set_render(scene, fd);
		else if (ft_strncmp(line, "camera {", 8) == 0)
			set_camera(scene, fd);
		else if (ft_strncmp(line, "light {", 7) == 0)
			add_light(scene, fd);
		else if (ft_strncmp(line, "object {", 8) == 0)
			set_object(&(scene->objects), scene,
					scene->amount_obj, fd);
		free(line);
	}
	if (gnl < 0)
		error(0);
	free(line);
	scene->cam = (t_cam *)(scene->cameras)->content;
	if (!(scene->grain))
		scene->grain = (scene->amount_obj && scene->amount_light) ?
			scene->amount_obj * scene->amount_light : 1;
	scene->step_size = scene->grain * scene->max_anti_a;
}
