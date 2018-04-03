/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 08:05:39 by mpauw             #+#    #+#             */
/*   Updated: 2018/03/21 14:28:24 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	error(int err)
{
	if (err == 0)
		ft_putstr_fd("Error: Error reading file\n", 2);
	else if (err == 1)
		ft_putstr_fd("Error: Error in memory allocation\n", 2);
	else if (err == 2)
		ft_putstr_fd("Error: NULL returned\n", 2);
	else if (err == 3)
		ft_putstr_fd("Error: Values must be properly tabulated.\n", 2);
	else if (err == 4)
		ft_putstr_fd("Error: Color values must be between 0 and 1.\n", 2);
	else if (err == 5)
		ft_putstr_fd("Error: There is a vector of size 0. Check if there are\
				lights with the same coordinates as objects.\n", 2);
	exit(1);
}

void	s_error(const char *s)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}

void	usage(void)
{
	ft_putstr("You must enter a valid file name\n");
	exit(0);
}

void	run_threads(t_event *event)
{
	pthread_t	s_values;
	pthread_t	light_values;
	pthread_t	turn_on;

//	light_inside((void *)event);
	pthread_create(&s_values, NULL, &get_s_values, (void *)event);
	pthread_join(s_values, NULL);
	pthread_create(&light_values, NULL, &init_light_values, (void *)event);
	pthread_join(light_values, NULL);
	pthread_create(&turn_on, NULL, &turn_on_all, (void *)event);
	pthread_join(turn_on, NULL);
	mlx_put_image_to_window(event->mlx, event->win,
			(event->img)->img_ptr, 0, 0);
	init_loop(event);
}

int		main(int argc, char **argv)
{
	int			fd;
	t_scene		scene;
	t_event		event;

	if (argc != 2)
		usage();
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		error(0);
	set_scene(fd, &scene);
	if (!(scene.cam_set))
		error(0);
	set_fixed_values(&scene);
	event = init_window(scene);
	run_threads(&event);
}
