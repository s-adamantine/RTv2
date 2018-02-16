#include "rtv1.h"

static int		light_reaches(t_3v dir, t_list *objects, int src_id)
{
	double		t_value;
	t_list		*o_lst;
	t_object	*obj;
	t_3v		dir_a;
	t_source	*rel_src;

	o_lst = objects;
	while (o_lst && o_lst->content)
	{
		obj = (t_object *)o_lst->content;
		dir_a = get_dir(dir, obj->rotation);
		rel_src = get_source(src_id, obj->rel_lights);
		t_value = obj->f(obj, dir_a, rel_src->origin);
		if (t_value > 0.001 && t_value < 0.99999)
			return (0);
		o_lst = o_lst->next;
	}
	return (1);
}

static void		get_pixel_value(t_3v point, t_pixel *pixel, t_scene scene,
		t_object *obj)
{
	t_source	src;
	t_3v		dir;
	t_intensity	intensity;

	src = scene.cur_src;
	dir = ft_3v_subtract(point, (src.origin));
	if (light_reaches(dir, scene.objects, src.id) > 0.01)
	{
		intensity = get_intensity(point, obj, dir, scene.camera);
		update_color(intensity, &(pixel->color), obj, src);
	}
}

static void		*get_light_values(void *arg)
{
	t_event		*event;
	t_pixel		*pixel;
	int			i;
	int			j;
	t_3v		point;
	t_3v		coor;
	int			pix_color;

	event = (t_event *)arg;
	i = 0;
	while (i < (event->scene).height)
	{
		j = 0;
		while (j < (event->scene).width)
		{
			pixel = &((event->p_array)[j + i * (event->scene).width]);
			j++;
			if (!pixel->vis_obj)
				continue ;
			coor = pixel->coor;
			point = ((event->scene).camera).origin;
			ft_3v_scalar(&coor, pixel->s_value);
			point = ft_3v_add(point, coor);
			get_pixel_value(point, pixel, event->scene, pixel->vis_obj);
			pix_color = get_color(pixel->color);
			((int *)(((t_event *)event)->img)->img_arr)
				[j + (event->scene).width * i] = get_color(pixel->color);
		}
		i++;
	}
	return (NULL);
}

void	*light_per_light(void *arg)
{
//	pthread_t	*l_threads;
	t_event		*event;
	t_list		*s_lst;
	t_source	*src;

	event = (t_event *)arg;
//	if (!(l_threads = (pthread_t *)malloc(sizeof(pthread_t) *
//					(event->scene).amount_light)))
//		error(1);
	s_lst = (event->scene).lights;
	while (s_lst && s_lst->content)
	{
		src = (t_source *)s_lst->content;
		(event->scene).cur_src = *src;
		get_light_values((void *)event);
//		pthread_create(&(l_threads[src->id]), NULL, &get_light_values,
//				(void *)event);
		s_lst = s_lst->next;
		mlx_put_image_to_window(event->mlx, event->win,
			(event->img)->img_ptr, 0, 0);
	}
	return (NULL);
}
