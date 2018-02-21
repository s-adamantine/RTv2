/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_source.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 09:19:59 by mpauw             #+#    #+#             */
/*   Updated: 2018/02/21 15:11:05 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_source	*get_source(int id, t_list *lst)
{
	t_list		*tmp;
	t_source	*src;

	tmp = lst;
	while (tmp && tmp->content)
	{
		src = (t_source *)(tmp->content);
		if (src->id == id)
			return (src);
		tmp = tmp->next;
	}
	error(1);
	return (src);
}

t_3v		get_source_origin(t_object *obj, int id)
{
	t_list		*tmp;
	t_source	*src;

	if (id == -1)
		return ((obj->rel_cam).origin);
	tmp = obj->rel_lights;;
	while (tmp && tmp->content)
	{
		src = (t_source *)(tmp->content);
		if (src->id == id)
			return (src->origin);
		tmp = tmp->next;
	}
	error(1);
	return (src->origin);
}
