/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_it.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadamant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 13:04:45 by sadamant          #+#    #+#             */
/*   Updated: 2018/06/26 11:49:30 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_material	rgb_filter_it(t_material m, int id)
{
	double	r_in;
	double	g_in;
	double	b_in;

	r_in = m.color.v[2];
	g_in = m.color.v[1];
	b_in = m.color.v[0];
	m.color.v[0] = 0.0;
	m.color.v[1] = 0.0;
	m.color.v[2] = 0.0;
	if (id == 1)
		m.color.v[2] = r_in;
	else if (id == 2)
		m.color.v[1] = g_in;
	else if (id == 3)
		m.color.v[0] = b_in;
	return (m);
}

static t_material	sepia_it(t_material m)
{
	double	r_in;
	double	g_in;
	double	b_in;

	r_in = m.color.v[2];
	g_in = m.color.v[1];
	b_in = m.color.v[0];
	m.color.v[2] = ((r_in * 0.393) + (g_in * 0.769) + (b_in * 0.189)) / 3;
	m.color.v[1] = ((r_in * 0.349) + (g_in * 0.686) + (b_in * 0.168)) / 3;
	m.color.v[0] = ((r_in * 0.272) + (g_in * 0.534) + (b_in * 0.131)) / 3;
	return (m);
}

static t_material	grayscale_it(t_material m)
{
	double	grey;

	grey = ((m.color.v[2] * 0.299) + (m.color.v[1] * 0.587) +
		(m.color.v[0] * 0.114)) / 3;
	m.color.v[2] = grey;
	m.color.v[1] = grey;
	m.color.v[0] = grey;
	return (m);
}

t_material			filter_it(t_material m, int id)
{
	if (id == 1 || id == 2 || id == 3)
		return (rgb_filter_it(m, id));
	else if (id == 4)
		return (sepia_it(m));
	else if (id == 5)
		return (grayscale_it(m));
	return (m);
}
