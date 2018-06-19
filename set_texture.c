/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadamant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 14:34:36 by sadamant          #+#    #+#             */
/*   Updated: 2018/06/19 14:34:46 by sadamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_img	  *new_xpm_image(t_event *event, char *name, int w, int h)
{
	t_img	*xpm;

	xpm = (t_img *)malloc(sizeof(t_img));
	xpm->width = w;
	xpm->height = h;
	xpm->img_ptr = mlx_xpm_file_to_image(event->mlx, name, &w, &h);
	xpm->img_arr = (int *)mlx_get_data_addr(xpm->id, &(xpm->bpp), &(xpm->sline),
		&(xpm->endian)); //he uses a char * array.
	return (xpm);
}

/*
** load texture from file to array.
*/
void        set_texture(t_scene *scene)
{
    if (scene)
        texture = new_xpm_image(event, "textures/bananas.xpm", 649, 275);
}
