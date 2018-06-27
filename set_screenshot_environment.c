/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_screenshot_environment.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadamant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 11:12:11 by sadamant          #+#    #+#             */
/*   Updated: 2018/06/27 11:38:56 by sadamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
 * May have to add in the menu keypresses as well.
 */ 

int		key_pressed_screenshot(int key, t_event *event)
{
	if (key == KEY_S)
		save_image_file(event);
	else if (key == KEY_W)
		read_image_file(event);
	return (1);
}

void	init_screenshot_loop(t_event *event)
{
	mlx_key_hook(event->win, &key_pressed_screenshot, event);
	mlx_loop(event->mlx);
}
