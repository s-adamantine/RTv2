/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clamp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroguszk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 13:33:52 by jroguszk          #+#    #+#             */
/*   Updated: 2018/06/25 13:33:54 by jroguszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_clamp(double min, double max, double x)
{
	if (x - min < 0.001)
		return (min);
	else if (x - max > 0.001)
		return (max);
	else
		return (x);
}
