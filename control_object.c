/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_object.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 13:35:39 by mpauw             #+#    #+#             */
/*   Updated: 2018/06/14 13:52:55 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	control_object(t_event *event, int mouse, int key, t_3v coor)
{
	static t_object	obj;
	static int		init = 0;

	if (!init)
		obj = init_def_object(&obj, (event->scene).amount_obj);
	init = 1;
	if (mouse)
		handle_mouse(coor);
	if (KEY_UP_TO_FOUR(key))
		obj.type = KEY_NUM_VALUE(key) - 1;
	
}
