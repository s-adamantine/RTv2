/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_camera.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 15:43:19 by mpauw             #+#    #+#             */
/*   Updated: 2018/02/07 15:58:34 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	set_values_camera(t_cam *cam, char *s, char *value)
{
	if (ft_strncmp(s, "origin", 6) == 0)
		update_vector(&(cam->origin), value);
	else if (ft_strncmp(s, "rotation", 5) == 0)
		update_vector(&(cam->rotation), value);
}

static void add_as_light(t_scene *scene)
{
	t_source	light;
	t_intensity	i;

	if (((scene->camera).origin).v[0] == 0)
		((scene->camera).origin).v[0] = 1;
	light.origin = (scene->camera).origin;
	light.color = ft_zero_3v();
	light.rotation = ft_zero_3v();
	i.diff = 0;
	i.spec = 0;
	light.intensity = i;
	light.id = 0;
	light.type = 0;
	ft_lstaddnewr(&(scene->lights), &light, sizeof(t_source));
}

void		set_camera(t_scene *scene, int fd)
{
	char	*line;
	char	*s;
	char	*value;
	int		gnl;

	if (scene->cam_set)
		return ;
	while ((gnl = get_next_line(fd, &line)) == 1)
	{
		if (*(line) == '}')
			break ;
		if (ft_isalpha(*line) || !(s = ft_brace_content(line, '{', '}')))
			error(0);
		if (!(value = ft_brace_content(s, '{', '}')))
			error(0);
		set_values_camera(&(scene->camera), s, value);
		free(s);
		free(value);
		free(line);
	}
	if (gnl < 0)
		error(0);
	free(line);
	scene->cam_set = 1;
	add_as_light(scene);
}
