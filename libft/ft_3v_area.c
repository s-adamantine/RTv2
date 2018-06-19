/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_3v_area.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadamant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 17:04:56 by sadamant          #+#    #+#             */
/*   Updated: 2018/06/18 17:05:03 by sadamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double  ft_3v_area(t_3v vertex_0, t_3v vertex_1, t_3v vertex_2)
{
    return (ft_get_3v_size(ft_cross_product((ft_3v_subtract(vertex_1, vertex_0)),
        ft_3v_subtract(vertex_2, vertex_0))));
}
