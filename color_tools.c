#include "rtv1.h"

void	update_color(t_intensity intensity, t_3v *color,
		t_object *o, t_source l)
{
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

int		get_color(t_3v c)
{
	int	color;
	int	int_value;

	if (c.v[0] > 1)
		c.v[0] = 1;
	else if (c.v[0] < 0)
		c.v[0] = 0;
	if (c.v[1] > 1)
		c.v[1] = 1;
	else if (c.v[1] < 0)
		c.v[1] = 0;
	if (c.v[2] > 1)
		c.v[2] = 1;
	else if (c.v[2] < 0)
		c.v[2] = 0;
	color = c.v[0] * 0xff;
	int_value = c.v[1] * 0xff;
	color += int_value * 0x100;
	int_value = c.v[2] * 0xff;
	color += int_value * 0x10000;
	return (color);
}
