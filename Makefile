# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/23 16:04:18 by sel-mars          #+#    #+#              #
#    Updated: 2022/07/29 17:13:03 by sel-mars         ###   ########.fr        #
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
			assets/2d/2d_map.c\
			assets/hooks/hook.c\
			assets/raycast/raycast.c

HDFL	=	assets/cub3d.h

$(NAME):	$(SRCS) $(HDFL)
	@make -C libft
	@$(CC) $(CFLAGS) $(MAIN) $(SRCS) -I $(HDFL) -L./libft -lft -lmlx -framework OpenGL -framework AppKit -o $(NAME)

all: $(NAME)

clean:
	@make clean -C libft

fclean:
	@make fclean -C libft
	@rm -rf $(NAME)

.PHONY:	all clean fclean