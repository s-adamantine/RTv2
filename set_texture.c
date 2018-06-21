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
	xpm->img_arr = mlx_get_data_addr(xpm->img_ptr, &(xpm->bpp),
		&(xpm->size_line), &(xpm->endian));
	xpm->bitmap = (int *)mlx_get_data_addr(xpm->img_ptr, &(xpm->bpp),
		&(xpm->size_line), &(xpm->endian)); //he uses a char * array, protect against null.
	return (xpm);
}

/*
** load texture from file to array.
*/
void        set_texture(t_event *event)
{
	t_img	*texture;

	if (!(texture = ft_memalloc(sizeof(t_img))))
		error(2);
    texture = new_xpm_image(event, "textures/bananas.xpm", 649, 275);
	event->texture = texture; //don't think this'll segfault, but jic when it
	//all loads set t_img * to t_img
	// mlx_put_image_to_window(event->mlx, event->win, event->texture->img_ptr,
		// 0, 0); in case I need to check that the image really is loading
}

void		texturize_it()
{

}
