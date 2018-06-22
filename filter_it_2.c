/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_it_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadamant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 16:24:12 by sadamant          #+#    #+#             */
/*   Updated: 2018/06/22 16:24:17 by sadamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_3v    color_filter_it(t_3v color, int id)
{
    if (id == 6)
    {
        // printf("color before: %f %f %f\n", color.v[0], color.v[1], color.v[2]);
        color.v[0] = (double)((int)(color.v[0] * 100)) / 100;
        color.v[1] = (double)((int)(color.v[1] * 100)) / 100;
        color.v[2] = (double)((int)(color.v[2] * 100)) / 100;
        // printf("color after: %f %f %f\n", color.v[0], color.v[1], color.v[2]);
    }
    return (color);
}
