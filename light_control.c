#include "rtv1.h"

void	*turn_on_all(void *arg)
{
	int		i;
	int		j;
	int		k;
	t_event	*event;
	t_pixel	*pixel;

	event = (t_event *)arg;
	i = -1;
	while (++i < (event->scene).height)
	{
		j = -1;
		while (++j < (event->scene).width)
		{
			pixel = &((event->p_array)[j + i * (event->scene).width]);
			if (pixel->vis_obj)
			{
				k = -1;
				while (++k < (event->scene).amount_light)
					pixel->color = ft_3v_add((pixel->c_per_src)[k], pixel->color);
			}
			((int *)(event->img)->img_arr)
				[j + (event->scene).width * i] = get_color(pixel->color);
		}
	}
	return (NULL);
}

void	*init_light_values(void *arg)
{
	t_event			*event;
	t_list			*s_lst;
	t_source		*src;

	event = (t_event *)arg;
	s_lst = (event->scene).lights;
	while (s_lst && s_lst->content)
	{
		src = (t_source *)s_lst->content;
		(event->scene).cur_src = *src;
		set_light_per_pixel(event, *src);
		s_lst = s_lst->next;
	}
	return (NULL);
}
