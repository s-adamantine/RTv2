/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_image_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadamant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 19:29:49 by sadamant          #+#    #+#             */
/*   Updated: 2018/06/25 19:31:34 by sadamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void		reinitialize_screen(t_event *event, int w, int h)
{
	mlx_destroy_window(event->mlx, event->win);
	event->win = mlx_new_window(event->mlx, w, h, "RT");
	event->scene.width = w;
	event->scene.height = h;
}

static t_img	init_bitmap_image(t_event *event, int w, int h)
{
	t_img	img;

	img.img_ptr = mlx_new_image(event->mlx, w, h);
	img.bitmap = (int *)mlx_get_data_addr(img.img_ptr, &(img.bpp),
			&(img.size_line), &(img.endian));
	img.width = w;
	img.height = h;
	return (img);
}

/*
** need to protect against an invalid file format
** protect against a file format that isn't width and height and a
** number in the header
** protect against inputting the name of a folder
** protect against accessing a tampered image file
** protect against saving the name of a folder
*/

void			read_image_file(t_event *event)
{
	FILE	*fp;
	char	*line;
	char	**tmp;
	int		i;
	t_img	img;

	i = 0;
	ft_putstr("Which image would you like to load? ");
	get_next_line(0, &line);
	if (!file_exists(line))
		s_error("Image not found.");
	fp = fopen(line, "r");
	tmp = ft_strsplit(fgets(line, 100, fp), ' ');
	if (ft_atoi(tmp[1]) != event->scene.width ||
			ft_atoi(tmp[3]) != event->scene.height)
		reinitialize_screen(event, ft_atoi(tmp[1]), ft_atoi(tmp[3]));
	img = init_bitmap_image(event, ft_atoi(tmp[1]), ft_atoi(tmp[3]));
	ft_free_array((void **)tmp);
	while (i < (img.width * img.height))
		img.bitmap[i++] = ft_atoi(fgets(line, 10, fp));
	free(line);
	fclose(fp);
	mlx_put_image_to_window(event->mlx, event->win, img.img_ptr, 0, 0);
	init_loop(event);
}

void			save_image_file(t_event *event)
{
	FILE	*fp;
	char	*name;
	char	*path;
	int		*data;
	int		i;

	i = 0;
	ft_putstr("Saving scene.\nWhat name should I save it to? ");
	get_next_line(0, &name);
	if (ft_strchr(name, '/'))
		s_error("Invalid file name.");
	path = ft_strcat_alloc("./images/", name);
	if (!file_exists_save(path))
	{
		fp = fopen(path, "w");
		data = (int *)event->img.img_arr;
		fprintf(fp, "width: %d height: %d\n", event->img.width,
			event->img.height);
		while (i < (event->img.width * event->img.height))
			fprintf(fp, "%08d ", data[i++]);
		fclose(fp);
		ft_putstr("File successfully saved.\n");
	}
	free(name);
	free(path);
}
