/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 14:12:24 by mpauw             #+#    #+#             */
/*   Updated: 2018/06/20 10:45:49 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	change_grain(t_event *event, int sharper)
{
	int	yes;

	yes = 1;
	if (sharper && (event->scene).anti_a * 2 > (event->scene).max_anti_a)
		yes = 0;
	if (yes && sharper && (event->scene).grain >= 2 && (event->scene).anti_a == 1)
		(event->scene).grain /= 2;	
	else if (yes && sharper && (event->scene).anti_a * 2 <= (event->scene).max_anti_a)
		(event->scene).anti_a *= 2;
	else if (yes && !sharper && (event->scene).grain == 1 && (event->scene).anti_a >= 2)
		(event->scene).anti_a /= 2;
	else if (yes && !sharper)
		(event->scene).grain *= 2;
	if (yes)
		(event->scene).step_size *= sharper ? .5 : 2;
	create_threads(event, set_t_values);
	init_light_values((void *)event);
	turn_on_lights(event);
	// mlx_put_image_to_window(event->mlx, event->win,
	// 	(event->img).img_ptr, 0, 0);
}

int			key_pressed(int key, t_event *event)
{
	if (key == ESC)
		exit(0);
	if (KEY_UP_TO_ZERO(key) || key == KEY_0)
		event->id_select = (key == KEY_0) ? KEY_0 : KEY_NUM_VALUE(key);
	if (key == COMMA || key == DOT)
		change_grain(event, (key == COMMA));
	else if (key == KEY_C || key == KEY_O || key == KEY_L || key == KEY_G || key == KEY_M)
		event->t_select = key;
	else if (key == KEY_Q && event->t_select == KEY_L)
		turn_on_lights(event);
//	else if (event->t_select == KEY_L && (key == MINUS || key == PLUS))
//		change_light(event, (key == PLUS));
	else if (key == KEY_Q && event->t_select == KEY_C)
		change_camera(event);
	else if (event->t_select == KEY_M)
	{
		mlx_hook(event->win, KEY_PRESS, KEY_PRESS_MASK,
			&key_hold, event);
		mlx_hook(event->win, BUTTON_RELEASE, BUTTON_RELEASE_MASK,
			&key_release, event);
	}
//	else if (event->t_select == KEY_O)
//		control_object(event, 0, key, ft_init_3v(0.0, 0.0, 0.0));
	return (1);
}

int			move(t_event *event)
{
	t_scene	*scene;

	scene = &(event->scene);
	event->scene.cam->origin.v[0] -= event->key.w;
	event->scene.cam->origin.v[0] += event->key.s;
	event->scene.cam->origin.v[1] -= event->key.a;
	event->scene.cam->origin.v[1] += event->key.d;
	if (event->t_select == KEY_M)
	{
		scene->set = 1;
		set_fixed_values(scene);
		create_threads(event, set_t_values);
		init_light_values((void *)event);
		turn_on_lights(event);
		event->redraw = 1;
	}
	return (1);
}

int			key_hold(int key, t_event *event)
{
	if (key == ESC)
		exit(0);
	if (KEY_UP_TO_ZERO(key) || key == KEY_0)
		event->id_select = (key == KEY_0) ? KEY_0 : KEY_NUM_VALUE(key);
	else if (key == KEY_C || key == KEY_O || key == KEY_L || key == KEY_G || key == KEY_M)
		event->t_select = key;
	else if ((key == COMMA || key == DOT) && event->t_select == KEY_G)
		change_grain(event, (key == COMMA));
	else if (key == KEY_Q && event->t_select == KEY_L)
		turn_on_lights(event);
//	else if (event->t_select == KEY_L && (key == MINUS || key == PLUS))
//		change_light(event, (key == PLUS));
	else if (key == KEY_Q && event->t_select == KEY_C)
		change_camera(event);
	else if ((key == KEY_W || key == KEY_A || key == KEY_S
		|| key == KEY_D) && event->t_select == KEY_M)
	{
		(key == KEY_W) ? event->key.w = 10.0 : 0.0;
		(key == KEY_A) ? event->key.a = 10.0 : 0.0;
		(key == KEY_S) ? event->key.s = 10.0 : 0.0;
		(key == KEY_D) ? event->key.d = 10.0 : 0.0;
	}
	return (1);
}

int				key_release(int key, t_event *event)
{
	(key == KEY_W) ? event->key.w = 0.0 : 0.0;
	(key == KEY_A) ? event->key.a = 0.0 : 0.0;
	(key == KEY_S) ? event->key.s = 0.0 : 0.0;
	(key == KEY_D) ? event->key.d = 0.0 : 0.0;
	return (1);
}

