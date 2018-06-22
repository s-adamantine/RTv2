/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_it.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadamant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 13:04:45 by sadamant          #+#    #+#             */
/*   Updated: 2018/06/22 13:04:52 by sadamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_material  red_filter_it(t_object o)
{
    o.m.color.v[0] = 0.0;
    o.m.color.v[1] = 0.0;
    return (o.m);
}

static t_material  blue_filter_it(t_object o)
{
    o.m.color.v[1] = 0.0;
    o.m.color.v[2] = 0.0;
    return (o.m);
}

static t_material  green_filter_it(t_object o)
{
    o.m.color.v[0] = 0.0;
    o.m.color.v[2] = 0.0;
    return (o.m);
}

t_material  filter_it(t_object o, int id)
{
    if (id == 1)
        return (red_filter_it(o));
    else if (id == 2)
        return (green_filter_it(o));
    else if (id == 3)
        return (blue_filter_it(o));
    return (o.m);
}
