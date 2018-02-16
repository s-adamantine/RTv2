# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpauw <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/06 17:41:17 by mpauw             #+#    #+#              #
#    Updated: 2018/02/08 15:05:11 by mpauw            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RTv1 
FLAGS = -Wall -Wextra -Werror 
INCLUDES = rtv1.h keys.h mlx_constants.h
SRCS = 	rtv1.c\
		set_scene.c\
		set_object.c\
		set_camera.c\
		set_render.c\
		rotate_object.c\
		add_light.c\
		get_dir.c\
		get_source.c\
		get_intensity.c\
		tools.c\
		color_tools.c\
		s_functions.c\
		light_per_light.c\
		get_s_values.c\
		window_init.c\
		key_control.c\
		anti_aliasing.c\
		fill_square.c\
		mouse_event.c\
		calculate_movement.c\
		get_light_value.c
OBJ = $(SRCS:%.c=%.o)
LFTDIR = libft/
#
# Use other $LMLXDIR by (un)commenting the following two lines 
# if the project does not compile. 
# 
#LMLXDIR = minilibx_macos/
LMLXDIR = mlx_macbook/
LIBFT = libft.a
LIBMLX = libmlx.a
FT = ft
MLX = mlx
MAKE = make
FRAMEWORK = -framework OpenGL -framework AppKit

all : $(NAME)

$(NAME): $(OBJ) $(LFTDIR)$(LIBFT) $(LMLXDIR)$(LIBMLX)
	-@gcc $(FLAGS) -o $(NAME) -ggdb $(OBJ) -I$(LFTDIR) -L$(LFTDIR) -l$(FT) \
	 -I$(LMLXDIR) -L$(LMLXDIR) -l$(MLX) \
	 $(FRAMEWORK)
	-@echo "RTv1 Ready"

%.o: %.c $(INCLUDES)
	-@gcc $(FLAGS) -I$(LFTDIR) -I$(LMLXDIR) -c $(SRCS)

$(LFTDIR)$(LIBFT):
	$(MAKE) -C $(LFTDIR) $(LIBFT)

$(LMLXDIR)$(LIBMLX):
	$(MAKE) -C $(LMLXDIR) $(LIBMLX)

clean:
	-@/bin/rm -f $(OBJ)
#	-@$(MAKE) -C $(LFTDIR) clean
#	-@$(MAKE) -C $(LMLXDIR) clean

fclean: clean
	-@/bin/rm -f $(NAME)
#	-@$(MAKE) -C $(LFTDIR) fclean

re: fclean all
