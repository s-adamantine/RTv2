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

static t_3v		get_point(t_event *event, t_pixel *pixel)
{
	t_3v		point;
	t_3v		coor;

	coor = pixel->coor;
	change_dir(&coor, ((event->scene).camera).rotation);
	point = ((event->scene).camera).origin;
	ft_3v_scalar(&coor, pixel->s_value);
	point = ft_3v_add(point, coor);
	return (point);
}

static void		set_light_value(t_intensity intensity, t_pixel *pixel,
		t_object *o, t_source l)
{
	t_3v	*color;

	color = &(pixel->c_per_src[l.id - 1]);
	intensity.diff = intensity.diff * (l.intensity).diff;
	intensity.spec = intensity.spec * (l.intensity).spec;
	if (intensity.diff > 1)
		intensity.diff = 1;
	if (intensity.spec > 1)
		intensity.spec = 1;
	if (((o->color).v)[0] > 1 || ((o->color).v)[1] > 1 || ((o->color).v)[2] > 1
			|| ((o->color).v)[0] < 0 || ((o->color).v)[1] < 0
			|| ((o->color).v)[2] < 0 || ((l.color).v)[0] > 1
			|| ((l.color).v)[1] > 1 || ((l.color).v)[2] > 1
			|| ((l.color).v)[0] < 0 || ((l.color).v)[1] < 0
			|| ((l.color).v)[2] < 0)
		error(4);
	(color->v)[0] += intensity.diff * ((l.color).v)[0] * ((o->color).v)[0];
	(color->v)[1] += intensity.diff * ((l.color).v)[1] * ((o->color).v)[1];
	(color->v)[2] += intensity.diff * ((l.color).v)[2] * ((o->color).v)[2];
	(color->v)[0] += intensity.spec * ((l.color).v)[0];
	(color->v)[1] += intensity.spec * ((l.color).v)[1];
	(color->v)[2] += intensity.spec * ((l.color).v)[2];
}

static void		light_intensity(t_source src, t_pixel *pixel, t_event *event,
		t_object *obj)
{
	t_3v		point;
	t_3v		dir;
	t_scene		scene;
	t_intensity	intensity;

	point = get_point(event, pixel);
	dir = ft_3v_subtract(point, (src.origin));
	scene = event->scene;
	intensity.diff = 0;
	intensity.spec = 0;
	if (light_reaches(dir, scene.objects, src.id) > 0.01)
		intensity = get_intensity(point, obj, dir, scene.camera);
	set_light_value(intensity, pixel, obj, src);
}

void		set_light_per_pixel(t_event *event, t_source src)
{
	t_pixel		*pixel;
	int			i;
	int			j;

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
			light_intensity(src, pixel, event, pixel->vis_obj);
		}
		i++;
	}
}
