/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_camera.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 15:43:19 by mpauw             #+#    #+#             */
/*   Updated: 2018/02/02 16:35:30 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	set_values_camera(t_source *cam, char *s, char *value)
{
	if (ft_strncmp(s, "origin", 6) == 0)
		update_vector(&(cam->origin), value);
	else if (ft_strncmp(s, "rotation", 5) == 0)
		update_vector(&(cam->rotation), value);
}

void		set_camera(t_scene *scene, int fd)
{
	char	*line;
	char	*s;
	char	*value;

	if (scene->cam_set)
		return ;
	while (get_next_line(fd, &line) == 1)
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
	free(line);
	scene->cam_set = 1;
}
