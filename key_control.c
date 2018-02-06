/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 08:24:38 by mpauw             #+#    #+#             */
/*   Updated: 2018/02/06 13:10:23 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		key_pressed(int key, t_event *event)
{
	printf("%d\n", key);
	if (key == ESC)
		exit(0);
	else if (key == SPACE)
		anti_aliasing(event);
	return (1);
}
