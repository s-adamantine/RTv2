/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 14:12:15 by mpauw             #+#    #+#             */
/*   Updated: 2018/06/25 09:45:42 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** For every light, determine the influence it has on every pixel by calling
** set_light_per_pixel.
*/

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
