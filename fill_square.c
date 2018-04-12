/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pixel_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 15:35:31 by mpauw             #+#    #+#             */
/*   Updated: 2018/04/11 13:20:08 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			fill_square(t_img *img, int index, int size, int color)
{
	int	i;
	int	j;

	i = 0;
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
