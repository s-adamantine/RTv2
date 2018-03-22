/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 09:52:49 by mpauw             #+#    #+#             */
/*   Updated: 2018/03/22 16:12:44 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdio.h>

double	ft_atod(const char *s)
{
	int		before_dot;
	int		after_dot;
	int		i;
	double	to_return;

	if (*s == '.')
		before_dot = 0;
	else
		before_dot = ft_atoi(s);
	while (!ft_isdigit((int)(*s)))
		s++;
	while (ft_isdigit((int)(*s)))
		s++;
	if (*s != '.')
		return ((double)before_dot);
	i = 0;
	s++;
	while (ft_isdigit((int)(*(s + i))))
		i++;
	after_dot = ft_atoi(s);
	to_return = (double)before_dot + ((double)after_dot /
			(double)ft_power(10, i));
	return (to_return);
}
