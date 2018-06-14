/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_grain.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 14:24:11 by mpauw             #+#    #+#             */
/*   Updated: 2018/06/13 17:19:57 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
 * Fill a square in the image with one color, so we can make the program
 * quicker by using the grainy effect.
 */

int		fill_square(t_img *img, int index, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	size = (size < 1) ? 1 : size;
	while (i < size && (index % (*img).size_line_int) + i < (*img).width)
	{
		j = 0;
		while (j < size && (index / (*img).size_line_int) + j < (*img).height)
		{
			((int *)((*img).img_arr))[index + i + j *
				(*img).size_line_int] = color;
			j++;
		}
		i++;
	}
	index += i;
	if (index % ((*img).size_line_int) == 0)
		index = index + 1 + ((j - 1) * ((*img).size_line_int));
	return (index);
}
