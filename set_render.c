/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 15:49:09 by mpauw             #+#    #+#             */
/*   Updated: 2018/02/06 08:36:36 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	set_values_render_2(t_scene *scene, char *s, char *value)
{
	if (ft_strncmp(s, "ambient", 7) == 0)
		scene->ambient = ft_atod(value);
	else if (ft_strncmp(s, "grain", 5) == 0)
		scene->grain = ft_atoi(value);
	else if (ft_strncmp(s, "anti_a", 6) == 0)
		scene->max_anti_a = ft_atod(value);
	else if (ft_strncmp(s, "wait", 4) == 0)
		scene->wait = ft_atod(value);
	else if (ft_strncmp(s, "reflection", 10) == 0)
		scene->refl = ft_atoi(value);
}

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
	if (ft_strncmp(s, "ambient", 7) == 0 || ft_strncmp(s, "grain", 5) == 0 ||
			ft_strncmp(s, "anti_a", 6) == 0 || ft_strncmp(s, "wait", 4) == 0
		|| ft_strncmp(s, "reflection", 10) == 0)
		set_values_render_2(scene, s, value);
	else if (ft_strncmp(s, "filter", 6) == 0)
		scene->filter = ft_atoi(value);
	else if (ft_strncmp(s, "dimensions", 10) == 0)
	{
		if (!(tmp = (double *)malloc(2 * sizeof(double))))
			error(0);
		get_doubles_from_line(tmp, value, 2);
		scene->width = (int)(tmp[0]);
		scene->height = (int)(tmp[1]);
		if (scene->width > 2048 || scene->height > 2048)
			s_error("Are you sure you want your window to be that big?");
		free(tmp);
	}
}

void		set_render(t_scene *scene, int fd)
{
	char		*line;
	char		*s;
	char		*value;
	int			gnl;

	while ((gnl = get_next_line(fd, &line)) == 1)
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
	if (gnl < 0)
		error(0);
	free(line);
}
