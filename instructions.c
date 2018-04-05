#include "rtv1.h"

void	set_instructions(t_menu *menu)
{
	char	**man;

	if (!(menu->man = (char **)malloc(sizeof(char *) * menu->amount_instructions)))
		error (1);
	man = menu->man;
	man[0] = ft_strdup("- Press ESC to exit.");
	man[1] = ft_strdup("- Press O, L or C to control object");
	man[2] = ft_strdup("    light or camera.");
	man[3] = ft_strdup("- Press number to control with ID.");
	man[4] = ft_strdup("- Press Q to turn on or off a light.");
	man[5] = ft_strdup("- Press I to toggle instructions.");
	man[6] = ft_strdup("More instructions here.");
}
