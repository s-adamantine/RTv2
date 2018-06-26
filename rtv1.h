/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 11:08:02 by mpauw             #+#    #+#             */
/*   Updated: 2018/06/26 11:03:43 by sadamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# define MAX_S_VALUE 50000
# define DEG 57.2958
# define THREADS 4
# define LIMIT_CORR 100

# define MENU_WIDTH 500
# define MENU_HEIGHT 1000
# define PRIMARY 0x9c27b0
# define SECONDARY 0x388e3c
# define P_LIGHT 0xd05ce3
# define P_DARK 0x6a0080
# define TEXT_L 0xffffff
# define TEXT_D 0x000000
# define GRAY 0xeceff1
# define GRAY_2 0xcfd8dc
# define TOP_BAR 100
# define MARGIN 20
# define SUB_MARGIN 10
# define INFO_MARGIN 150
# define MENU_LINE 20
# define OBJ_HEIGHT 140
# define CAM_HEIGHT 80
# define LIGHT_HEIGHT 120
# define AMOUNT_INSTRUCTIONS 7
# define AMOUNT_INFO 8
# define IMG_FOLDER "./images/"

# include "libft.h"

# include "mlx.h"
# include "keys.h"
# include "mlx_constants.h"

# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <stdio.h>
# include <errno.h>
# include <pthread.h>
# include <time.h>

typedef struct	s_img
{
	void		*img_ptr;
	char		*img_arr;
	int			*bitmap;
	int			width;
	int			height;
	int			bpp;
	int			size_line;
	int			size_line_int;
	int			endian;
	int			id;
}				t_img;

typedef struct	s_menu
{
	char		**info;
	char		**types;
	char		**man;
}				t_menu;

typedef struct	s_intensity
{
	double		spec;
	double		diff;
	double		attrition_diff;
	double		attrition_spec;
}				t_intensity;

typedef struct	s_source
{
	int			type;
	int			id;
	int			on;
	int			*inside_obj;
	t_intensity	intensity;
	t_3v		origin;
	t_3v		color;
	t_3v		tmp_color;
	double		max_intensity;
}				t_source;

typedef struct	s_fixed_v
{
	int			obj_id;
	double		val;
	double		val_2;
	double		rad;
	double		rad_sq;
	t_3v		vec;
	t_3v		vec2;
	t_3v		vertex0;
	t_3v		vertex1;
	t_3v		vertex2;
	t_3v		dif_c;
	t_3v		dir;
	t_3v		origin;
}				t_fixed_v;

typedef struct	s_material
{
	int			id;
	int			pattern;
	int			wavy;
	t_3v		color;
	t_3v		beer;
	t_3v		n_var;
	double		diffuse;
	double		ambient;
	double		specular;
	double		shininess;
	double		transparent;
	double		refractive_index;
}				t_material;

typedef struct	s_pattern
{
	int			id;
	int			type;
	double		size;
	int			amount_points;
	t_3v		*points_arr;
	double		distance;
	double		os_1;
	double		os_2;
}				t_pattern;

typedef struct	s_object
{
	int				id;
	int				type;
	int				pattern_id;
	int				lim_by_1;
	int				lim_by_2;
	int				limit_id;
	int				visible;
	int				group_id;
	int				is_group_main;
	struct s_object	*obj_lim_1;
	struct s_object	*obj_lim_2;
	t_material		m;
	t_material		m2;
	t_pattern		pattern;
	double			radius;
	double			size;
	double			(*f)();
	double			axis_rotation;
	t_3v			origin;
	t_3v			origin_2;
	t_3v			origin_3;
	t_3v			rotation;
	t_3v			dir;
	t_3v			group_origin;
	t_3v			group_rotation;
	t_fixed_v		**fixed_c[THREADS];
	t_fixed_v		**fixed_s[THREADS];
	char			*path;
}				t_object;

typedef struct	s_p_info
{
	t_3v		normal;
	double		s_value;
	t_object	*vis_obj;
	t_material	obj_m;
	t_3v		point;
	t_3v		dir;
	int			type;
	int			is_set;
	int			is_inside;
	double		fresnal_transparent;
	double		fresnal_specular;
	t_3v		beer;
}				t_p_info;

typedef struct	s_pixel
{
	int			status;
	int			amount_p;
	int			amount_refl;
	int			type;
	double		index_refract;
	t_3v		*c_per_src;
	t_3v		coor;
	t_3v		color;
	t_p_info	**pi_arr;
}				t_pixel;

typedef struct	s_cam
{
	int			id;
	int			init;
	int			grain;
	t_3v		origin;
	t_3v		rotation;
	t_pixel		*p_array;
	double		*light_vis;
	int			*pixel_set;
	int			selected;
}				t_cam;

typedef struct	s_scene
{
	char		*name;
	int			width;
	int			height;
	int			amount_obj;
	int			amount_light;
	int			amount_fixed;
	int			amount_material;
	int			amount_pattern;
	int			cam_set;
	int			grain;
	int			anti_a;
	int			max_anti_a;
	int			step_size;
	int			refl;
	int			filter;
	double		ambient;
	double		wait;
	t_cam		*cam;
	t_list		*cameras;
	t_list		*lights;
	t_list		*objects;
	t_list		*materials;
	t_list		*patterns;
	int			all_on;
	int			source_id;
	int			thread_id;
}				t_scene;

typedef struct	s_event
{
	void		*mlx;
	void		*win;
	void		*menu_win;
	t_img		img;
	t_img		menu_img;
	t_menu		menu;
	t_scene		scene;
	t_source	*src;
	int			mouse_hold;
	int			x_0;
	int			y_0;
	int			t_select;
	int			id_select;
	int			instructions;
	int			redraw;
}				t_event;

void			error(int err);
void			s_error(const char *s);
void			set_scene(int fd, t_scene *scene);
void			set_object(t_scene *scene, int id, int fd, t_object *obj);
void			update_vector(t_3v *vector, char *line);
void			get_doubles_from_line(double *vector, char *line, int size);
void			add_light(t_scene *scene, int fd);
void			set_render(t_scene *scene, int fd);
void			set_camera(t_scene *scene, int fd);
double			get_t_triangle(t_fixed_v f, t_3v dir, int alt, t_object *obj);
double			get_t_cylinder(t_fixed_v f, t_3v dir, int alt, t_object *obj);
double			get_t_plane(t_fixed_v f, t_3v dir, int alt, t_object *obj);
double			get_t_sphere(t_fixed_v f, t_3v dir, int alt, t_object *obj);
double			get_t_cone(t_fixed_v f, t_3v dir, int alt, t_object *obj);
double			get_t_mesh(t_fixed_v f, t_3v dir, int alt);
void			*set_t_values(void *arg);
void			*get_light_value(void *arg);
void			*init_light_values(void *arg);
void			turn_on_lights(t_event *event);
void			*set_light_per_pixel(void *event);
t_event			get_event(t_scene scene);
t_source		*get_source(int id, t_list *lst);
t_3v			rotate_v(t_3v dir, t_3v rotation);
t_3v			rotate_v_inv(t_3v dir, t_3v rotation);
t_3v			get_point(t_3v origin, t_3v coor, double s_value);
t_3v			get_reflection_vector(t_3v n, t_3v dir_a);
t_3v			get_normal(t_object *obj, t_3v point);
t_3v			get_source_origin(t_object *obj, int id);
t_3v			get_r_source(t_object *obj, t_cam *cam);
void			change_dir(t_3v *dir, t_3v rotation);
void			rotate_object(t_object *object, t_scene *scene, int cam_only);
void			init_loop(t_event *event);
int				key_pressed(int key, t_event *param);
int				get_color(t_3v c);
t_3v			get_rel_origin(t_3v origin, t_object *obj);
t_3v			normalize(t_3v v);
t_intensity		get_intensity(t_p_info *pi, t_3v dir, t_cam cam, int src_id);
int				fill_square(t_img *img, int index, int size, int color);
void			init_image(void *mlx, int width_scr, int height_scr,
		t_img *img);
void			anti_aliasing(t_event *event);
int				drag_scene(int x, int y, t_event *event);
int				mouse_click(int button, int x, int y, t_event *event);
int				toggle_button(int button, int x, int y, t_event *event);
void			set_drag_angle(t_event *event, int x, int y);
void			set_move(t_event *event, int move);
int				key_hold(int key, t_event *event);
void			set_fixed_values(t_scene *scene);
void			set_value_refl(t_3v point, t_object *o, int *var);
void			set_drag_angle(t_event *event, int x, int y);
char			*get_vector_string(t_3v v, int precision);
t_material		get_object_material(t_object o, t_3v p, t_scene scene);
t_material		polka_dot_it(t_object o, t_3v angle, t_3v dif);
t_material		stripe_it(t_object o, t_3v angle, t_3v dif);
void			change_camera(t_event *event);
void			set_values_material(t_material *m, char *s, char *value);
void			set_material(t_scene *scene);
void			set_pattern(t_scene *scene);
void			set_point_list(t_pattern *p);
void			init_def_object(t_object *obj, int id, t_scene *scene,
		t_object *param);
void			create_threads(t_event *event, void *(*f)(void*));
void			refraction(t_p_info	*pi, t_3v *dir, t_pixel *p, t_scene scene);
void			get_reflections(t_pixel *p, t_scene scene, t_3v dir);
double			within_limits(t_object *obj, t_3v point, double b);
void			set_finish(t_scene *scene);
void			set_fixed_value(t_3v origin, t_object *o, t_fixed_v *f);
void			set_menu(t_event *event);
void			set_object_menu(t_event *event);
void			set_strings(t_menu *menu);
void			init_menu(t_event *event);
void			change_menu(t_event *event);
void			set_cam_menu(t_event *event);
void			set_light_menu(t_event *event);
double			light_reaches(t_3v d, t_scene *scene, t_source *src);
double			get_influence_specular(t_pixel *p, int i);
void			change_material(t_scene *scene, t_object *obj, int value,
		int mat);
void			set_object_type(char *s, t_object *obj);
double			get_nearest_intersection(double a, double b, double d, int alt);
void			set_var(int *var, int amount_p, int cam_id, int thread_id);
void			check_for_composite(t_scene *scene, t_object *obj);
t_3v			**read_obj_file(char *path, int verbose);
void			get_int_from_line(int *v, char *line, int size);
void			update_vector_xyz(t_3v *vector, char *line);
void			create_mesh(t_list **objects, t_object *parent, t_scene *scene);
t_material		filter_it(t_object o, int id);
void			save_image_file(t_event *event);
void			read_image_file(t_event *event);
int				file_exists(char *name);
int				file_exists_save(char *name);

#endif
