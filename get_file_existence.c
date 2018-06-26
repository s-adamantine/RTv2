/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_existence.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadamant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 19:19:32 by sadamant          #+#    #+#             */
/*   Updated: 2018/06/26 11:49:51 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		put_error(const char *s)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("\n", 2);
}

int				file_exists(char *name)
{
	int		fd;

	fd = open(name, O_RDONLY);
	close(fd);
	if (fd > 0)
		return (1);
	return (0);
}

int				file_exists_save(char *name)
{
	int		fd;
	char	*input;

	fd = open(name, O_RDONLY);
	close(fd);
	if (fd > 0)
	{
		put_error("A file with that name already exists.");
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
			put_error("Invalid input.");
		free(input);
		return (1);
	}
	return (0);
}
