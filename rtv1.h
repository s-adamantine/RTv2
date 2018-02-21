/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 11:08:02 by mpauw             #+#    #+#             */
/*   Updated: 2018/02/21 17:05:42 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# define IMG_W 1080
# define IMG_H 800
# define MAX_S_VALUE 50000
# define BG_COLOR 0x20
# define RADIUS 10.0
# define ALBEDO 0.25
# define CAM_X 2000
# define CAM_Y 0
# define CAM_Z 0
# define DEG 57.2958

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
	int			*inside_obj;
	t_intensity	intensity;
	t_3v		origin;
	t_3v		*origin_o;
	t_3v		color;
	t_3v		rotation;
}				t_source;

typedef struct	s_cam
{
	int			id;
	int			*inside_obj;
	t_3v		origin;
	t_3v		*origin_o;
	t_3v		rotation;
}				t_cam;

typedef struct	s_object
{
	int			id;
	int			type;
	double		radius;
	double		diffuse;
	double		ambient;
	double		specular;
	double		shininess;
	double		(*f)();
	t_3v		color;
	t_3v		origin;
	t_3v		rotation;
	t_3v		normal;
	t_list		*rel_lights;
	t_cam		rel_cam;
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
	int			amount_d;
	int			grain;
	int			anti_a;
	int			refl;
	double		avg_d;
	double		ambient;
	double		wait;
	t_cam		camera;
	t_list		*lights;
	t_list		*objects;
	t_source	cur_src;
}				t_scene;

typedef struct	s_event
{
	void		*mlx;
	void		*win;
	t_img		*img;
	t_scene		scene;
	t_pixel		*p_array;
	char		*scene_name;
	int			cur_grain;
	int			mouse_hold;
	int			x_0;
	int			y_0;
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
double			get_s_cylinder(t_object *s, t_3v dir, t_3v r_origin);
double			get_s_plane(t_object *s, t_3v dir, t_3v src_o);
double			get_s_sphere(t_object *s, t_3v dir, t_3v src_o);
double			get_s_cone(t_object *s, t_3v dir, t_3v src_c);
void			*get_s_values(void *arg);
void			*get_light_value(void *arg);
void			*init_light_values(void *arg);
void			*turn_on_all(void *arg);
void			*light_inside(void *arg);
void			set_light_per_pixel(t_event *event, t_source src);
t_event			init_window(t_scene scene);
t_source		*get_source(int id, t_list *lst);
t_3v			get_dir(t_3v dir, t_3v rotation);
t_3v			get_point(t_cam origin, t_3v coor, double s_value);
t_3v			get_reflection_vector(t_3v n, t_3v dir_a);
t_3v			get_normal(t_object *obj, t_3v point);
t_3v			get_source_origin(t_object *obj, int id);
void			change_dir(t_3v *dir, t_3v rotation);
void			rotate_object(t_object *object, t_scene *scene, int cam_only);
void			init_loop(t_event *event);
int				key_pressed(int key, t_event *param);
int				get_color(t_3v c);
void			update_color(t_intensity intensity, t_3v *color,
		t_object *o, t_source l);
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

#endif
