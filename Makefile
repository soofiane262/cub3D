# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/23 16:04:18 by sel-mars          #+#    #+#              #
#    Updated: 2022/08/17 17:57:01 by sel-mars         ###   ########.fr        #
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
			assets/parsing/parsing.c\
			assets/mlx/init_mlx_ptrs.c\
			assets/mlx/init_walls.c\
			assets/mlx/mlx_utils.c\
			assets/mlx/key_hook.c\
			assets/mlx/leave.c\
			assets/render/update.c\
			assets/render/render.c\
			assets/raycast/raycast.c\
			assets/raycast/wall_hit.c

OBJS	=	$(SRCS:%.c=%.o)

%.o:	%.c $(HDFL)
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME):	$(HDFL) $(OBJS)
	@printf "\033[0;33m\n---------------------------------------- \033[0;0m\n\n"
	@printf "\033[1;33m\tMaking \`libft\` library \033[0;0m\n"
	@printf "\033[0;33m\n---------------------------------------- \033[0;0m\n\n"
	make -C libft
	@printf "\033[0;34m\n--------------------------------------------------- \033[0;0m\n\n"
	@printf "\033[1;34m\tSuccessfully made \`libft\` library \033[0;0m\n"
	@printf "\033[0;34m\n--------------------------------------------------- \033[0;0m\n\n"
	@printf "\033[0;33m\n----------------------------------------------------- \033[0;0m\n\n"
	@printf "\033[1;33m\tMaking \`minilibx\` graphical library \033[0;0m\n"
	@printf "\033[0;33m\n----------------------------------------------------- \033[0;0m\n\n"
	make -C mlx
	@printf "\033[0;34m\n---------------------------------------------------------------- \033[0;0m\n\n"
	@printf "\033[1;34m\tSuccessfully made \`minilibx\` graphical library \033[0;0m\n"
	@printf "\033[0;34m\n---------------------------------------------------------------- \033[0;0m\n\n"
	@printf "\033[0;33m\n---------------------------------------------------------------- \033[0;0m\n\n"
	@printf "\033[1;33m\tGathering \`cub3D\` object files into library \033[0;0m\n"
	@printf "\033[0;33m\n---------------------------------------------------------------- \033[0;0m\n\n"
	$(AR) $(LIB) $(OBJS)
	@printf "\033[0;34m\n-------------------------------------------------------- \033[0;0m\n\n"
	@printf "\033[1;34m\tSuccessfully gathered \`cub3D\` library \033[0;0m\n"
	@printf "\033[0;34m\n-------------------------------------------------------- \033[0;0m\n\n"
	@printf "\033[0;33m\n-------------------------------------------------------- \033[0;0m\n\n"
	@printf "\033[1;33m\tCompiling \`cub3D\` binary executable \033[0;0m\n"
	@printf "\033[0;33m\n-------------------------------------------------------- \033[0;0m\n\n"
	$(CC) $(CFLAGS) $(MAIN) -L. -lcub3d -L./libft -lft -L./mlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)
	@printf "\033[0;34m\n-------------------------------------------------------- \033[0;0m\n\n"
	@printf "\033[1;34m\tSuccessfully compiled \`cub3D\` executable \033[0;0m\n"
	@printf "\033[0;34m\n-------------------------------------------------------- \033[0;0m\n\n"
	@printf "\033[1;32m\n\n---------------------------------------------- \033[0;0m\n\n"
	@printf "\033[1;32m\t      Cub3D Game is ready \033[0;0m\n"
	@printf "\033[0;32m\t-- ./cub3D path_to_map_file -- \033[0;0m\n"
	@printf "\033[1;32m\n---------------------------------------------- \033[0;0m\n\n"

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