/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_mesh_obj.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicola <nicola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 14:52:14 by nmanzini          #+#    #+#             */
/*   Updated: 2018/06/18 18:29:02 by nicola           ###   ########.fr       */
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
	int	fac_num;
	int	ver_num;
	t_3v *vertices;
	t_3v **faces;

	fac_num = 0;
	ver_num = 0;
	if(!scan_obj_file(path, &fac_num, &ver_num))
	{
		// can be shortened with printf;
		ft_putstr("Error reading obj file at: ");
		ft_putendl(path);
		exit(0);
	}

	vertices = (t_3v *)malloc((ver_num) * sizeof(t_3v));
	faces = (t_3v **)malloc((fac_num) * sizeof(t_3v*));
	fill_f_v_obj_file(path, vertices, faces);

	if( verbose)
	{
		printf("number of vertices = %d\n",ver_num);
		printf("number of faces = %d\n",fac_num);
		ver_num = -1;
		while(++ver_num < fac_num)
			printf_triangle(faces[ver_num],ver_num);
	}
	return(faces);
}

/*
** takes the obj path and fills all the vertex and faces linked to the
** vetecies
*/

int		fill_f_v_obj_file(char *path,  t_3v *vertices , t_3v **faces)
{
	int		fd;
	char	*line;
	int		v_i;
	int		f_i;

	v_i = -1;
	f_i = -1;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	while (get_next_line(fd, &line) > 0)
	{
		if (*line == 'v'  && line[1] == ' ')
		{
			vertices[++v_i] = ft_zero_3v();
			update_vector(&(vertices[v_i]), &(line[2]));
		}
		else if (*line == 'f'  && line[1] == ' ')
			fill_triangle(line, faces, ++f_i, vertices);
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

	if (close(fd) == -1)
		return (0);
	if (*fac_ver_num_0 < 1 || *fac_ver_num_1 < 3)
		return (0);
	return (1);
}

/*
** takes a string and fills the i_f triangle with the vertex in the string
*/

int		fill_triangle(char *line, t_3v **faces, int f_i, t_3v *vertices)
{
	int		ver_order[3];

	get_int_from_line(ver_order, &(line[2]), 3);
	faces[f_i] = (t_3v *)malloc(3 * sizeof(t_3v));
	faces[f_i][0] = vertices[ver_order[0] - 1];
	faces[f_i][1] = vertices[ver_order[1] - 1];
	faces[f_i][2] = vertices[ver_order[2] - 1];
	return(0);
}

/*
** takes a triangle ( an array of 3 t_3v) and its id i and prints it
*/

int		printf_triangle(t_3v *triangle, int i)
{
	char *str;
	int j;

	printf("trianagle %d:\n", i);
	j = -1;
	while(++j <3)
	{
		str = get_vector_string(triangle[j], 3);
		printf("\t%s\n", str);
	}
	return(0);
}
