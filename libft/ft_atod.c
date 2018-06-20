/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 09:52:49 by mpauw             #+#    #+#             */
/*   Updated: 2018/06/19 16:34:00 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atod(const char *s)
{
	int		before_dot;
	int		after_dot;
	int		i;
	int		neg;
	double	to_return;

	neg = 1;
	if (*s == '-')
	{
		neg = -1;
		s++;
	}
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
	return (neg * to_return);
}
