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

#include "rtv1.c"

//I think a, b and c can be input into t_fived_v
double  get_t_triangle(t_fixed_v f, t_3v origin, t_3v dir)
{
    t_3v    ab;
    t_3v    ac;
    t_3v    n;

    ab = ft_3v_subtract(b, a);
    ac = ft_3v_subtract(c, a);
    n = ft_cross_product(ab, ac);
    d = ft_3v_dot_product(n, a);
    top = ft_3v_add(ft_3v_dot_product(n, o), d);
    if ((bottom = ft_3v_dot_product(n, dir)) < 0.01)
        return (-1); //no intersection
    return (-top/bottom); //if t is negative then it's behind the camera
}
