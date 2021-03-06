/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 14:12:24 by mpauw             #+#    #+#             */
/*   Updated: 2018/06/27 11:36:56 by mpauw            ###   ########.fr       */
/*   Updated: 2018/06/26 11:49:16 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	change_grain(t_event *event, int sharper)
{
	int	yes;

	yes = 1;
	if ((sharper && (event->scene).grain == 1 && (event->scene).anti_a * 2 >
				(event->scene).max_anti_a) ||
			(!sharper && (event->scene).grain >= 32))
		yes = 0;
	if (yes && sharper && (event->scene).grain >= 2 &&
			(event->scene).anti_a == 1)
		(event->scene).grain /= 2;
	else if (yes && sharper && (event->scene).anti_a *
			2 <= (event->scene).max_anti_a)
		(event->scene).anti_a *= 2;
	else if (yes && !sharper && (event->scene).grain == 1
			&& (event->scene).anti_a >= 2)
		(event->scene).anti_a /= 2;
	else if (yes && !sharper)
		(event->scene).grain *= 2;
	if (yes)
		(event->scene).step_size *= sharper ? .5 : 2;
	create_threads(event, set_t_values);
	init_light_values((void *)event);
	turn_on_lights(event);
	if ((event->scene).anti_a == 0 || (event->scene).grain == 0)
		s_error("Anti aliasing or grain has a value of 0.\n");
	mlx_put_image_to_window(event->mlx, event->win,
		(event->img).img_ptr, 0, 0);
}

static void	key_pressed_2(int key, t_event *event)
{
	if (event->t_select == KEY_G && (key == COMMA || key == DOT))
		change_grain(event, (key == COMMA));
	else if (key == KEY_C || key == KEY_O || key == KEY_L || key == KEY_G)
	{
		event->t_select = key;
		event->sub_menu = 0;
		change_menu(event);
	}
	else if (key == KEY_Q && event->t_select == KEY_L)
	{
		turn_on_lights(event);
		event->sub_menu = 0;
		change_menu(event);
	}
	else if (key == SQ_BR_L || key == SQ_BR_R)
	{
		event->sub_menu += (key == SQ_BR_L && event->sub_menu > 0) ? -1 : 1;
		change_menu(event);
	}
	else if (event->t_select == KEY_L && (key == MINUS || key == PLUS))
	{
		change_light(event, (key == PLUS));
		event->sub_menu = 0;
		change_menu(event);
	}
	else if (key == KEY_Q && event->t_select == KEY_C)
	{
		change_camera(event);
		event->sub_menu = 0;
		change_menu(event);
	}
	else
		return ;
}

int			key_pressed(int key, t_event *event)
{
	if (key == ESC)
		exit(0);
	if (key == KEY_I)
	{
		event->instructions = (event->instructions) ? 0 : 1;
		change_menu(event);
	}
	if (KEY_UP_TO_ZERO(key) || key == KEY_0)
	{
		event->id_select = (key == KEY_0) ? KEY_0 : KEY_NUM_VALUE(key);
		change_menu(event);
	}
	event->execute = 0;
	if (key == ESC)
		exit(0);
	if (KEY_UP_TO_ZERO(key) || key == KEY_0)
		event->id_select = (key == KEY_0) ? KEY_0 : KEY_NUM_VALUE(key);
	if (key == KEY_Q)
		event->execute = 1;
	key_pressed_2(key, event);
	return (1);
}

int			key_hold(int key, t_event *event)
{
	if (key == KEY_W || key == KEY_S || key == KEY_A || key == KEY_D)
	{
		mlx_put_image_to_window(event->mlx, event->win,
		(event->img).img_ptr, 0, 0);
	}
	return (1);
}
