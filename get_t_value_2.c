/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_t_value_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 11:12:11 by mpauw             #+#    #+#             */
/*   Updated: 2018/06/18 11:12:32 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double  get_t_triangle(t_fixed_v f, t_3v dir)
{
    double  bottom;

    if ((bottom = ft_3v_dot_product(f.vec, dir)) < 0.01)
        return (-1); //no intersection
    bottom = ft_3v_dot_product(f.vec, dir);
    return (f.val/bottom * -1); //if t is negative then it's behind the camera
}
