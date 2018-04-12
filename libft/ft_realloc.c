/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 13:24:52 by mpauw             #+#    #+#             */
/*   Updated: 2018/04/11 13:24:54 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_realloc(void **s, size_t old_size, size_t new_size)
{
	size_t			i;
	unsigned char	*m;

	m = *(unsigned char **)s;
	if (!(*(unsigned char **)s =
				(unsigned char *)malloc(sizeof(unsigned char) * new_size)))
		return ;
	i = 0;
	while (i < old_size)
	{
		(*(unsigned char **)s)[i] = m[i];
		i++;
	}
	free(m);
}
