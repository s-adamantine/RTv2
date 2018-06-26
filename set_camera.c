/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_camera.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 15:43:19 by mpauw             #+#    #+#             */
/*   Updated: 2018/06/26 11:47:17 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_cam	init_def_cam(t_scene *scene)
{
	t_cam	cam;

	cam.id = scene->cam_set;
	cam.grain = scene->grain;
	cam.init = 0;
	cam.selected = 0;
	cam.origin = ft_init_3v(700, 0, 0);
	cam.rotation = ft_zero_3v();
	(scene->cam_set)++;
	return (cam);
}

static void		set_values_camera(t_cam *cam, char *s, char *value)
{
	if (ft_strncmp(s, "origin", 6) == 0)
		update_vector(&(cam->origin), value);
	else if (ft_strncmp(s, "rotation", 5) == 0)
		update_vector(&(cam->rotation), value);
}

static void		add_as_light(t_scene *scene, t_cam cam)
{
	t_source	light;
	t_intensity	i;

	if ((cam.origin).v[0] == 0)
		(cam.origin).v[0] = 1;
	light.origin = cam.origin;
	light.color = ft_zero_3v();
	i.diff = 0;
	i.spec = 0;
	light.intensity = i;
	light.id = cam.id;
	light.type = 0;
	ft_lstaddnewr(&(scene->lights), &light, sizeof(t_source));
	ft_lstaddnewr(&(scene->cameras), &cam, sizeof(t_cam));
}

void			set_camera(t_scene *scene, int fd)
{
	char	*line;
	char	*s;
	char	*value;
	int		gnl;
	t_cam	cam;

	cam = init_def_cam(scene);
	while ((gnl = get_next_line(fd, &line)) == 1)
	{
		if (*(line) == '}')
			break ;
		if (ft_isalpha(*line) || !(s = ft_brace_content(line, '{', '}')))
			error(0);
		if (!(value = ft_brace_content(s, '{', '}')))
			error(0);
		set_values_camera(&cam, s, value);
		free(s);
		free(value);
		free(line);
	}
	if (gnl < 0)
		error(0);
	free(line);
	add_as_light(scene, cam);
}
