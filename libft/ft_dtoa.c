/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 10:01:33 by mpauw             #+#    #+#             */
/*   Updated: 2018/04/10 15:58:35 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_dtoa(double d, int precision)
{
	char	*s;
	char	*t;
	int		comma;
	int		len;

	t = ft_itoa((int)d);
	if (precision == 0)
		return (t);
	len = ft_strlen(t);
	if (!(s = (char *)malloc(sizeof(char) * (len + precision + 2))))
		return (NULL);
	s = ft_strcpy(s, t);
	ft_strcat(s, ".");
	d = d - (int)d;
	comma = d * ft_power(10, precision);
	free(t);
	t = ft_itoa(comma);
	ft_strcat(s, t);
	if (comma == 0 && precision > 1)
		ft_memset((char *)(s + len + ft_strlen(t) + 1), '0',
				len + precision + 1 - ft_strlen(s));
	free(t);
	*(s + len + precision + 1) = 0;
	return (s);
}
