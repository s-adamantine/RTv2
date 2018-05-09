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

/*
 * Change the color of a pixel by adding the color value of the light. Change
 * in image by calling fill_square (grainy effect).
 */

static void	change_color(t_event *event, int id, int index)
{
	t_pixel	*p;

	p = &((((event->scene).cam)->p_array)[index]);
	if ((p->pi_arr[0])->vis_obj)
	{
		if (id == 0)
			p->color = p->c_per_src[0];
		else
			p->color = ft_3v_add((p->c_per_src)[id], p->color);
	}
	fill_square(&(event->img), index, ((event->scene).cam)->grain,
			get_color(p->color));
}

static void	switch_one(t_event *event, int id)
{
	int		i;
	int		j;
	t_scene	scene;

	i = 0;
	scene = event->scene;
	while (i < scene.height)
	{
		j = 0;
		while (j < scene.width)
		{
			change_color(event, id, j + scene.width * i);
			j += (scene.cam)->grain;
		}
		i += (scene.cam)->grain;
	}
}

/*
 * Turn on light or multiple lights.
 */

void		turn_on_lights(t_event *event)
{
	t_source	*src;
	t_list		*s_lst;

	event->redraw = 1;
	switch_one(event, 0);
	if (((event->scene).cam)->grain == 1 && event->t_select == KEY_L)
	{
		if (!(turn_off_or_on(&(event->scene), event->id_select)))
			return ;
		if (event->id_select == KEY_0 && !((event->scene).all_on))
			return ;
	}
	s_lst = (event->scene).lights;
	while (s_lst && s_lst->content)
	{
		src = (t_source *)s_lst->content;
		if (src->type && src->on)
			switch_one(event, src->id);
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
	t_source		*src;

	event = (t_event *)arg;
	s_lst = (event->scene).lights;
	while (s_lst && s_lst->content)
	{
		src = (t_source *)s_lst->content;
		if (src->type)
			set_light_per_pixel(event, *src);
		s_lst = s_lst->next;
	}
	return (NULL);
}
