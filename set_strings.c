/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_strings.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 11:35:58 by mpauw             #+#    #+#             */
/*   Updated: 2018/06/26 14:33:36 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	set_info(t_menu *menu)
{
	char	**info;

	if (!(menu->info = (char **)malloc(sizeof(char *) * AMOUNT_INFO)))
		error(1);
	info = menu->info;
	info[0] = ft_strdup("ID: ");
	info[1] = ft_strdup("Origin: ");
	info[2] = ft_strdup("Rotation: ");
	info[3] = ft_strdup("Radius: ");
	info[4] = ft_strdup("Color: ");
	info[5] = ft_strdup("Reflections: ");
	info[6] = ft_strdup("Diffuse: ");
	info[7] = ft_strdup("Specular: ");
}

static void	set_types(t_menu *menu)
{
	char	**types;

	if (!(menu->types = (char **)malloc(sizeof(char *) * 10)))
		error(1);
	types = menu->types;
	types[0] = ft_strdup("Plane");
	types[1] = ft_strdup("Sphere");
	types[2] = ft_strdup("Cylinder");
	types[3] = ft_strdup("Cone");
	types[4] = ft_strdup("None");
	types[5] = ft_strdup("Triangle");
	types[6] = ft_strdup("Mesh");
	types[7] = ft_strdup("Composite");
	types[8] = ft_strdup("Camera");
	types[9] = ft_strdup("Light");
}

static void	set_instructions(t_menu *menu)
{
	char	**man;

	if (!(menu->man = (char **)malloc(sizeof(char *) *
					AMOUNT_INSTRUCTIONS)))
		error(1);
	man = menu->man;
	man[0] = ft_strdup("- Press ESC to exit.");
	man[1] = ft_strdup("- Press O, L or C to see object,");
	man[2] = ft_strdup("    light, or camera menu.");
	man[3] = ft_strdup("- Press number to control with ID.");
	man[4] = ft_strdup("- Press Q to turn on or off a light.");
	man[5] = ft_strdup("- Press I to toggle instructions.");
	man[6] = ft_strdup("- + or - to increase/decrease light.");
}

void		set_strings(t_menu *menu)
{
	set_instructions(menu);
	set_types(menu);
	set_info(menu);
}
