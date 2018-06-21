/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_mesh_obj.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 14:52:14 by nmanzini          #+#    #+#             */
/*   Updated: 2018/06/21 18:26:31 by nmanzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** takes a path of an obj file and returns a list of triangles
** every triangle is a list of 3 vector t_3v
** if verbose == 1 then prints out al the triangle (debug mode)
*/

t_3v	**read_obj_file(char *path, int verbose)
{
	int		fac_num;
	int		ver_num;
	t_3v	*vertices;
	t_3v	**faces;

	fac_num = 0;
	ver_num = 0;
	if (!scan_obj_file(path, &fac_num, &ver_num))
	{
		ft_putstr("Error reading obj file at: ");
		ft_putendl(path);
		exit(0);
	}
	vertices = (t_3v *)malloc((ver_num) * sizeof(t_3v));
	faces = (t_3v **)malloc((fac_num + 1) * sizeof(t_3v*));
	fill_f_v_obj_file(path, vertices, faces, fac_num);
	if (verbose)
		;
	faces[fac_num] = NULL;
	return (faces);
}

/*
** takes the obj path and fills all the vertex and faces linked to the
** vetecies
*/

int		fill_f_v_obj_file(char *path, t_3v *vertices, t_3v **faces, int ver_num)
{
	int		fd;
	char	*line;
	int		v_i;
	int		f_i[2];

	v_i = -1;
	f_i[0] = -1;
	f_i[1] = ver_num;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	while (get_next_line(fd, &line) > 0)
	{
		if (*line == 'v' && line[1] == ' ')
		{
			update_vector_xyz(&(vertices[++v_i]), &(line[2]));
		}
		else if (*line == 'f' && line[1] == ' ')
			fill_triangle(line, faces, f_i, vertices);
		free(line);
	}
	free(line);
	if (close(fd) == -1)
		return (0);
	return (1);
}

/*
** scann the obj file for number of vertices and faces
** this number will be later used for allocation pourposes.
** checks also that the number of faces and vertex is > than minimum
*/

int		scan_obj_file(char *path, int *fac_num, int *ver_num)
{
	int		fd;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	while (get_next_line(fd, &line) > 0)
	{
		if (*line == 'v' && line[1] == ' ')
			(*ver_num)++;
		else if (*line == 'f' && line[1] == ' ')
			(*fac_num)++;
		free(line);
	}
	free(line);
	if (close(fd) == -1)
		return (0);
	if (*fac_num < 1 || *ver_num < 3)
		return (0);
	return (1);
}

/*
** takes a string and fills the i_f[0] triangle with the vertex in the string
** i_f[1] is the number of vertices, so it is the maximum callable value.
*/

int		fill_triangle(char *line, t_3v **faces, int *f_i, t_3v *vertices)
{
	int		ver_order[3];

	get_int_from_line(ver_order, &(line[2]), 3);
	if (ver_order[0] != ver_order[1] &&
		ver_order[0] != ver_order[2] &&
		ver_order[1] != ver_order[2] &&
		ver_order[0] <= f_i[1] && ver_order[0] >= 0 &&
		ver_order[1] <= f_i[1] && ver_order[1] >= 0 &&
		ver_order[2] <= f_i[1] && ver_order[2] >= 0)
	{
		f_i[0] += 1;
		faces[*f_i] = (t_3v *)malloc(3 * sizeof(t_3v));
		faces[*f_i][0] = vertices[ver_order[0] - 1];
		faces[*f_i][1] = vertices[ver_order[1] - 1];
		faces[*f_i][2] = vertices[ver_order[2] - 1];
	}
	else
	{
		ft_putstr("error in the obj file in line:\n");
		ft_putendl(line);
	}
	return (0);
}

/*
** takes a triangle ( an array of 3 t_3v) and its id i and prints it
*/

int		printf_triangle(t_3v *triangle, int i)
{
	char	*str;
	int		j;

	printf("trianagle %d:\n", i);
	j = -1;
	while (++j < 3)
	{
		str = get_vector_string(triangle[j], 3);
		printf("\t%s\n", str);
	}
	return (0);
}
