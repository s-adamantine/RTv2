/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_t_value_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 14:31:35 by mpauw             #+#    #+#             */
/*   Updated: 2018/06/11 17:07:31 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

//I think a, b and c can be input into t_fived_v
double  get_t_triangle(t_fixed_v f, t_3v dir)
{
    double  bottom;
    double  t;
    t_3v     P;
    t_3v    edge0;
    t_3v    edge1;
    t_3v    edge2;
    t_3v    vp0;
    t_3v    vp1;
    t_3v    vp2;
    t_3v    scalar;

    if ((bottom = ft_3v_dot_product(f.vec, dir)) > -0.01)
        return (-1); //no intersection
    bottom = ft_3v_dot_product(f.vec, dir);
    t = f.val/bottom * -1;
    //now we do the inside out test.
    P = ft_3v_add(f.vec2, ft_3v_scalar(dir, t)); //adding the origin w/ the raydir x t
    scalar = ft_3v_scalar(dir, t);
    edge0 = ft_3v_subtract(f.vertex1, f.vertex0);
    edge1 = ft_3v_subtract(f.vertex2, f.vertex1);
    edge2 = ft_3v_subtract(f.vertex0, f.vertex2);
    vp0 = ft_cross_product(edge0, ft_3v_subtract(P, f.vertex0));
    vp1 = ft_cross_product(edge1, ft_3v_subtract(P, f.vertex1));
    vp2 = ft_cross_product(edge2, ft_3v_subtract(P, f.vertex2));
    if (ft_3v_dot_product(f.vec, vp0) < 0 || ft_3v_dot_product(f.vec, vp1) < 0
        || ft_3v_dot_product(f.vec, vp2) < 0)
        return (-1);
    return (f.val/bottom * -1); //if t is negative then it's behind the camera
}
