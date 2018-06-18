/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicola <nicola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 11:08:02 by mpauw             #+#    #+#             */
/*   Updated: 2018/06/18 13:31:30 by nicola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# define MAX_S_VALUE 50000
# define DEG 57.2958
# define MENU_WIDTH 500

# define AMOUNT_INSTRUCTIONS 7
# define AMOUNT_INFO 6

# define AMT_SUB_M 5
# define AMT_BUT 5
# define AMT_B_ROW 2
# define AMT_B_P_ROW 3
# define MENU_MARGIN 20
# define SUB_MARGIN 10
# define INFO_MARGIN 130
# define SUB_SUB_MARGIN 5
# define BAR_TOP_HEIGHT 60
# define OBJ_SUB_M_HEIGHT 125
# define DEF_BUTTON_HEIGHT 30
# define TAB_BUTTON_WIDTH 20
# define SUB_MENU_Y (BAR_TOP_HEIGHT + 2 * DEF_BUTTON_HEIGHT + SUB_MARGIN)
# define MENU_LINE 15
# define TEXT_LIGHT 0xffffff
# define TEXT_DARK 0x000000
# define ALERT_COLOR 0xff3f80
# define PRIMARY_COLOR 0x66bb6a
# define PRIMARY_DARK 0x338a3e
# define PRIMARY_LIGHT 0x98ee99

# define MAIN_MENU 0x00
# define OBJECT_MENU 0x01
# define LIGHT_MENU 0x02
# define CAM_MENU 0x03
# define MAN_MENU 0x04
# define SUB_MENU 0x06
# define SUB_SUB_MENU 0x07
# define MAIN_BUTTON 0x10
# define OBJECT_BUTTON 0x11
# define LIGHT_BUTTON 0x12
# define CAM_BUTTON 0x13
# define MAN_BUTTON 0x14
# define SUB_MENU_BUTTON 0x15
# define TAB_BUTTON 0x20

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
	int			width;
	int			height;
	int			bpp;
	int			size_line;
	int			size_line_int;
	int			endian;
	int			id;
}				t_img;

typedef struct	s_intensity
{
	double		spec;
	double		diff;
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
}				t_source;

typedef struct	s_fixed_v
{
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
}				t_fixed_v;

typedef struct	s_material
{
	int			id;
	int			pattern;
	t_3v		color;
	double		diffuse;
	double		ambient;
	double		specular;
	double		shininess;
	double		transparent;
}				t_material;

typedef struct	s_pattern
{
	int			id;
	int			type;
	double		size;
	int			distance;
	int			amount_points;
	t_3v		*points_arr;
	int			os_1;
	int			os_2;
}				t_pattern;

typedef struct	s_object
{
	int			id;
	int			type;
	int			from_inside;
	t_material	m;
	t_material	m2;
	t_pattern	pattern;
	double		radius;
	double		(*f)();
	double		axis_rotation;
	double		params_val;
	t_3v		params;
	t_3v		origin;
	t_3v		origin_2;
	t_3v		origin_3;
	t_3v		rotation;
	t_fixed_v	**fixed_c;
	t_fixed_v	**fixed_s;
}				t_object;

typedef struct	s_p_info
{
	t_3v		normal;
	double		s_value;
	t_object	*vis_obj;
	t_material	obj_m;
	t_3v		point;
	int			type;
	int			is_set;
}				t_p_info;

typedef struct	s_pixel
{
	int			status;
	int			amount_p;
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
	int			refl;
	double		ambient;
	double		wait;
	t_cam		*cam;
	t_list		*cameras;
	t_list		*lights;
	t_list		*objects;
	t_list		*materials;
	t_list		*patterns;
	int			all_on;
}				t_scene;

typedef struct	s_event
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_scene		scene;
	int			mouse_hold;
	int			x_0;
	int			y_0;
	int			t_select;
	int			id_select;
	int			redraw;
}				t_event;

void			error(int err);
void			s_error(const char *s);
void			set_scene(int fd, t_scene *scene);
void			set_object(t_list **objects, t_scene *scene, int id, int fd);
void			update_vector(t_3v *vector, char *line);
void			get_doubles_from_line(double *vector, char *line, int size);
void			add_light(t_scene *scene, int fd);
void			set_render(t_scene *scene, int fd);
void			set_camera(t_scene *scene, int fd);
double			get_t_cylinder(t_fixed_v f, t_3v dir, int alt);
double			get_t_plane(t_fixed_v f, t_3v dir, int alt);
double			get_t_sphere(t_fixed_v f, t_3v dir, int alt);
double			get_t_cone(t_fixed_v f, t_3v dir, int alt);
double			get_t_quadric(t_fixed_v f, t_3v dir, int alt);
double  		get_t_triangle(t_fixed_v f, t_3v dir);
void			*set_t_values(void *arg);
void			*get_light_value(void *arg);
void			*init_light_values(void *arg);
void			turn_on_lights(t_event *event);
void			light_inside(t_scene *scene);
void			set_light_per_pixel(t_event *event, t_source src);
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
t_3v			entry_division(t_3v v1, t_3v v2);
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
void			set_value_refl(t_3v point, t_object *o, int r, int cam_id);
void			set_drag_angle(t_event *event, int x, int y);
void			init_menu(t_event *event);
void			add_sub_menu(t_event *event);
char			*get_vector_string(t_3v v, int precision);
void			menu_click(int index, t_event *event);
t_material		get_object_material(t_object o, t_3v p);
t_material		polka_dot_it(t_object o, t_3v angle, t_3v dif);
void			change_camera(t_event *event);
void			set_values_material(t_material *m, char *s, char *value);
void			set_material(t_scene *scene);
void			set_pattern(t_scene *scene);
void			set_point_list(t_pattern *p);


// NICOLA
int		scan_obj_file(char *path, int *f_v_n);
int	read_obj_file(char *path);
int	init_faces_vertices( t_3v *vertices, t_3v **faces, int *fac_ver_num);
int		fill_f_v_obj_file(char *path,  t_3v *vertices );
void	get_int_from_line(int *v, char *line, int size);
#endif
