/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 15:49:09 by mpauw             #+#    #+#             */
/*   Updated: 2018/06/27 11:50:42 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	set_values_render_3(t_scene *scene, char *s, char *value)
{
	if (ft_strncmp(s, "ambient", 7) == 0)
		scene->ambient = (ft_atod(value) > MAX_AMBIENT) ? MAX_AMBIENT :
			ft_atod(value);
	else if (ft_strncmp(s, "grain", 5) == 0)
	{
		if (ft_atoi(value) < 0)
			s_error("The grain size must be larger or equal to zero.");
		scene->grain = (ft_atoi(value) > MAX_GRAIN) ? ft_power(2, MAX_GRAIN) : ft_power(2, ft_atoi(value));
	}
	else if (ft_strncmp(s, "reflection", 10) == 0)
		scene->refl = (ft_atoi(value) > MAX_REFL) ? MAX_REFL : ft_atoi(value);
}

static void	set_values_render_2(t_scene *scene, char *s, char *value)
{
	int	*tmp;

	if (ft_strncmp(s, "filter", 6) == 0)
		scene->filter = ft_atoi(value);
	else if (ft_strncmp(s, "dimensions", 10) == 0)
	{
		if (!(tmp = (int *)malloc(2 * sizeof(double))))
			error(0);
		get_int_from_line(tmp, value, 2);
		if ((int)tmp[0] <= 0 || (int)tmp[1] <= 0)
			s_error("Dimensions must be greater than 0.");
		if ((int)tmp[0] > 1280 || (int)tmp[0] < 100)
			scene->width = 1280;
		else
			scene->width = (int)(tmp[0]);
		if ((int)tmp[1] > 800 || (int)tmp[1] < 100)
			scene->height = 800;
		else
			scene->height = (int)(tmp[1]);
		scene->width /= 4;
		scene->width *= 4;
		scene->height /= 4;
		scene->height *= 4;
		free(tmp);
	}
	set_values_render_3(scene, s, value);
}

static void	set_values_render(t_scene *scene, char *s, char *value)
{
	if (ft_strncmp(s, "name", 4) == 0)
	{
		if (!(scene->name = (char *)malloc(sizeof(char) *
						(ft_strlen(value) + 1))))
			error(1);
		ft_strcpy(scene->name, (const char *)value);
	}
	set_values_render_2(scene, s, value);
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
