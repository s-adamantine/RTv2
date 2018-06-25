/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_it.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadamant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 13:04:45 by sadamant          #+#    #+#             */
/*   Updated: 2018/06/25 11:38:24 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_material	rgb_filter_it(t_object o, int id)
{
	double	r_in;
	double	g_in;
	double	b_in;

	r_in = o.m.color.v[2];
	g_in = o.m.color.v[1];
	b_in = o.m.color.v[0];
	o.m.color.v[0] = 0.0;
	o.m.color.v[1] = 0.0;
	o.m.color.v[2] = 0.0;
	if (id == 1)
		o.m.color.v[2] = r_in;
	else if (id == 2)
		o.m.color.v[1] = g_in;
	else if (id == 3)
		o.m.color.v[0] = b_in;
	return (o.m);
}

static t_material	sepia_it(t_object o)
{
	double	r_in;
	double	g_in;
	double	b_in;

	r_in = o.m.color.v[2];
	g_in = o.m.color.v[1];
	b_in = o.m.color.v[0];
	o.m.color.v[2] = ((r_in * 0.393) + (g_in * 0.769) + (b_in * 0.189)) / 3;
	o.m.color.v[1] = ((r_in * 0.349) + (g_in * 0.686) + (b_in * 0.168)) / 3;
	o.m.color.v[0] = ((r_in * 0.272) + (g_in * 0.534) + (b_in * 0.131)) / 3;
	return (o.m);
}

static t_material	grayscale_it(t_object o)
{
	double	grey;

	grey = ((o.m.color.v[2] * 0.299) + (o.m.color.v[1] * 0.587) +
		(o.m.color.v[0] * 0.114)) / 3;
	o.m.color.v[2] = grey;
	o.m.color.v[1] = grey;
	o.m.color.v[0] = grey;
	return (o.m);
}

t_material			filter_it(t_object o, int id)
{
	if (id == 1 || id == 2 || id == 3)
		return (rgb_filter_it(o, id));
	else if (id == 4)
		return (sepia_it(o));
	else if (id == 5)
		return (grayscale_it(o));
	return (o.m);
}
