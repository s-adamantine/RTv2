/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 11:08:02 by mpauw             #+#    #+#             */
/*   Updated: 2018/02/06 16:58:37 by mpauw            ###   ########.fr       */
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
# define CAM_LIGHT_B 1.0
# define CAM_LIGHT_G 1.0
# define CAM_LIGHT_R 1.0

# define SPACE 0x31
# define ESC 0x35

# include "libft.h"
# include "mlx.h"
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <stdio.h>
# include <errno.h>

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
	t_intensity	intensity;
	t_3v		origin;
	t_3v		*origin_o;
	t_3v		rotation;
	t_3v		color;
}				t_source;

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
	t_source	rel_cam;
}				t_object;

typedef struct	s_scene
{
	char		*name;
	int			amount_obj;
	int			amount_light;
	int			cam_set;
	int			width;
	int			height;
	int			amount_d;
	int			grain;
	int			anti_a;
	double		avg_d;
	double		ambient;
	t_source	camera;
	t_list		*lights;
	t_list		*objects;
}				t_scene;

typedef struct	s_event
{
	void		*mlx;
	void		*win;
	t_img		*img;
	char		*scene_name;
	t_scene		scene;
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
double			get_nearest_intersection(double a, double b, double d);
void			raytracer(t_event *event, t_scene *scene, int it);
t_event			init_window(t_scene scene);
t_source		*get_source(int id, t_list *lst);
t_3v			get_dir(t_3v dir, t_3v rotation);
void			change_dir(t_3v *dir, t_3v rotation);
int				get_light_value(t_3v point, t_scene *scene,
		t_list *sources, t_object *obj);
void			rotate_object(t_object *object, t_scene *scene);
void			init_loop(t_event *event);
int				key_pressed(int key, t_event *param);
int				get_color(double blue, double green, double red);
t_intensity		get_intensity(t_3v point, t_object *obj, t_3v dir,
		t_source cam);
int				fill_square(t_img **img, int index, int size, int color);
t_img			*init_image(void *mlx, int width_scr, int height_scr);
void			anti_aliasing(t_event *event);

#endif
