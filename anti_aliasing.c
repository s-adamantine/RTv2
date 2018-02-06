/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti_aliasing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 11:39:50 by mpauw             #+#    #+#             */
/*   Updated: 2018/02/06 16:58:09 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
/*
static void	add_to_color(t_3v *color, int to_add)
{
	color->v[0] += to_add % 0xffff;
	color->v[1] += (to_add / 0xff) % 0xff;
	color->v[2] += to_add / 0xffff;
}
*/
static int	take_average(t_event *event, t_scene scene, int vert, int hor)
{
	int		i;
	int		j;
	int		k;
	int		index;
	t_3v	color;

	i = 0;
	index = scene.anti_a * hor + scene.anti_a * vert * scene.width;
	color.v[0] = 0;
	color.v[1] = 0;
	color.v[2] = 0;
	while (i < scene.anti_a)
	{
		j = 0;
		while (j < scene.anti_a)
		{
			k = 0;
			while (k < 3)
			{
				color.v[k] += (event->img)->img_arr[(index + j + i * scene.width) * 4 + k];
				k++;
			}
			j++;
		}
		i++;
	}
	printf("%f %f %f\n", color.v[0], color.v[1], color.v[2]);
	color.v[0] /= (scene.anti_a * scene.anti_a);
	color.v[1] /= (scene.anti_a * scene.anti_a);
	color.v[2] /= (scene.anti_a * scene.anti_a);
	printf("%f %f %f\n\n", color.v[0], color.v[1], color.v[2]);
	return (color.v[0] + 0x100 * color.v[1] + 0x10000 * color.v[2]);
}

void		anti_aliasing(t_event *event)
{
	t_scene	tmp;
	int		i;
	int		j;
	t_img	*old_img;

	tmp.width = (event->scene).width;
	tmp.height = (event->scene).height;
	tmp.grain = (event->scene).grain;
	(event->scene).width *= (event->scene).anti_a;
	(event->scene).height *= (event->scene).anti_a;
	(event->scene).grain = 1;
	old_img = init_image(event->mlx, tmp.width, tmp.height);
	event->img = init_image(event->mlx, (event->scene).width, (event->scene.height));
	i = 0;
	raytracer(event, &(event->scene), 0);
	while (i < tmp.height)
	{
		j = 0;
		while (j < tmp.width)
		{
			((int *)(old_img->img_arr))[j + i * tmp.width] = take_average(event, event->scene, i, j);
			j++;
		}
		i++;
	}
	free(event->img);
	(event->img) = old_img;
	(event->scene).width = tmp.width;
	(event->scene).height = tmp.height;
	(event->scene).grain = tmp.grain;
	i = 0;
	mlx_put_image_to_window(event->mlx, event->win,
			old_img->img_ptr, 0, 0);
}
