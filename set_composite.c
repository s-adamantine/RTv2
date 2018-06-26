/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_composite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 13:57:38 by mpauw             #+#    #+#             */
/*   Updated: 2018/06/26 11:47:31 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	set_composite(int fd, t_scene *scene, t_object *obj)
{
	char		*line;
	int			gnl;
	static int	id = 1;

	obj->group_id = id;
	id++;
	while ((gnl = get_next_line(fd, &line)) == 1)
	{
		if (ft_strncmp(line, "object {", 8) == 0)
			set_object(scene, scene->amount_obj, fd, obj);
		free(line);
	}
	if (gnl < 0)
		error(0);
	free(line);
}

void		check_for_composite(t_scene *scene, t_object *obj)
{
	int	fd;

	if (obj->type != 7 || !obj->path)
		return ;
	if ((fd = open(obj->path, O_RDONLY)) == -1)
		error(0);
	set_composite(fd, scene, obj);
}
