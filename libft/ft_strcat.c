/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 15:14:23 by mpauw             #+#    #+#             */
/*   Updated: 2018/04/09 18:55:12 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	char	*to_return;
	int		i;

	if (!(to_return = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) *
					sizeof(char))))
		return (NULL);
	i = 0;
	while (*(s1 + i))
	{
		*(to_return + i) = *(s1 + i);
		i++;
	}
	while (*s2)
	{
		*(to_return + i) = *(s2++);
		i++;
	}
	*(to_return + i) = 0;
	return (to_return);
}
