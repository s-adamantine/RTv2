/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_intensity.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 15:40:06 by mpauw             #+#    #+#             */
/*   Updated: 2018/05/09 13:55:04 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static double	get_s(t_p_info *pi, t_3v dir, t_cam cam)
{
	double		s;
	t_3v		tmp_dir;
	t_3v		dir_v;
	t_3v		point;
	t_3v		n;

	point = pi->point;
	n = pi->normal;
	s = 0;
	dir_v = get_reflection_vector(n, dir);
	tmp_dir = ft_3v_subtract(cam.origin, point);
	tmp_dir = normalize(tmp_dir);
	s = ft_3v_dot_product(dir_v, tmp_dir);
	return (s);
}

static double	get_d(t_3v dir, t_3v n, t_object *obj)
{
	double	d;
	double	size;
	double	angle;

	size = ft_get_3v_size(n);
	if (size == 0 && obj->type != 3)
		error(5);
	angle = -ft_3v_dot_product(n, dir);
	if (angle < 0 && obj->type > 0)
		obj->from_inside = 1;
	else
		obj->from_inside = 0;
	angle = fabs(angle);
	d = ((obj->m).diffuse / M_PI) * angle;
	return (d);
}

t_intensity		get_intensity(t_p_info *pi, t_3v dir, t_cam cam, int src_id)
{
	t_intensity	i;
	t_object	*obj;
	double		angle;
	double		distance;

	obj = pi->vis_obj;
	i.diff = 0;
	i.spec = 0;
	if (ft_get_3v_size(pi->normal) == 0)
		return (i);
	distance = (sqrt(ft_3v_dot_product(dir, dir)));
	i.attrition_diff = 1 / ((distance / 500) * (distance / 500));
	i.attrition_spec = 1 / ((distance / 100) * (distance / 100));
	dir = normalize(dir);
	i.diff = (get_d(dir, pi->normal, obj)) * i.attrition_diff;
	angle = get_s(pi, dir, cam);
	if (angle < 0)
		angle = 0;
	i.spec = ((obj->m).specular * pow(angle, (obj->m).shininess)) * i.attrition_spec;
	(void)src_id;
	return (i);
}
