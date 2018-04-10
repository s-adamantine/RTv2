/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 11:08:02 by mpauw             #+#    #+#             */
/*   Updated: 2018/04/10 18:08:16 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# define MAX_S_VALUE 50000
# define DEG 57.2958
# define MENU_WIDTH 500

# define AMOUNT_INSTRUCTIONS 7
# define AMOUNT_INFO 6

# define AMOUNT_BUTTONS 5
# define AMOUNT_BUTTON_ROWS 2
# define AMT_B_PER_ROW 3
# define MENU_MARGIN 20
# define SUB_MARGIN 10
# define INFO_MARGIN 130
# define SUB_SUB_MARGIN 5
# define BAR_TOP_HEIGHT 60
# define OBJ_SUB_MENU_HEIGHT 60
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
}				t_source;

typedef struct	s_cam
{
	int			id;
	int			*inside_obj;
	t_3v		origin;
	t_3v		rotation;
}				t_cam;

typedef struct	s_object
{
	int			id;
	int			type;
	double		radius;
	double		radius_sq;
	double		diffuse;
	double		ambient;
	double		specular;
	double		shininess;
	double		(*f)();
	t_3v		color;
	t_3v		origin;
	t_3v		dir;
	t_3v		rotation;
	double		*fixed_value;
	double		*fixed_value_2;
	t_3v		*fixed_vec;
	t_3v		*dif_c;
}				t_object;

typedef struct	s_pixel
{
	int			status;
	t_3v		coor;
	t_3v		*normal;
	double		*s_value;
	t_object	**vis_obj;
	t_3v		*point;
	t_3v		*c_per_src;
	t_3v		color;
}				t_pixel;

typedef struct	s_scene
{
	char		*name;
	int			width;
	int			height;
	int			amount_obj;
	int			amount_light;
	int			cam_set;
	int			grain;
	int			anti_a;
	int			refl;
	double		ambient;
	double		wait;
	double		max_value;
	t_cam		camera;
	t_list		*lights;
	t_list		*objects;
	double		*f_value;
	double		*f_value_2;
	t_3v		*f_vec;
	int			all_on;
}				t_scene;

typedef struct	s_menu_p
{
	int			x;
	int			y;
	int			button;
	int			id;
	int			color;
}				t_menu_p;

typedef struct	s_strings
{
	char		**man;
	char		**types;
	char		**info;
	char		**buttons;
}				t_strings;

typedef struct	s_button
{
	int			x;
	int			y;
	int			width;
	int			height;
	int			color;
	int			id;
	char		*text;
	t_img		*img;
}				t_button;

typedef struct	s_sub_m
{
	int			x;
	int			y;
	int			width;
	int			height;
	int			color;
	int			id;
	int			sub_tab;
	int			position;
	int			tab_amount;
	int			per_tab;
	t_img		*img;
}				t_sub_m;

typedef struct	s_menu
{
	int			x;
	int			y;
	int			width;
	int			height;
	int			now_showing;
	int			first;
	int			objects_set;
	int			lights_set;
	int			sub_tab_showing;
	t_img		*img;
	t_menu_p	*p;
	t_strings	strings;
	t_button	*buttons;
	t_sub_m		sub_m;
	t_sub_m		camera;
	t_sub_m		*objects;
	t_sub_m		*lights;
}				t_menu;

typedef struct	s_event
{
	void		*mlx;
	void		*win;
	t_img		*img;
	t_scene		scene;
	t_pixel		*p_array;
	char		*scene_name;
	t_menu		menu;
	int			cur_grain;
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
double			get_s_cylinder(t_object *s, t_3v dir, int i);
double			get_s_plane(t_object *s, t_3v dir, int i);
double			get_s_sphere(t_object *s, t_3v dir, int i);
double			get_s_cone(t_object *s, t_3v dir, int i);
void			*get_s_values(void *arg);
void			*get_light_value(void *arg);
void			*init_light_values(void *arg);
void			turn_on_lights(t_event *event);
void			*light_inside(void *arg);
void			set_light_per_pixel(t_event *event, t_source src);
t_event			init_window(t_scene scene);
t_source		*get_source(int id, t_list *lst);
t_3v			get_dir(t_3v dir, t_3v rotation);
t_3v			get_rev_dir(t_3v dir, t_3v rotation);
t_3v			get_point(t_cam origin, t_3v coor, double s_value);
t_3v			get_reflection_vector(t_3v n, t_3v dir_a);
t_3v			get_normal(t_object *obj, t_3v point);
t_3v			get_source_origin(t_object *obj, int id);
t_3v			get_r_source(t_object *obj, t_cam *cam);
void			change_dir(t_3v *dir, t_3v rotation);
void			rotate_object(t_object *object, t_scene *scene, int cam_only);
void			init_loop(t_event *event);
int				key_pressed(int key, t_event *param);
int				get_color(t_3v c);
void			update_color(t_intensity intensity, t_3v *color,
		t_object *o, t_source l);
t_3v			get_rel_origin(t_3v origin, t_object *obj);
t_3v			normalize(t_3v v);
t_intensity		get_intensity(t_pixel *p, int r, t_3v dir, t_cam cam);
int				fill_square(t_img **img, int index, int size, int color);
t_img			*init_image(void *mlx, int width_scr, int height_scr);
void			anti_aliasing(t_event *event);
int				drag_scene(int x, int y, t_event *event);
int				mouse_click(int button, int x, int y, t_event *event);
int				toggle_button(int button, int x, int y, t_event *event);
void			set_drag_angle(t_event *event, int x, int y);
void			set_move(t_event *event, int move);
int				key_hold(int key, t_event *event);
void			set_fixed_values(t_scene *scene);
void			set_value_refl(t_3v point, t_object *o, int r);
void			set_drag_angle(t_event *event, int x, int y);
void			fill_menu(t_event *event);
void			init_menu(t_event *event);
void			set_strings(t_menu *menu);
void			add_sub_menu(t_event *event);
void			add_button(t_event *event, t_button *button);
void			set_sub_menu_pixel(t_menu *menu, t_sub_m *sub_m);
void			add_object_menu(t_event *event);
char			*get_vector_string(t_3v v, int precision);
void			set_sub_tab_number(t_sub_m *parent, t_sub_m *child, int i);

#endif
