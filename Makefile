# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpauw <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/06 17:41:17 by mpauw             #+#    #+#              #
#    Updated: 2018/06/15 15:46:33 by mpauw            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RTv1 
INCLUDES = rtv1.h keys.h mlx_constants.h
SRCS = 	rtv1.c\
		set_scene.c\
		set_object.c\
		set_camera.c\
		set_render.c\
		set_material.c\
		set_pattern.c\
		set_light.c\
		set_point_list.c\
		set_fixed_values.c\
		set_t_values.c\
		get_event.c\
		set_light_per_pixel.c\
		get_intensity.c\
		get_t_value.c\
		get_object_material.c\
		tools_parse.c\
		tools_vector.c\
		tools_color.c\
		tools_rotate.c\
		tools_anti_a.c\
		tools_grain.c\
		tools_limits.c\
		event_key.c\
		event_mouse.c\
		control_light.c\
		control_camera.c\
		polka_dot_it.c
OBJ = $(SRCS:%.c=%.o)
LFTDIR = libft/
#
# Use other $LMLXDIR by (un)commenting the following two lines 
# if the project does not compile. 
# 
LMLXDIR = minilibx_macos/
#LMLXDIR = mlx_macbook/
LIBFT = libft.a
LIBMLX = libmlx.a
FT = ft
MLX = mlx
MAKE = make
FLAGS = -Wall -Wextra -Werror 
# Add before -ggdb to find out where segfault is
SEGFAULT = -fsanitize=address
VALGRIND = -g3
FRAMEWORK = -framework OpenGL -framework AppKit

all : $(NAME)

$(NAME): $(OBJ) $(LFTDIR)$(LIBFT) $(LMLXDIR)$(LIBMLX)
	-@gcc $(FLAGS) -o $(NAME) $(SEGFAULT) -ggdb $(OBJ) -I$(LFTDIR) -L$(LFTDIR) -l$(FT) \
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
