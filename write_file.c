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

//need to protect against reading an empty file/one that doesn't exist
//protect against reading image that's too big
//protect against a file format that isn't width and height and a number in the header
void	read_image(t_event *event)
{
	FILE	*fp;
	char	*line;
	char	**params;
	int		i;

	i = 0;
	ft_putstr("Which image would you like to load? ");
	get_next_line(0, &line);
	fp = fopen(line, "r");
	params = ft_strsplit(fgets(line, 100, fp), ' ');
	event->img.img_ptr = mlx_new_image(event->mlx, ft_atoi(params[1]),
		ft_atoi(params[3]));
	event->img.bitmap = (int *)mlx_get_data_addr(event->img.img_ptr,
		&(event->img.bpp), &(event->img.size_line), &(event->img.endian));
	event->img.width = ft_atoi(params[1]);
	event->img.height = ft_atoi(params[3]);
	while (i < (event->img.width * event->img.height))
		event->img.bitmap[i++] = ft_atoi(fgets(line, 10, fp));
	mlx_put_image_to_window(event->mlx, event->win,
		(event->img).img_ptr, 0, 0);
	init_loop(event);
}

void	save_image(t_event *event)
{
	FILE	*fp;
	char	*name;
	char	*input;
	int		*data;
	int		i;

	i = 0;
	ft_putstr("Saving scene.\nWhat name should I save it to? ");
	get_next_line(0, &name);
	if (open(name, O_RDONLY) > 0)
	{
		ft_putstr("The file already exists. Are you sure you want to overwrite it? y/n\n");
		get_next_line(0, &input);
		if (ft_strncmp(input, "n", 1) == 0)
		{
			ft_putstr("Scene not saved.\n");
			return ;
		}
		else if (ft_strncmp(input, "y", 1) != 0)
		{
			ft_putstr("Invalid input.\n");
			return ;
		}
	}
	fp = fopen(name, "w");
	data = (int *)event->img.img_arr;
	fprintf(fp, "width: %d height: %d\n", event->img.width, event->img.height);
	while (i < (event->img.width * event->img.height))
		fprintf(fp, "%08d ", data[i++]);
	ft_putstr("File successfully saved.\n");
	fclose(fp);
}
