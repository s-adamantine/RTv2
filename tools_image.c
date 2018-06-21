/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_image.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadamant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 16:24:06 by sadamant          #+#    #+#             */
/*   Updated: 2018/06/21 16:24:12 by sadamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

//here just in case

/*
 ** converts an int rgb into his color vector.
*/

void    ft_rgb(t_3v c, int color)
{
	c.v[0] = color % 256;
	color /= 256;
	c.v[1] = color % 256;
	color /= 256;
	c.v[2] = color;
}

void	clear_image(t_img *img)
{
	ft_bzero(img->bitmap, img->size_line * img->height);
}

void	insert_bitmap(t_img *img, int x, int y, unsigned int color)
{
	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	img->bitmap[(y * img->width + x)] = color;
}

void	get_tex_color(t_3v c, t_img *img, int x, int y)
{
    x *= img->width;
    x *= img->height;
	return (ft_rgb(c, img->bitmap[(y * img->width + x)]));
}
