#include "rtv1.h"

static int	turn_off_or_on(t_scene *scene, int id)
{
	t_source	*src;
	t_list		*s_lst;

	s_lst = (scene->lights)->next;
	if (id == KEY_0)
		scene->all_on = (scene->all_on) ? 0 : 1;
	while (s_lst && s_lst->content)
	{
		src = (t_source *)s_lst->content;
		if (id == KEY_0)
			src->on = (scene->all_on) ? 1 : 0;
		else if (id == src->id)
		{
			src->on = (src->on) ? 0 : 1;
			return (1);
		}
		s_lst = s_lst->next;
	}
	if (id == KEY_0)
		return (1);
	return (0);
}

static void	switch_one(t_event *event, int id)
{
	int		i;
	int		j;
	t_pixel	*p;

	i = 0;
	while (i < (event->scene).height)
	{
		j = 0;
		while (j < (event->scene).width)
		{
			p = &((event->p_array)[j + i * (event->scene).width]);
			if (p->vis_obj[0])
			{
				if (id == 0)
					p->color = p->c_per_src[0];
				else
					p->color = ft_3v_add((p->c_per_src)[id], p->color);
			}
			((int *)(event->img)->img_arr)
				[j + (event->scene).width * i] = get_color(p->color);
			j++;
		}
		i++;
	}
}

void		turn_on_lights(t_event *event)
{
	t_source	*src;
	t_list		*s_lst;

	event->redraw = 1;
	if (!(turn_off_or_on(&(event->scene), event->id_select)))
		return ;
	switch_one(event, 0);
	s_lst = ((event->scene).lights)->next;
	if (event->id_select == KEY_0 && !((event->scene).all_on))
		return ;
	while (s_lst && s_lst->content)
	{
		src = (t_source *)s_lst->content;
		if (src->on)
			switch_one(event, src->id);
		s_lst = s_lst->next;
	}
}

void		*init_light_values(void *arg)
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
