# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yjama <yjama@student.21-school.ru>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/18 09:36:26 by yjama             #+#    #+#              #
#    Updated: 2021/04/27 11:51:25 by yjama            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

SRCS =	./srcs/main.c\
		./srcs/main_utils.c\
		./srcs/color.c\
		./srcs/ft_args_fd.c\
		./srcs/ft_events_keys.c\
		./srcs/ft_free_all.c\
		./srcs/ft_rays.c\
		./srcs/ft_rays_utils.c\
		./srcs/ft_rays_3D.c\
		./srcs/ft_sprites.c\
		./srcs/ft_sprites_put.c\
		./srcs/ft_sprites_utils.c\
		./srcs/ft_sprites_put_utils.c\
		./srcs/ft_sprites_put_utils_norm.c\
		./srcs/map_char_check.c\
		./srcs/map_minimap.c\
		./srcs/map_spaces_check.c\
		./srcs/parsing.c\
		./srcs/parsing_utils.c\
		./srcs/player_move.c\
		./srcs/player.c\
		./srcs/window_size.c\
		./srcs/window_size_utils.c\
		./srcs/screenshoot.c\
		./srcs/list_utils.c\
		./srcs/list_utils_norm.c\

OBJS			= $(SRCS:.c=.o)

CC				= gcc
RM				= rm -f
CFLAGS			= -O3 -Wall -Wextra -Werror -I.
LIBS			= -L. -lmlx -framework OpenGL -framework AppKit
MLX				= libmlx.a
LIBFT			= libft.a

NAME			= cub3D

all:			$(NAME)

$(NAME):		$(LIBFT) $(MLX) $(OBJS)
				gcc ${CFLAGS} -o ${NAME} ${OBJS} ${LIBS} ${LIBFT}

$(LIBFT):
				@$(MAKE) -C libft_c3D
				@mv libft_c3D/$(LIBFT) .

$(MLX):
				@$(MAKE) -C minilibx
				@mv minilibx/$(MLX) .

clean:
				@$(MAKE) -C minilibx clean
				@$(MAKE) -C libft_c3D clean
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME) $(MLX) $(LIBFT)

re:				fclean $(NAME)

.PHONY:			all clean fclean re
