/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_vector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 14:15:23 by mpauw             #+#    #+#             */
/*   Updated: 2018/06/12 17:47:08 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_3v		get_reflection_vector(t_3v n, t_3v dir)
{
	double	tmp;

	ft_3v_scalar_p(&dir, -1);
	tmp = 2 * ft_3v_dot_product(n, dir);
	ft_3v_scalar_p(&n, tmp);
	return (ft_3v_subtract(n, dir));
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

static t_3v	get_normal_2(t_object *obj, t_3v point)
{
	t_3v	c_mid;
	t_3v	tmp_v;
	t_3v	norm;
	double	a;
	double	b;

	c_mid = ft_3v_add(obj->origin,
			ft_3v_scalar(obj->dir, obj->param_1 / 2.0));
	tmp_v = ft_3v_subtract(point, c_mid);
	a = (obj->param_1 / 2 + obj->radius) / 2;
	b = sqrt(obj->param_1 * obj->param_1 / 4 + obj->radius * obj->radius) / 2;
	if (b < 0.0001)
		error(5);
	norm = ft_3v_subtract(tmp_v, ft_3v_scalar(obj->dir, (1 -
						a * a / (b * b)) * ft_3v_dot_product(tmp_v, obj->dir)));
	norm = normalize(norm);
	printf("norm: %f %f %f\n", norm.v[0], norm.v[1], norm.v[2]);
	printf("point - mid: %f %f %f\n\n", tmp_v.v[0], tmp_v.v[1], tmp_v.v[2]);
	return (norm);
}

t_3v		get_normal(t_object *obj, t_3v point)
{
	t_3v	norm_t;
	double	size;

	if (obj->type == 0)
		return (rotate_v(ft_get_3v_unit(2), obj->rotation));
	else if (obj->type == 4)
		return (get_normal_2(obj, point));
	else
		norm_t = ft_3v_subtract(point, obj->origin);
	norm_t = rotate_v_inv(norm_t, obj->rotation);
	if (obj->type == 2)
		(norm_t.v)[2] = 0;
	if (obj->type == 3)
		(norm_t.v)[2] = -((norm_t.v)[0] * (norm_t.v)[0]
			+ (norm_t.v)[1] * (norm_t.v)[1]) / (norm_t.v)[2];
	size = ft_get_3v_size(norm_t);
	if (size == 0 && obj->type != 3)
		error(5);
	if (size != 0)
		ft_3v_scalar_p(&norm_t, 1 / size);
	norm_t = rotate_v(norm_t, obj->rotation);
	return (norm_t);
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
