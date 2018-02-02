/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 15:49:09 by mpauw             #+#    #+#             */
/*   Updated: 2018/02/02 16:35:31 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	set_values_render(t_scene *scene, char *s, char *value)
{
	double	*tmp;

	if (ft_strncmp(s, "name", 4) == 0)
	{
		if (!(scene->name = (char *)malloc(sizeof(char) *
						(ft_strlen(value) + 1))))
			error(1);
		ft_strcpy(scene->name, (const char *)value);
	}
	else if (ft_strncmp(s, "ambient", 7) == 0)
		scene->ambient = ft_atod(value);
	else if (ft_strncmp(s, "dimensions", 10) == 0)
	{
		if (!(tmp = (double *)malloc(2 * sizeof(double))))
			error(0);
		get_doubles_from_line(tmp, value, 2);
		scene->width = (int)(tmp[0]);
		scene->height = (int)(tmp[1]);
		free(tmp);
	}
}

void		set_render(t_scene *scene, int fd)
{
	char		*line;
	char		*s;
	char		*value;

	while (get_next_line(fd, &line) == 1)
	{
		if (*(line) == '}')
			break ;
		if (ft_isalpha(*line) || !(s = ft_brace_content(line, '{', '}')))
			error(0);
		if (!(value = ft_brace_content(s, '{', '}')))
			error(0);
		set_values_render(scene, s, value);
		free(s);
		free(value);
		free(line);
	}
	free(line);
}
