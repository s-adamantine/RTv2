/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 13:57:58 by mpauw             #+#    #+#             */
/*   Updated: 2018/02/07 13:41:00 by mpauw            ###   ########.fr       */
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

double	get_nearest_intersection(double a, double b, double d)
{
	double	t_1;
	double	t_2;

	t_1 = (-b + sqrt(d)) / (2 * a);
	t_2 = (-b - sqrt(d)) / (2 * a);
	if (t_1 < 0.001 && t_2 < 0.001)
		return (-1);
	if (t_1 < 0.001)
		return (t_2);
	if (t_2 < 0.001)
		return (t_1);
	else
		return ((t_1 < t_2) ? t_1 : t_2);
}
