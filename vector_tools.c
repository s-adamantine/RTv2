/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 18:18:41 by mpauw             #+#    #+#             */
/*   Updated: 2018/03/20 18:18:45 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_3v	get_reflection_vector(t_3v n, t_3v dir_a)
{
	double	tmp;

	tmp = 2 * ft_3v_dot_product(n, dir_a);
	ft_3v_scalar(&n, tmp);
	return (ft_3v_subtract(dir_a, n));
}

t_3v	get_normal(t_object *obj, t_3v point)
{
	t_3v	norm_d;
	t_3v	norm_t;
	double	size;

	if (obj->type == 0)
		return (ft_get_3v_unit(1));
	else
		norm_d = ft_3v_subtract(point, obj->origin);
	norm_t = get_dir(norm_d, obj->rotation);
	if (obj->type == 2)
		(norm_t.v)[2] = 0;
	if (obj->type == 3)
		(norm_t.v)[2] = -((norm_t.v)[0] * (norm_t.v)[0]
			+ (norm_t.v)[1] * (norm_t.v)[1]) / (norm_t.v)[2];
	size = ft_get_3v_size(norm_t);
	if (size == 0 && obj->type != 3)
		error(5);
	if (size != 0)
		ft_3v_scalar(&norm_t, -1 / size);
	return (norm_t);
}

