/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_intensity.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 15:40:06 by mpauw             #+#    #+#             */
/*   Updated: 2018/03/22 16:53:42 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static double	get_s(t_pixel *p, int r, t_3v dir, t_cam cam)
{
	double	s;
	t_3v	tmp_dir;
	t_3v	dir_v;
	t_3v	point;
	t_3v	n;

	point = p->point[r];
	n = p->normal[r];
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
	angle = ft_3v_dot_product(n, dir);
	if (obj->type == 0)
		angle = fabs(angle);
	d = (obj->diffuse / M_PI) * angle;
	return (d);
}

t_intensity		get_intensity(t_pixel *p, int r, t_3v dir, t_cam cam)
{
	t_intensity	i;
	t_object	*obj;
	double		angle;

	obj = p->vis_obj[r];
	i.diff = 0;
	i.spec = 0;
	if (ft_get_3v_size(p->normal[r]) == 0)
		return (i);
	dir = normalize(dir);
	i.diff = get_d(dir, p->normal[r], obj);
	angle = get_s(p, r, dir, cam);
	if (angle < 0)
		angle = 0;
	i.spec = obj->specular * pow(angle, obj->shininess);
	return (i);
}
