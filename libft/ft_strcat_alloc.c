/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat_alloc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 10:12:53 by mpauw             #+#    #+#             */
/*   Updated: 2018/04/10 11:04:46 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat_alloc(char *s1, const char *s2)
{
	char	*to_return;
	int		i;
	int		j;

	if (!(to_return = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) *
					sizeof(char))))
		return (NULL);
	i = 0;
	while (*(s1 + i))
	{
		*(to_return + i) = *(s1 + i);
		i++;
	}
	j = 0;
	while (*(s2 + j))
	{
		*(to_return + i) = *(s2 + j);
		i++;
		j++;
	}
	*(to_return + i) = 0;
	return (to_return);
}
