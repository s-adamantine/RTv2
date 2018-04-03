#include "rtv1.h"

void	*turn_on_all(void *arg)
{
	int		i;
	int		j;
	int		k;
	t_event	*event;
	t_pixel	*p;

	event = (t_event *)arg;
	i = -1;
	while (++i < (event->scene).height)
	{
		j = -1;
		while (++j < (event->scene).width)
		{
			p = &((event->p_array)[j + i * (event->scene).width]);
			if (p->vis_obj[0])
			{
				k = -1;
				while (++k < (event->scene).amount_light)
					p->color = ft_3v_add((p->c_per_src)[k], p->color);
			}
			((int *)(event->img)->img_arr)
				[j + (event->scene).width * i] = get_color(p->color);
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
	s_lst = ((event->scene).lights)->next;
	while (s_lst && s_lst->content)
	{
		src = (t_source *)s_lst->content;
		set_light_per_pixel(event, *src);
		s_lst = s_lst->next;
	}
	return (NULL);
}
