/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fixed_values_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 18:33:38 by mpauw             #+#    #+#             */
/*   Updated: 2018/06/25 12:57:08 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** The fixed values are values that are specific for every object, relative to
** a camera, light source or reflection/transparent point. Instead of
** calculating them at every pixel, we fix them for every object.
*/

static void	set_fixed_value_2(t_3v origin, t_object *o, t_fixed_v *f)
{
	f->vec = ft_cross_product(ft_3v_subtract(o->origin_2, o->origin),
		ft_3v_subtract(o->origin_3, o->origin)); //the normal
	f->vec = normalize(f->vec);
	f->vec2 = origin;
	f->val = ft_3v_dot_product(f->vec, f->dif_c);
	f->vertex0 = o->origin;
	f->vertex1 = o->origin_2;
	f->vertex2 = o->origin_3;
}

void		set_fixed_value(t_3v origin, t_object *o, t_fixed_v *f)
{
	f->dir = rotate_v(ft_init_3v(0.0, 0.0, 1.0), o->rotation);
	o->dir = f->dir;
	f->rad = o->radius;
	f->rad_sq = o->radius * o->radius;
	f->dif_c = ft_3v_subtract(origin, o->origin);
	f->origin = origin;
	if (o->type == 0)
		f->val = ft_3v_dot_product(f->dir, f->dif_c);
	else if (o->type == 1)
		f->val = ft_3v_dot_product(f->dif_c, f->dif_c);
	else if (o->type == 2 || o->type == 3)
	{
		f->vec = ft_3v_subtract(f->dif_c, ft_3v_scalar(f->dir,
					ft_3v_dot_product(f->dif_c, f->dir)));
		f->val = ft_3v_dot_product(f->vec, f->vec);
	}
	if (o->type == 3)
		f->val_2 = ft_3v_dot_product(f->dif_c, f->dir);
	if (o->type == 5)
		set_fixed_value_2(origin, o, f);
}
