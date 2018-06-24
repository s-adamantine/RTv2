/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadamant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 18:12:10 by sadamant          #+#    #+#             */
/*   Updated: 2018/06/23 18:12:18 by sadamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	file_exists(char *name)
{
	int		fd;
	char	*input;

	fd = open(name, O_RDONLY);
	close(fd);
	if (fd > 0)
	{
		ft_putstr("A file with that name already exists.\n");
		ft_putstr("Would you like to overwrite it? y/n\n");
		get_next_line(0, &input);
		if (ft_strncmp(input, "n", 1) == 0)
			ft_putstr("Scene not saved.\n");
		else if (ft_strcmp(input, "y") == 0)
		{
			free(input);
			return (0);
		}
		else
			ft_putstr("Error: Invalid input.\n");
		free(input);
		return (1);
	}
	return (0);
}

// static void	init_bitmap_image(t_event *event, int w, int h)
// {
//
// }

//protect against a file format that isn't width and height and a number in the header
//protect against accessing a tampered image file
void	read_image(t_event *event)
{
	FILE	*fp;
	char	*line;
	char	**tmp;
	int		i;
	t_img	img;

	i = 0;
	ft_putstr("Which image would you like to load? ");
	get_next_line(0, &line);
	if (!(fp = fopen(line, "r")))
	{
		ft_putstr("Error: File not found.\n");
		free(line);
		fclose(fp);
		return ;
	}
	tmp = ft_strsplit(fgets(line, 100, fp), ' ');
	img.img_ptr = mlx_new_image(event->mlx, ft_atoi(tmp[1]), ft_atoi(tmp[3]));
	img.bitmap = (int *)mlx_get_data_addr(img.img_ptr,
		&(img.bpp), &(img.size_line), &(img.endian));
	img.width = ft_atoi(tmp[1]);
	img.height = ft_atoi(tmp[3]);
	ft_free_array((void **)tmp);
	while (i < (img.width * img.height))
		img.bitmap[i++] = ft_atoi(fgets(line, 10, fp));
	free(line);
	fclose(fp);
	mlx_put_image_to_window(event->mlx, event->win, img.img_ptr, 0, 0);
	init_loop(event);
}

void	save_image(t_event *event)
{
	FILE	*fp;
	char	*name;
	char	*path;
	int		*data;
	int		i;

	i = 0;
	ft_putstr("Saving scene.\nWhat name should I save it to? ");
	get_next_line(0, &name);
	path = ft_strcat_alloc("./images/", name);
	if (!file_exists(path))
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
