#include "rtv1.h"

static void	set_background(t_event *event)
{
	int		i;
	int		j;
	t_menu	*menu;

	i = 0;
	menu = &(event->menu);
	while (i < menu->height)
	{
		j = 0;
		while (j < menu->width)
		{
			if (i > menu->bar_top && i < menu->height - menu->bar_bottom
					&& j > SUB_MARGIN && j < menu->width - SUB_MARGIN)
				((int *)(menu->img)->img_arr)
					[j + menu->width * i] = PRIMARY_LIGHT;
			else
				((int *)(menu->img)->img_arr)
					[j + menu->width * i] = PRIMARY_COLOR;
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(event->mlx, event->win,
		(menu->img)->img_ptr, menu->x, menu->y);
}

static void	print_instructions(t_event *event)
{
	int	i;
	int	y;
	t_menu	*menu;

	i = 0;
	menu = &(event->menu);
	mlx_string_put(event->mlx, event->win, menu->x + MENU_MARGIN,
			menu->y + MENU_MARGIN, TEXT_DARK, "INSTRUCTIONS");
	y = menu->bar_top + SUB_MARGIN;
	while (i < menu->amount_instructions)
	{
		mlx_string_put(event->mlx, event->win, menu->x + MENU_MARGIN,
			y, TEXT_DARK, menu->man[i]);
		i++;
		y += MENU_LINE;
	}
	menu->now_showing = 1;
}

void	fill_menu(t_event *event)
{
	t_menu	*menu;

	set_background(event);
	menu = &(event->menu);
	if (menu->now_showing == 0)
		print_instructions(event);
	else
	{
		mlx_string_put(event->mlx, event->win, menu->x + MENU_MARGIN,
			menu->y + MENU_MARGIN, TEXT_DARK, event->scene_name);
		mlx_string_put(event->mlx, event->win, menu->x + MENU_MARGIN,
			   	menu->height - menu->bar_bottom + MENU_MARGIN,
				ALERT_COLOR, "Press I to toggle instructions");
		menu->now_showing = 0;
	}
}

void	init_menu(t_event *event)
{
	t_menu	*menu;

	menu = &(event->menu);
	menu->x = (event->scene).width;
	menu->y = 0;
	menu->width = MENU_WIDTH;
	menu->height = (event->scene).height;
	menu->bar_top = BAR_TOP_HEIGHT;
	menu->bar_bottom = MENU_MARGIN + MENU_LINE;
	menu->amount_instructions = AMOUNT_INSTRUCTIONS;
	menu->img = init_image(event->mlx, menu->width, menu->height);
	set_instructions(menu);
	set_background(event);
	menu->now_showing = 1;
}
