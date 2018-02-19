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

static void		check_values(t_intensity *in, t_object o, t_source l)
{
	if (in->diff > 1)
		in->diff = 1;
	if (in->spec > 1)
		in->spec = 1;
	if (((o.color).v)[0] > 1 || ((o.color).v)[1] > 1 || ((o.color).v)[2] > 1
			|| ((o.color).v)[0] < 0 || ((o.color).v)[1] < 0
			|| ((o.color).v)[2] < 0 || ((l.color).v)[0] > 1
			|| ((l.color).v)[1] > 1 || ((l.color).v)[2] > 1
			|| ((l.color).v)[0] < 0 || ((l.color).v)[1] < 0
			|| ((l.color).v)[2] < 0)
		error(4);
}

static void		set_light_value(t_intensity in, t_pixel *pixel,
		t_source l, int i)
{
	t_3v		*c;
	t_object	o;
	double		influence;

	o = *((pixel->vis_obj_r)[i]);
	c = &(pixel->c_per_src[l.id - 1]);
	influence = 1.0;
	while (i > 0)
	{
		influence *= ((pixel->vis_obj_r)[i - 1])->specular;
		i--;
	}
	in.diff = in.diff * (l.intensity).diff;
	in.spec = in.spec * (l.intensity).spec;
	check_values(&in, o, l);
	(c->v)[0] += influence * (1 - in.spec) * in.diff * ((l.color).v)[0] * ((o.color).v)[0];
	(c->v)[1] += influence * (1 - in.spec) * in.diff * ((l.color).v)[1] * ((o.color).v)[1];
	(c->v)[2] += influence * (1 - in.spec) * in.diff * ((l.color).v)[2] * ((o.color).v)[2];
	(c->v)[0] += in.spec * ((l.color).v)[0];
	(c->v)[1] += in.spec * ((l.color).v)[1];
	(c->v)[2] += in.spec * ((l.color).v)[2];
}

static void		light_intensity(t_source src, t_pixel *pixel, t_event *event)
{
	t_3v		dir;
	t_scene		scene;
	t_intensity	in;
	t_cam		view;
	int			i;

	scene = event->scene;
	i = 0;
	while (i < scene.refl && pixel->vis_obj_r[i])
	{
		dir = ft_3v_subtract(pixel->point_r[i], (src.origin));
		in.diff = 0;
		in.spec = 0;
		if (i == 0)
			view = scene.camera;
		else
		{
			view.origin = pixel->point_r[i - 1];
			view.rotation = ft_zero_3v();
		}
		if (light_reaches(dir, scene.objects, src.id) > 0.01)
			in = get_intensity(pixel->point_r[i], pixel->vis_obj_r[i],
					dir, view);
		set_light_value(in, pixel, src, i);
		i++;
	}
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
			light_intensity(src, pixel, event);
		}
		i++;
	}
}
