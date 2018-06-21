/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_t_value_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 11:12:11 by mpauw             #+#    #+#             */
/*   Updated: 2018/06/20 16:31:30 by sadamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	get_t_triangle(t_fixed_v f, t_3v dir, int alt, t_object *obj)
{
	double	bottom;
	t_3v	p;
	t_3v	vp0;
	t_3v	vp1;
	t_3v	vp2;
	double	u; //for the texture coordinates
	double	v;

	(void)alt;
	(void)obj;
	if ((bottom = ft_3v_dot_product(f.vec, dir)) > -0.01)
		return (-1);
	p = ft_3v_add(f.vec2, ft_3v_scalar(dir, f.val / bottom * -1));
	//in order to slap texture, read where they set the color
	// edge0 = ft_3v_subtract(f.vertex1, f.vertex0);
	// edge1 = ft_3v_subtract(f.vertex2, f.vertex1);
	// edge2 = ft_3v_subtract(f.vertex0, f.vertex2);
	vp0 = ft_cross_product(ft_3v_subtract(f.vertex1, f.vertex0),
		ft_3v_subtract(p, f.vertex0));
	vp1 = ft_cross_product(ft_3v_subtract(f.vertex2, f.vertex1),
		ft_3v_subtract(p, f.vertex1));
	vp2 = ft_cross_product(ft_3v_subtract(f.vertex0, f.vertex2),
		ft_3v_subtract(p, f.vertex2));
	//ft_get_3v_size is find the distance
	u = (ft_get_3v_size(vp0) / 2) / f.val_2;
	v = (ft_get_3v_size(vp2) / 2) / f.val_2;
	//at that p value, grab the respective color from the texture map.
	//going to pretend that it's purple!

	//I hate how I have to comment this out.
	// get_color(obj->m.color, event->texture, u, v);

	if (ft_3v_dot_product(f.vec, vp0) < 0 || ft_3v_dot_product(f.vec, vp1) < 0
		|| ft_3v_dot_product(f.vec, vp2) < 0)
		return (-1);
	// printf("u: %f, v: %f, u + v: %f\n", u, v, u + v);
	return (f.val / bottom * -1);
}

double  get_t_mesh(t_fixed_v f, t_3v dir, int alt)
{
    (void)f;
    (void)dir;
	(void)alt;

    return (-1);
}
