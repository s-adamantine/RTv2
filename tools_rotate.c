/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_rotate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 14:18:27 by mpauw             #+#    #+#             */
/*   Updated: 2018/06/26 11:50:39 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_3v	rotate_v_inv(t_3v dir, t_3v rotation)
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

t_3v	rotate_v(t_3v dir, t_3v rotation)
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
