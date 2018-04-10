/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_strings.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 11:35:58 by mpauw             #+#    #+#             */
/*   Updated: 2018/04/10 13:31:03 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	set_buttons(t_menu *menu)
{
	char	**buttons;

	if (!((menu->strings).buttons = (char **)malloc(sizeof(char *) * 5)))
		error (1);
	buttons = (menu->strings).buttons;
	buttons[0] = ft_strdup("Main");
	buttons[1] = ft_strdup("Objects");
	buttons[2] = ft_strdup("Lights");
	buttons[3] = ft_strdup("Camera");
	buttons[4] = ft_strdup("Manual");
}

static void	set_info(t_menu *menu)
{
	char	**info;

	if (!((menu->strings).info = (char **)malloc(sizeof(char *) * 6)))
		error (1);
	info = (menu->strings).info;
	info[0] = ft_strdup("Origin: ");
	info[1] = ft_strdup("Rotation: ");
	info[2] = ft_strdup("Radius: ");
	info[3] = ft_strdup("Color: ");
	info[4] = ft_strdup("ID: ");
	info[5] = ft_strdup("Reflections: ");
}

static void	set_types(t_menu *menu)
{
	char	**types;

	if (!((menu->strings).types = (char **)malloc(sizeof(char *) * 6)))
		error (1);
	types = (menu->strings).types;
	types[0] = ft_strdup("Plane");
	types[1] = ft_strdup("Sphere");
	types[2] = ft_strdup("Cylinder");
	types[3] = ft_strdup("Cone");
	types[4] = ft_strdup("Camera");
	types[5] = ft_strdup("Light");
}

static void	set_instructions(t_menu *menu)
{
	char	**man;

	if (!((menu->strings).man = (char **)malloc(sizeof(char *) *
					AMOUNT_INSTRUCTIONS)))
		error (1);
	man = (menu->strings).man;
	man[0] = ft_strdup("- Press ESC to exit.");
	man[1] = ft_strdup("- Press O, L or C to control object");
	man[2] = ft_strdup("    light or camera.");
	man[3] = ft_strdup("- Press number to control with ID.");
	man[4] = ft_strdup("- Press Q to turn on or off a light.");
	man[5] = ft_strdup("- Press I to toggle instructions.");
	man[6] = ft_strdup("More instructions here.");
}

void	set_strings(t_menu *menu)
{
	set_instructions(menu);
	set_types(menu);
	set_info(menu);
	set_buttons(menu);
}
