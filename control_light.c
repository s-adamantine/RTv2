/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 14:12:15 by mpauw             #+#    #+#             */
/*   Updated: 2018/05/09 14:12:17 by mpauw            ###   ########.fr       */
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

static void	add_color(t_pixel *p, int id)
{
	if (p->pi_arr[0] && (p->pi_arr[0])->vis_obj)
	{
		if (id == 0)
			p->color = p->c_per_src[0];
		else
			p->color = ft_3v_add((p->c_per_src)[id], p->color);
	}
}

/*
 * Change the color of a pixel by adding the color value of the light. Change
 * in image by calling fill_square (grainy effect).
 */

static void	change_color(t_event *event, int id, int index, int factor)
{
	t_pixel	*p;
	t_3v	temp;
	int		i;
	int		j;
	int		loop_to;

	i = 0;
	temp = ft_init_3v(0.0, 0.0, 0.0);
	loop_to = (event->scene).anti_a > (event->scene).grain ?
	(event->scene).anti_a : 1;
	while (i < loop_to)
	{
		j = index;
		while (j < index + loop_to)
		{
			p = &((((event->scene).cam)->p_array)
			[j + (event->scene).width * factor * i]);
			add_color(p, id);
			j++;
			temp = ft_3v_add(p->color, temp);
		}
		i++;
	}
	(temp.v)[0] /= (loop_to * loop_to);
	(temp.v)[1] /= (loop_to * loop_to);
	(temp.v)[2] /= (loop_to * loop_to);
	j = index % ((event->scene).width * factor);
	i = (index - j) / ((event->scene).width * factor);
	fill_square(&(event->img), j / factor + (event->scene).width
	* i / factor, ((event->scene).anti_a > (event->scene).grain)
	? 1 : (event->scene).grain, get_color(temp));
}

static void	*switch_one(void *event)
{
	int		i;
	int		j;
	int		factor;
	t_scene	scene;
	t_event	*e;

	e = (t_event*)event;
	scene = e->scene;
	factor = scene.anti_a > scene.grain ?
	scene.anti_a : 1;
	i = ((scene.height * factor / THREADS) * scene.thread_id);
	while (i < (scene.height * factor / THREADS)  * (scene.thread_id + 1))
	{
		j = 0;
		while (j < scene.width * factor)
		{
			change_color(event, scene.source_id,
			j + scene.width * factor * i, factor);
			j += scene.step_size;
		}
		i += scene.step_size;
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
	// create_threads(event, switch_one);
	switch_one((void*)event);
	if ((event->scene).grain == 1 && event->t_select == KEY_L)
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
			// create_threads(event, switch_one);
			switch_one((void*)event);
		}
		s_lst = s_lst->next;
	}
}

/*
 * For every light, determine the influence it has on every pixel by calling
 * set_light_per_pixel.
 */

void		*init_light_values(void *arg)
{
	t_event			*event;
	t_list			*s_lst;

	event = (t_event *)arg;
	s_lst = (event->scene).lights;
	while (s_lst && s_lst->content)
	{
		event->src = (t_source *)s_lst->content;
		if (event->src->type)
			// create_threads(event, set_light_per_pixel);
			set_light_per_pixel((void*)event);
		s_lst = s_lst->next;
	}
	return (NULL);
}

void	create_threads(t_event *event, void *(*f)(void*))
{
	int			i;
	pthread_t	thread[THREADS];
	t_event		t[THREADS];

	i = 0;
	while (i < THREADS)
	{
		ft_memcpy((void*)&t[i], (void*)event, sizeof(t_event));
		t[i].scene.thread_id = i;
		pthread_create(&thread[i], NULL, f, &t[i]);
		i++;
	}
	i = 0;
	while (i < THREADS)
	{
		pthread_join(thread[i], NULL);
		i++;
	}
}