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
void        set_texture(t_scene *scene, t_event *event)
{
	t_img	*texture;

	if (!(texture = ft_memalloc(sizeof(t_img))))
		error(2);
    texture = new_xpm_image(event, "textures/bananas.xpm", 649, 275);
	scene->texture = texture; //don't think this'll segfault, but jic when it
	//all loads set t_img * to t_img
	if (scene->texture)
		printf("I swear I exist.\n");
	else
		printf("I never got initialized.\n");
	mlx_put_image_to_window(event->mlx, event->win, texture->img_ptr,
		0, 0);// in case I need to check that the image really is loading
}

void		get_triangle_texture(t_object *obj)
{
	(void)obj;
	//this is where you would ideally do the u and v calculations
}

t_material	texturize_it(t_object o, t_scene* scene)
{
	if (o.type == 5)
	{
		get_triangle_texture(&o);
	}
	// if (o.u > 0 && o.v > 0)
	// {
	// 	if (o.u + o.v > 1)
	// 		printf("o.u and o.v: %f, %f %f\n", o.u, o.v, o.u + o.v); //is this looking for o.u and o.v for everything tho
	// }
	// if (o.u + o.v < 1 && o.u + o.v > 0)
		get_tex_color(o.m.color, scene->texture, o.u, o.v);
	return (o.m); //idk what m and m2 are
}
