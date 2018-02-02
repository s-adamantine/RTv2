/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 13:32:50 by mpauw             #+#    #+#             */
/*   Updated: 2018/02/02 12:10:05 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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
