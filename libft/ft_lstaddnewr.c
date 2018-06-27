/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddnewr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 12:34:45 by mpauw             #+#    #+#             */
/*   Updated: 2018/06/26 17:30:46 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstaddnewr(t_list **alst, void const *content, size_t content_size)
{
	t_list	*to_add;

	if ((to_add = ft_lstnew(content, content_size)))
	{
		ft_lstaddright(alst, to_add);
		return (1);
	}
	return (0);
}
