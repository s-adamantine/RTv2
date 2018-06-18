/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_mesh_obj.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicola <nicola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 14:52:14 by nmanzini          #+#    #+#             */
/*   Updated: 2018/06/18 16:31:29 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*

open the file
read number of lines

*/

// main reading function per obj

void	read_obj_file(char *path)
{
//	int fac_ver_num[2];
	int	fac_ver_num_0;
	int	fac_ver_num_1;

	fac_ver_num_0 = 0;
	fac_ver_num_1 = 0;
	if(!scan_obj_file(path,&fac_ver_num_0,&fac_ver_num_1))
	{
		// can be shortened with printf;
		ft_putstr("Error reading obj file at:");
		ft_putstr(path);
		ft_putchar('\n');
		exit(0);
	}
	t_3v *vertices;
	t_3v *faces;
	vertices = (t_3v *)malloc((fac_ver_num_1 + 1) * sizeof(t_3v));
	init_faces_vertices(vertices, &faces, fac_ver_num_1);
	fill_f_v_obj_file(path, vertices);
}

int	init_faces_vertices( t_3v *vertices, t_3v **faces, int fac_ver_num_1)
{
	int i;

	(void)faces;
	(void)vertices;
	(void)fac_ver_num_1;
	i = -1;
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

	v_i = 0;
	f_i = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	while (get_next_line(fd, &line) > 0)
	{
		if (*line == 'v'  && line[1] == ' ')
		{
			vertices[v_i] = ft_zero_3v();
			update_vector(&(vertices[v_i]), &(line[2]));
			str = get_vector_string(vertices[v_i], 5);
			ft_putendl(str);
			v_i++;
		}
		free(line);
	}
	free(line);

	if (close(fd) == -1)
		return (0);

	return (1);
}

// scanner

int		scan_obj_file(char *path, int *fac_ver_num_0, int *fac_ver_num_1)
{
	int		fd;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	while (get_next_line(fd, &line) > 0)
	{
		if (*line == 'v'  && line[1] == ' ')
			(*fac_ver_num_1)++;
		else if (*line == 'f' && line[1] == ' ')
			(*fac_ver_num_0)++;
		free(line);
	}
	free(line);

	// TESTING OUTPUT
	ft_putstr("Faces number = ");
	ft_putnbr(*fac_ver_num_0);
	ft_putchar(10);
	ft_putstr("Vertex number = ");
	ft_putnbr(*fac_ver_num_1);
	ft_putchar(10);
	// 

	if (close(fd) == -1)
		return (0);
	if (*fac_ver_num_0 < 1 || *fac_ver_num_1 < 3)
		return (0);
	return (1);
}
