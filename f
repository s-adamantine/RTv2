get_intensity.c:	if (size == 0 && obj->type != 3)
get_intensity.c:	d = ((obj->m).diffuse / M_PI) * angle;
get_intensity.c:	i.spec = ((obj->m).specular * pow(angle, (obj->m).shininess));
get_t_value.c:	if (!(obj->visible))
get_t_value.c:	if (!(obj->visible))
get_t_value.c:	if (!(obj->visible))
get_t_value.c:	if (!(obj->visible))
set_light_per_pixel.c:	if ((obj->pattern).type == 0)
set_light_per_pixel.c:		(src->tmp_color).v[0] *= (obj->m).transparent * ((obj->m).color).v[0];
set_light_per_pixel.c:		(src->tmp_color).v[1] *= (obj->m).transparent * ((obj->m).color).v[1];
set_light_per_pixel.c:		(src->tmp_color).v[2] *= (obj->m).transparent * ((obj->m).color).v[2];
set_light_per_pixel.c:		t_value = obj->f(obj->fixed_s[thread_id][cam][src->id - 1], dir, 2, obj);
set_light_per_pixel.c:		if (obj->type == 1)
set_light_per_pixel.c:		if (t_value > 0.001 && t_value < 0.99999 && obj->visible)
set_light_per_pixel.c:	if (((p->pi_arr[i])->vis_obj->id) == 0)
set_object.c:				obj->m = *material;
set_object.c:				obj->m2 = *material;
set_object.c:	obj->id = id;
set_object.c:	obj->type = 0;
set_object.c:	obj->f = &get_t_plane;
set_object.c:	obj->axis_rotation = 0;
set_object.c:	obj->origin = def;
set_object.c:	obj->rotation = def;
set_object.c:	obj->axis_rotation = 0;
set_object.c:	obj->radius = 1;
set_object.c:	obj->pattern_id = 0;
set_object.c:	obj->lim_by_1 = 0;
set_object.c:	obj->lim_by_2 = 0;
set_object.c:	obj->limit_id = 0;
set_object.c:	obj->visible = 1;
set_object.c:		obj->f = &get_t_plane;
set_object.c:		obj->type  = 0;
set_object.c:		obj->f = &get_t_sphere;
set_object.c:		obj->type = 1;
set_object.c:		obj->f = &get_t_cylinder;
set_object.c:		obj->type = 2;
set_object.c:		obj->f = &get_t_cone;
set_object.c:		obj->type = 3;
set_object.c:			obj->pattern = *p;
set_object.c:			obj->pattern_id = id;
set_object.c:		update_vector(&(obj->origin), value);
set_object.c:		update_vector(&(obj->rotation), value);
set_object.c:		obj->axis_rotation = ft_atod(value);
set_object.c:		obj->radius = ft_atod(value);
set_object.c:		obj->lim_by_1 = ft_atoi(value);
set_object.c:		obj->lim_by_2 = ft_atoi(value);
set_object.c:		obj->limit_id = ft_atoi(value);
set_object.c:		obj->visible = ft_atoi(value);
set_object.c:		set_values_material(&(obj->m), s, value);
set_scene.c:	while (tmp_obj && tmp_obj->content)
set_scene.c:		obj = (t_object *)tmp_obj->content;
set_scene.c:		if (obj->limit_id == lim_id_1 && ++set)
set_scene.c:		else if (obj->limit_id == lim_id_2 && ++set)
set_scene.c:		tmp_obj = tmp_obj->next;
set_scene.c:	while (tmp_obj && tmp_obj->content)
set_scene.c:		obj = (t_object *)tmp_obj->content;
set_scene.c:		if (obj->lim_by_1 > 0 && obj->lim_by_2 > 0)
set_scene.c:			get_limit_object(scene->objects, obj->lim_by_1,
set_scene.c:					obj->lim_by_2, obj);
set_scene.c:		tmp_obj = tmp_obj->next;
set_t_values.c:	while (tmp_obj && tmp_obj->content)
set_t_values.c:		obj = (t_object *)tmp_obj->content;
set_t_values.c:		tmp = obj->f(obj->fixed_c[sc->thread_id][(sc->cam)->id][p->amount_p], dir, 0, obj);
set_t_values.c:		tmp_obj = tmp_obj->next;
set_t_values.c:	p->color = ft_init_3v((color.v)[0] * (obj->m).ambient * scene->ambient,
set_t_values.c:			(color.v)[1] * (obj->m).ambient * scene->ambient,
set_t_values.c:			(color.v)[2] * (obj->m).ambient * scene->ambient);
tools_limits.c:	if (!(obj->visible))
tools_limits.c:	if (obj->lim_by_1 <= 0 || obj->lim_by_2 <= 0)
tools_limits.c:	c = within_planes(obj->obj_lim_1, obj->obj_lim_2, point);
tools_limits.c:	obj->currently_visible = c;
tools_vector.c:	if (obj->type == 0)
tools_vector.c:		return (rotate_v(ft_get_3v_unit(2), obj->rotation));
tools_vector.c:		norm_t = ft_3v_subtract(point, obj->origin);
tools_vector.c:	norm_t = rotate_v_inv(norm_t, obj->rotation);
tools_vector.c:	if (obj->type == 2)
tools_vector.c:	if (obj->type == 3)
tools_vector.c:	if (size == 0 && obj->type != 3)
tools_vector.c:	norm_t = rotate_v(norm_t, obj->rotation);
