/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_mesh_obj.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicola <nicola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 14:52:14 by nmanzini          #+#    #+#             */
/*   Updated: 2018/06/18 15:39:55 by nicola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*

open the file
read number of lines

*/

// main reading function per obj

int	read_obj_file(char *path)
{
	int fac_ver_num[2];
	if(!scan_obj_file(path,fac_ver_num))
	{
		// can be shortened with printf;
		ft_putstr("Error reading obj file at:");
		ft_putstr(path);
		ft_putchar('\n');
		return (0);
	}

	t_3v vertices;
	t_3v *faces;
	init_faces_vertices(&vertices, &faces, fac_ver_num);
	fill_f_v_obj_file(path, &vertices);
	return(1);
}

int	init_faces_vertices( t_3v *vertices, t_3v **faces, int *fac_ver_num)
{
	int i;

	i = -1;
	vertices = (t_3v *)malloc((fac_ver_num[1] + 1) * sizeof(t_3v));
	// faces = (t_3v **)malloc((fac_ver_num[0] + 1) * sizeof(t_3v*));
	// while (++i < fac_ver_num[0])
	// {
	// 	faces[i] = (t_3v *)malloc((3 * sizeof(t_3v)));
	// }
	return(1);
}

int		fill_f_v_obj_file(char *path,  t_3v *vertices )
{
	int		fd;
	char	*line;
	int		v_i;
	int		f_i;
	// int		ver_order[3];

	char *str;

	v_i = -1;
	f_i = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	while (get_next_line(fd, &line) > 0)
	{
		if (*line == 'v'  && line[1] == ' ')
		{
			// update_vector(&vertices[++v_i],&line[2]);
			get_doubles_from_line(vertices[++v_i].v, &line[2],3);
			str = get_vector_string(vertices[v_i], 5);
			ft_putendl(str);
		}
		free(line);
	}
	free(line);

	if (close(fd) == -1)
		return (0);

	return (1);
}

// scanner

int		scan_obj_file(char *path, int *fac_ver_num)
{
	int		fd;
	char	*line;

	fac_ver_num[0] = 0;
	fac_ver_num[1] = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	while (get_next_line(fd, &line) > 0)
	{
		if (*line == 'v'  && line[1] == ' ')
			fac_ver_num[1]++;
		else if (*line == 'f' && line[1] == ' ')
			fac_ver_num[0]++;
		free(line);
	}
	free(line);

	// TESTING OUTPUT
	ft_putstr("Faces number = ");
	ft_putnbr(fac_ver_num[0]);
	ft_putchar(10);
	ft_putstr("Vertex number = ");
	ft_putnbr(fac_ver_num[1]);
	ft_putchar(10);
	// 

	if (close(fd) == -1)
		return (0);
	if (fac_ver_num[0] < 1 || fac_ver_num[1] < 3)
		return (0);
	return (1);
}