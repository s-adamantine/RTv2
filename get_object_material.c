/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_object_material.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 14:27:04 by mpauw             #+#    #+#             */
/*   Updated: 2018/05/09 14:27:06 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_material		get_object_material(t_object o, t_3v p)
{
	if ((o.pattern).type == 1)
		return (polka_dot_it(o, p));
	return (o.m);
}
