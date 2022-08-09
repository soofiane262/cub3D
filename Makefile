# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/23 16:04:18 by sel-mars          #+#    #+#              #
#    Updated: 2022/08/09 13:00:37 by sel-mars         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3D

HDFL	=	assets/cub3d.h

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror

AR		=	ar rc

LIB		=	libcub3d.a

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

OBJS	=	$(SRCS:%.c=%.o)

$(NAME):	$(HDFL) $(OBJS)
	make -C libft
	make -C mlx
	$(AR) $(LIB) $(OBJS)
	$(CC) $(CFLAGS) $(MAIN) -L. -lcub3d -L./libft -lft -L./mlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

all:	$(NAME)

clean:
	make clean -C libft
	make clean -C mlx
	rm -rf $(OBJS) $(LIB)

fclean:	clean
	make fclean -C libft
	make clean -C mlx
	rm -rf $(NAME)

re:	fclean $(NAME)

.PHONY:	all clean fclean