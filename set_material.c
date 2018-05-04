#include "rtv1.h"

static void	init_def_material(t_material *m, int id)
{
	m->color = ft_init_3v(1.0, 1.0, 0.0);
	m->id = id;
	m->diffuse = 0.2;
	m->ambient = 0.1;
	m->specular = 0.0;
	m->shininess = 0;
	m->transparent = 0.0;
}

static void	set_values_material_plus(t_material *m, char *s, char *value)
{
	double	*tmp;

	if (ft_strncmp(s, "transparent", 11) == 0)
		m->transparent = ft_atod(value);
	else if (ft_strncmp(s, "reflection", 10) == 0)
	{
		if (!(tmp = (double *)malloc(4 * sizeof(double))))
			error(0);
		get_doubles_from_line(tmp, value, 4);
		m->ambient = tmp[0];
		m->diffuse = tmp[1];
		m->specular = tmp[2];
		m->shininess = tmp[3];
		free(tmp);
	}
}

void		set_values_material(t_material *m, char *s, char *value)
{
	if (ft_strncmp(s, "color", 5) == 0)
		update_vector(&(m->color), value);
	else if (ft_strncmp(s, "id", 2) == 0)
		m->id = ft_atoi(value);
	else if (ft_strncmp(s, "transparent", 11) == 0
			|| ft_strncmp(s, "reflection", 10) == 0)
		set_values_material_plus(m, s,  value);
}

static void	add_material(t_scene *scene, int fd)
{
	char		*line;
	char		*s;
	char		*value;
	t_material	m;
	int			gnl;

	init_def_material(&m, scene->amount_material);
	while ((gnl = get_next_line(fd, &line)) == 1)
	{
		if (*(line) == '}')
			break ;
		if (ft_isalpha(*line) || !(s = ft_brace_content(line, '{', '}')))
			error(0);
		if (!(value = ft_brace_content(s, '{', '}')))
			error(0);
		set_values_material(&m, s, value);
		free(line);
		free(s);
		free(value);
	}
	if (gnl < 0)
		error(0);
	free(line);
	(scene->amount_material)++;
	ft_lstaddnewr(&(scene->materials), &m, sizeof(m));
}

void		set_material(t_scene *scene)
{
	int			fd;
	t_material	m;
	char		*line;
	int			gnl;

	init_def_material(&m, 0);
	scene->amount_material = 1;
	ft_lstaddnewr(&(scene->materials), &m, sizeof(m));
	if ((fd = open("materials/materials", O_RDONLY)) == -1)
		return ;
	while ((gnl = get_next_line(fd, &line)) == 1)
	{
		if (ft_strncmp(line, "material {", 8) == 0)
			add_material(scene, fd);
		free(line);
	}
	if (gnl < 0)
		error(0);
	free(line);
}
