/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_light_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 14:09:05 by mpauw             #+#    #+#             */
/*   Updated: 2018/06/21 18:09:11 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
 * Determines whether a source should be turned off or on.
 */

static int	turn_off_or_on(t_scene *scene, int id)
{
	t_source	*src;
	t_list		*s_lst;

	s_lst = scene->lights;
	if (id == KEY_0)
		scene->all_on = (scene->all_on) ? 0 : 1;
	while (s_lst && s_lst->content)
	{
		src = (t_source *)s_lst->content;
		if (src->type)
		{
			if (id == KEY_0)
				src->on = (scene->all_on) ? 1 : 0;
			else if (id == src->id)
			{
				src->on = (src->on) ? 0 : 1;
				return (1);
			}
		}
		s_lst = s_lst->next;
	}
	if (id == KEY_0)
		return (1);
	return (0);
}

static void	add_color(t_pixel *p, int id, t_event *event, t_3v *t)
{
	if (p->pi_arr[0] && (p->pi_arr[0])->vis_obj)
	{
		if (id == 0)
			p->color = p->c_per_src[0];
		else
		{
			if ((event->src)->max_intensity > 1.0)
				(p->c_per_src)[id] = ft_3v_scalar((p->c_per_src)[id],
						1.0 / (event->src)->max_intensity);
			p->color = ft_3v_add((p->c_per_src)[id], p->color);
		}
	}
	*t = ft_3v_add(p->color, *t);
}

/*
 * Change the color of a pixel by adding the color value of the light. Change
 * in image by calling fill_square (grainy effect).
 */

static void	change_color(t_event *event, int id, int vert, int hor)
{
	t_pixel	*p;
	t_3v	t;
	int		i;
	int		j;
	int		index;

	i = 0;
	t = ft_init_3v(0.0, 0.0, 0.0);
	index = (event->scene).max_anti_a * (hor + vert * (event->scene).max_anti_a
			* (event->scene).width);
	while (i < event->scene.max_anti_a)
	{
		j = index;
		while (j < index + event->scene.max_anti_a)
		{
			p = &((((event->scene).cam)->p_array)
				[j + (event->scene).width * i * (event->scene).max_anti_a]);
			add_color(p, id, event, &t);
			j += event->scene.step_size;
		}
		i += event->scene.step_size;
	}
	t = ft_3v_scalar(t, 1.0 / ((event->scene).anti_a * (event->scene).anti_a));
	fill_square(&(event->img), hor + (event->scene).width * vert,
			(event->scene).step_size / (event->scene).max_anti_a, get_color(t));
}

static void	*switch_one(void *event)
{
	int		i;
	int		j;
	int		grain_step;
	t_scene	scene;
	t_event	*e;

	e = (t_event*)event;
	scene = e->scene;
	i = ((scene.height / THREADS) * scene.thread_id);
	grain_step = (scene.step_size > scene.max_anti_a) ? scene.step_size /
		scene.max_anti_a : 1;
	while (i < (scene.height / THREADS) * (scene.thread_id + 1))
	{
		j = 0;
		while (j < scene.width)
		{
			change_color(event, scene.source_id, i, j);
			j += grain_step;
		}
		i += grain_step;
	}
	return (NULL);
}

/*
 * Turn on light or multiple lights.
 */

void		turn_on_lights(t_event *event)
{
	t_list		*s_lst;

	event->redraw = 1;
	(event->scene).source_id = 0;
	create_threads(event, switch_one);
	if (event->t_select == KEY_L)
	{
		if (!(turn_off_or_on(&(event->scene), event->id_select)))
			return ;
		if (event->id_select == KEY_0 && !((event->scene).all_on))
			return ;
	}
	s_lst = (event->scene).lights;
	while (s_lst && s_lst->content)
	{
		event->src = (t_source *)s_lst->content;
		if (event->src->type && event->src->on)
		{
			(event->scene).source_id = event->src->id;
			create_threads(event, switch_one);
		}
		s_lst = s_lst->next;
	}
}
