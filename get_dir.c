/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 13:32:50 by mpauw             #+#    #+#             */
/*   Updated: 2018/03/01 17:33:38 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_3v	get_rel_origin(t_3v origin, t_object *obj)
{
	int		i;
	t_3v	rel_origin;

	i = 0;
	rel_origin = origin;
	while (i < 3)
	{
		rel_origin.v[i] = rel_origin.v[i] - (obj->origin).v[i];
		i++;
	}
	return (rel_origin);
}

void	change_dir(t_3v *dir, t_3v rotation)
{
	int		i;

	i = 2;
	while (i >= 0)
	{
		ft_rotate_3v(dir, i, -(rotation.v)[i], 0);
		i--;
	}
}

t_3v	get_dir(t_3v dir, t_3v rotation)
{
	int		i;
	t_3v	new_dir;

	(new_dir.v)[0] = (dir.v)[0];
	(new_dir.v)[1] = (dir.v)[1];
	(new_dir.v)[2] = (dir.v)[2];
	i = 2;
	while (i >= 0)
	{
		ft_rotate_3v(&new_dir, i, -(rotation.v)[i], 0);
		i--;
	}
	return (new_dir);
}

t_3v	get_rev_dir(t_3v dir, t_3v rotation)
{
	int		i;
	t_3v	new_dir;

	(new_dir.v)[0] = (dir.v)[0];
	(new_dir.v)[1] = (dir.v)[1];
	(new_dir.v)[2] = (dir.v)[2];
	i = 0;
	while (i < 3)
	{
		ft_rotate_3v(&new_dir, i, rotation.v[i], 0);
		i++;
	}
	return (new_dir);
}

t_3v		get_r_source(t_object *obj, t_cam *cam)
{
	t_3v	refl_o;

	if (!cam)
		return ((obj->rel_cam).origin);
	refl_o = get_rel_origin(cam->origin, obj);
	change_dir(&refl_o, obj->rotation);
	return (refl_o);
}
