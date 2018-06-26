/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pattern.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 16:21:20 by mpauw             #+#    #+#             */
/*   Updated: 2018/06/26 11:52:09 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	init_def_pattern(t_pattern *p, int id)
{
	p->id = id;
	p->type = 0;
	p->size = 0.05;
	p->distance = 2;
	p->os_1 = 0;
	p->os_2 = 0;
	p->amount_points = 25;
}

static void	set_values_pattern(t_pattern *p, char *s, char *value)
{
	if (ft_strncmp(s, "type", 4) == 0)
		p->type = ft_atoi(value);
	else if (ft_strncmp(s, "size", 4) == 0)
		p->size = ft_atod(value);
	else if (ft_strncmp(s, "distance", 8) == 0)
		p->distance = ft_atod(value);
	else if (ft_strncmp(s, "amount_points", 13) == 0)
		p->amount_points = ft_atoi(value);
	else if (ft_strncmp(s, "offset_1", 8) == 0)
		p->os_1 = ft_atod(value);
	else if (ft_strncmp(s, "offset_2", 8) == 0)
		p->os_2 = ft_atod(value);
	if (p->distance <= 0)
		p->distance = 2;
	free(s);
	free(value);
}

static void	add_pattern(t_scene *scene, int fd)
{
	char		*line;
	char		*s;
	char		*value;
	t_pattern	p;
	int			gnl;

	init_def_pattern(&p, scene->amount_pattern);
	while ((gnl = get_next_line(fd, &line)) == 1)
	{
		if (*(line) == '}')
			break ;
		if (ft_isalpha(*line) || !(s = ft_brace_content(line, '{', '}')))
			error(0);
		if (!(value = ft_brace_content(s, '{', '}')))
			error(0);
		set_values_pattern(&p, s, value);
		free(line);
	}
	if (gnl < 0)
		error(0);
	free(line);
	if (p.type == 1 && p.amount_points > 0)
		set_point_list(&p);
	(scene->amount_pattern)++;
	ft_lstaddnewr(&(scene->patterns), &p, sizeof(p));
}

void		set_pattern(t_scene *scene)
{
	int			fd;
	t_pattern	p;
	char		*line;
	int			gnl;

	init_def_pattern(&p, 0);
	scene->amount_pattern = 1;
	ft_lstaddnewr(&(scene->patterns), &p, sizeof(p));
	if ((fd = open("materials/patterns", O_RDONLY)) == -1)
		return ;
	while ((gnl = get_next_line(fd, &line)) == 1)
	{
		if (ft_strncmp(line, "pattern {", 9) == 0)
			add_pattern(scene, fd);
		free(line);
	}
	if (gnl < 0)
		error(0);
	free(line);
}
