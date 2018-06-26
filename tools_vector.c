/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_vector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 14:15:23 by mpauw             #+#    #+#             */
/*   Updated: 2018/06/26 11:50:45 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_3v		get_reflection_vector(t_3v n, t_3v dir)
{
	double	tmp;

	ft_3v_scalar_p(&dir, -1);
	tmp = 2 * ft_3v_dot_product(n, dir);
	ft_3v_scalar_p(&n, tmp);
	return (ft_3v_subtract(n, dir));
}

static t_3v	get_rand_v(double min, double max, t_3v v)
{
	int		i;

	i = 0;
	while (i < 3)
	{
		if (v.v[i] < 0.0001)
			v.v[i] += 0.05 * (min + (max - min) * ((double)rand() /
						(double)RAND_MAX));
		v.v[i] *= (min + (max - min) * ((double)rand() / (double)RAND_MAX));
		i++;
	}
	return (v);
}

t_3v		get_normal(t_object *obj, t_3v point)
{
	t_3v	norm_t;
	double	size;

	norm_t = rotate_v(ft_get_3v_unit(2), obj->rotation);
	if (obj->type == 0)
		return (get_rand_v((obj->m).n_var.v[0], (obj->m).n_var.v[1], norm_t));
	else
		norm_t = ft_3v_subtract(point, obj->origin);
	norm_t = rotate_v_inv(norm_t, obj->rotation);
	if (obj->type == 2)
		(norm_t.v)[2] = 0;
	if (obj->type == 3)
		(norm_t.v)[2] = -((norm_t.v)[0] * (norm_t.v)[0]
			+ (norm_t.v)[1] * (norm_t.v)[1]) / (norm_t.v)[2];
	if (obj->type == 5)
		norm_t = ft_cross_product(ft_3v_subtract(obj->origin_2, obj->origin),
				ft_3v_subtract(obj->origin_3, obj->origin));
	norm_t = get_rand_v((obj->m).n_var.v[0], (obj->m).n_var.v[1], norm_t);
	size = ft_get_3v_size(norm_t);
	if (size == 0 && obj->type != 3)
		error(5);
	if (size != 0)
		ft_3v_scalar_p(&norm_t, 1 / size);
	norm_t = rotate_v(norm_t, obj->rotation);
	return (norm_t);
}

t_3v		normalize(t_3v v)
{
	double	size;
	t_3v	tr;

	size = ft_get_3v_size(v);
	if (size < 0.00001)
		error(5);
	tr = ft_3v_scalar(v, 1 / size);
	return (tr);
}

t_3v		get_point(t_3v origin, t_3v coor, double s_value)
{
	t_3v	point;
	t_3v	dir;

	dir = coor;
	point = origin;
	ft_3v_scalar_p(&dir, s_value);
	point = ft_3v_add(point, dir);
	return (point);
}
