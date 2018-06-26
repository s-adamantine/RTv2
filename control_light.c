/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 14:12:15 by mpauw             #+#    #+#             */
/*   Updated: 2018/06/26 12:59:14 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** For every light, determine the influence it has on every pixel by calling
** set_light_per_pixel.
*/

static	t_source	*get_source(t_list *lst, int id)
{
	t_list		*s_lst;
	t_source	*src;

	s_lst = lst;
	while (s_lst && s_lst->content)
	{
		src = (t_source *)s_lst->content;
		if (src->type && src->id == id)
			return (src);
		s_lst = s_lst->next;
	}
	return (NULL);
}

void	*init_light_values(void *arg)
{
	t_event			*event;
	t_list			*s_lst;

	event = (t_event*)arg;
	s_lst = (event->scene).lights;
	while (s_lst && s_lst->content)
	{
		event->src = (t_source *)s_lst->content;
		if (event->src->type)
			create_threads(event, set_light_per_pixel);
		s_lst = s_lst->next;
	}
	return (NULL);
}

void	change_light(t_event *event, int brighter)
{
	t_source	*src;

	src = get_source((event->scene).lights, event->id_select);
	if (!src)
		return ;
	if (brighter)
		src->int_factor += 0.05;
	else if (src->int_factor >= 0.05)
		src->int_factor -= 0.05;
	turn_on_lights(event);
}
