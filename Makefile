# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/23 16:04:18 by sel-mars          #+#    #+#              #
#    Updated: 2022/08/04 18:00:58 by sel-mars         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3D

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror

MAIN	=	assets/main.c

SRCS	=	gnl/get_next_line.c gnl/get_next_line_utils.c\
			assets/general/general_utils.c assets/cub3d.c\
			assets/parsing/parsing.c assets/parsing/check_map.c\
			assets/parsing/read_map.c\
			assets/hooks/hook.c\
			assets/2d/2d_map.c\
			assets/2d/mini_map.c\
			assets/3d/3d.c\
			assets/raycast/raycast.c

HDFL	=	assets/cub3d.h

$(NAME):	$(SRCS) $(HDFL)
	@make -C libft
	@make -C mlx
	@$(CC) $(CFLAGS) $(MAIN) $(SRCS) -I $(HDFL) -L./libft -lft -L./mlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

all: $(NAME)

clean:
	@make clean -C libft
	@make clean -C mlx

fclean:
	@make fclean -C libft
	@make clean -C mlx
	@rm -rf $(NAME)

.PHONY:	all clean fclean