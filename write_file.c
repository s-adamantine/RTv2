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

//need to protect against reading an empty file
//protect against reading image that's too big
//protect against a file format that isn't width and height and a number in the header
void	read_image(t_event *event)
{
	FILE	*fp;
	char	*line;
	char	**params;

	ft_putstr("Which image would you like to load? ");
	get_next_line(0, &line);
	fp = fopen(line, "r");
	params = ft_strsplit(fgets(line, 100, fp), ' ');
	//do I have to init an image?
	event->img.width = ft_atoi(params[1]);
	event->img.height = ft_atoi(params[3]);
	event->
}

void	write_file(t_event *event)
{
	FILE	*fp;
	char	*name;
	int		*data;
	int		i;

	i = 0;
	//need to protect against rewriting a file
	ft_putstr("Saving scene.\nFile name: ");
	get_next_line(0, &name);
	fp = fopen(name, "w");
	data = (int *)event->img.img_arr;
	fprintf(fp, "width: %d height: %d\n", event->img.width, event->img.height);
	while (data[i])
		fprintf(fp, "%d ", data[i++]);
	fclose(fp);
}
