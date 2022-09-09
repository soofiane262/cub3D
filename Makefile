# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/23 16:04:18 by sel-mars          #+#    #+#              #
#    Updated: 2022/09/09 01:27:52 by kid-bouh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3D

MLX		=	-L./mlx -lmlx -framework OpenGL -framework AppKit

HDFL	=	assets/cub3d.h

BNSHDFL	=	assets/bonus/cub3d_bonus.h

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
			assets/raycast/raycast_2.c\
			assets/raycast/wall_hit.c\
			assets/raycast/wall_hit_2.c\

OBJS	=	$(SRCS:%.c=%.o)

BNSSRCS	=	gnl/get_next_line.c\
			gnl/get_next_line_utils.c\
			assets/bonus/cub3d_bonus.c\
			assets/bonus/cub3d_bonus_2.c\
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
			assets/raycast/raycast_2.c\
			assets/raycast/wall_hit.c\
			assets/raycast/wall_hit_2.c\
			assets/bonus/utils/check_map.c\
			assets/bonus/utils/leave.c\
			assets/bonus/render/update.c\
			assets/bonus/render/render.c\
			assets/bonus/render/paint_master.c\
			assets/bonus/render/paint_wall_door_pixel.c\
			assets/bonus/wall_col/wall_collision.c\
			assets/bonus/mini_map/mini_map.c\

BNSOBJS	=	$(BNSSRCS:%.c=%.o)

%.o:	%.c $(HDFL) $(BNSHDFL)
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME):	$(HDFL) $(OBJS)
	make -C libft
	make -C mlx
	$(AR) $(LIB) $(OBJS)
	$(CC) $(CFLAGS) $(MAIN) $(MLX) -L. -lcub3d -L./libft -lft -o $(NAME)

bonus:	$(BNSHDFL) $(BNSOBJS)
	make -C libft
	make -C mlx
	$(AR) $(BNSLIB) $(BNSOBJS)
	$(CC) $(CFLAGS) $(BNSMAIN) $(MLX) -L. -lcub3dbonus -L./libft -lft -o cub3D_bonus

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