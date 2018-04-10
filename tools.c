/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 13:57:58 by mpauw             #+#    #+#             */
/*   Updated: 2018/04/10 15:55:25 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	update_vector(t_3v *vector, char *line)
{
	double	*tmp;
	int		i;

	if (!(tmp = (double *)malloc(3 * sizeof(double))))
		error(0);
	get_doubles_from_line(tmp, line, 3);
	i = 0;
	while (i < 3)
	{
		(vector->v)[i] = tmp[i];
		i++;
	}
	free(tmp);
}

void	get_doubles_from_line(double *v, char *line, int size)
{
	char		**values_str;
	int			i;

	values_str = ft_strsplit((line), ' ');
	i = 0;
	while (*(values_str + i))
		i++;
	if (i != size)
		s_error("Not the right amount of vector values");
	i = -1;
	while (++i < size)
		v[i] = ft_atod(values_str[i]);
	ft_free_array((void **)values_str);
}

char	*get_vector_string(t_3v v, int precision)
{
	char	*s;
	char	*v0;
	char	*v1;
	char	*v2;
	int		size;

	v0 = ft_dtoa(v.v[0], precision);
	v1 = ft_dtoa(v.v[1], precision);
	v2 = ft_dtoa(v.v[2], precision);
	size = ft_strlen(v0) + ft_strlen(v1) + ft_strlen(v2) + 3;
	if (!(s = (char *)malloc(sizeof(char) * size)))
		error(1);
	ft_bzero(s, size);
	s = ft_strcat(s, v0);
	s = ft_strcat(s, " ");
	s = ft_strcat(s, v1);
	s = ft_strcat(s, " ");
	s = ft_strcat(s, v2);
	free(v0);
	free(v1);
	free(v2);
	return (s);
}
