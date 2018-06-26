/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 14:11:11 by mpauw             #+#    #+#             */
/*   Updated: 2018/06/26 11:50:42 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	create_threads(t_event *event, void *(*f)(void*))
{
	int			i;
	pthread_t	thread[THREADS];
	t_event		t[THREADS];

	i = 0;
	while (i < THREADS)
	{
		ft_memcpy((void*)&t[i], (void*)event, sizeof(t_event));
		t[i].scene.thread_id = i;
		pthread_create(&thread[i], NULL, f, &t[i]);
		i++;
	}
	i = 0;
	while (i < THREADS)
	{
		pthread_join(thread[i], NULL);
		i++;
	}
}
