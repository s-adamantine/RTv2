/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 11:08:02 by mpauw             #+#    #+#             */
/*   Updated: 2018/04/12 19:33:09 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# define MAX_S_VALUE 50000
# define DEG 57.2958
# define MENU_WIDTH 500

# define AMOUNT_INSTRUCTIONS 7
# define AMOUNT_INFO 6

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

typedef struct	s_menu_p
{
	int			x;
	int			y;
	int			button;
	int			id;
	int			type_id;
	int			type;
	int			color;
}				t_menu_p;

typedef struct	s_sub_m
{
	int			y;
	int			x;
	int			width;
	int			height;
	int			color;
	int			color_selected;
	int			id;
	char		**strings;
	t_img		img;
	int			first;
	int			parent_id;
	int			*child_id;
	int			child_count;
	int			showing;
	int			selected;
	int			type;
	int			type_id;
	int			sub_tab;
	int			sub_tab_showing;
	int			position;
	int			tab_amount;
	int			per_tab;
	int			edge_thickness;
	int			edge_color;
}				t_sub_m;

typedef struct	s_menu
{
	t_menu_p	*p;
	t_sub_m		*sub_m;
	int			sub_m_count;
}				t_menu;

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

typedef struct	s_fixed_v
{
	double		val;
	double		val_2;
	double		rad;
	double		rad_sq;
	t_3v		vec;
	t_3v		dif_c;
	t_3v		dir;
}				t_fixed_v;

typedef struct	s_object
{
	int			id;
	int			type;
	double		radius;
	double		diffuse;
	double		ambient;
	double		specular;
	double		shininess;
	double		transparent;
	double		(*f)();
	t_3v		color;
	t_3v		origin;
	t_3v		rotation;
	t_fixed_v	**fixed_c;
	t_fixed_v	**fixed_s;
}				t_object;

typedef struct	s_p_info
{
	t_3v		normal;
	double		s_value;
	t_object	*vis_obj;
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
	t_3v		origin;
	t_3v		rotation;
	t_pixel		*p_array;
	double		*light_vis;
}				t_cam;

typedef struct	s_scene
{
	char		*name;
	int			width;
	int			height;
	int			amount_obj;
	int			amount_light;
	int			amount_fixed;
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
	int			all_on;
}				t_scene;

typedef struct	s_event
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_scene		scene;
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
double			get_s_cylinder(t_fixed_v f, t_3v dir, int alt);
double			get_s_plane(t_fixed_v f, t_3v dir, int alt);
double			get_s_sphere(t_fixed_v f, t_3v dir, int alt);
double			get_s_cone(t_fixed_v f, t_3v dir, int alt);
void			*get_s_values(void *arg);
void			*get_light_value(void *arg);
void			*init_light_values(void *arg);
void			turn_on_lights(t_event *event);
void			light_inside(t_scene *scene);
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
void			set_sub_menu_pixel(t_menu *menu, t_sub_m *sub_m);
void			init_menu(t_event *event);
int				init_sub_menu(t_menu *menu, int parent_id);
void			fill_menu(t_event *event, t_menu *menu);
void			add_object_menu(t_event *event, t_sub_m *parent, t_menu *menu);
void			add_sub_menu(t_event *event);
char			*get_vector_string(t_3v v, int precision);
void			set_sub_tab_number(t_sub_m *parent, t_sub_m *child, int i);
void			menu_click(int index, t_event *event);
void			add_child_id(t_sub_m *parent, t_sub_m *child);
void			change_camera(t_event *event);
t_cam			*get_selected_cam(t_scene *scene, int id);

#endif
