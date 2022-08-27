# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/23 16:04:18 by sel-mars          #+#    #+#              #
#    Updated: 2022/08/27 12:58:18 by sel-mars         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3D

HDFL	=	assets/cub3d.h

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror

AR		=	ar rc

LIB		=	libcub3d.a

BNSLIB	=	libcub3dbonus.a

MAIN	=	assets/main.c

BNSMAIN	=	assets/bonus/main_bonus.c

SRCS	=	gnl/get_next_line.c\
			gnl/get_next_line_utils.c\
			assets/cub3d.c\
			assets/general/utils.c\
			assets/general/errors.c\
			assets/parsing/parsing.c\
			assets/parsing/check_map.c\
			assets/parsing/get_color.c\
			assets/parsing/check.c\
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

BNSSRCS	=	gnl/get_next_line.c\
			gnl/get_next_line_utils.c\
			assets/bonus/cub3d_bonus.c\
			assets/general/utils.c\
			assets/general/errors.c\
			assets/parsing/parsing.c\
			assets/parsing/get_color.c\
			assets/parsing/check.c\
			assets/mlx/init_mlx_ptrs.c\
			assets/mlx/init_walls.c\
			assets/mlx/mlx_utils.c\
			assets/mlx/key_hook.c\
			assets/mlx/leave.c\
			assets/raycast/raycast.c\
			assets/raycast/wall_hit.c\
			assets/bonus/check_map_bonus.c\
			assets/bonus/update_bonus.c\
			assets/bonus/render_bonus.c\
			assets/bonus/wall_col/wall_collision.c\
			assets/bonus/mini_map/mini_map.c\

BNSOBJS	=	$(BNSSRCS:%.c=%.o)

%.o:	%.c $(HDFL) $(BNSHDFL)
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME):	$(HDFL) $(OBJS)
	make -C libft
	make -C mlx
	$(AR) $(LIB) $(OBJS)
	$(CC) $(CFLAGS) $(MAIN) -L. -lcub3d -L./libft -lft -L./mlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

bonus:	$(BNSHDFL) $(BNSOBJS)
	make -C libft
	make -C mlx
	$(AR) $(BNSLIB) $(BNSOBJS)
	$(CC) $(CFLAGS) $(BNSMAIN) -L. -lcub3dbonus -L./libft -lft -L./mlx -lmlx -framework OpenGL -framework AppKit -o cub3D_bonus

all:	$(NAME)

clean:
	make clean -C libft
	make clean -C mlx
	rm -rf $(OBJS) $(BNSOBJS) $(LIB) $(BNSLIB)

fclean:	clean
	make fclean -C libft
	make clean -C mlx
	rm -rf $(NAME) cub3D_bonus

re:	fclean $(NAME)

.PHONY:	all clean fclean