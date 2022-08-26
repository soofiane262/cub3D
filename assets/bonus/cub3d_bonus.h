/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 16:01:56 by sel-mars          #+#    #+#             */
/*   Updated: 2022/08/26 17:54:21 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H
/* -------------------------------------------------------------------------- */
/*                                  Includes                                  */
/* -------------------------------------------------------------------------- */
/* ------------------------------ Header Files ------------------------------ */
# include "../cub3d.h"
/* -------------------------------------------------------------------------- */
/*                                   Defines                                  */
/* -------------------------------------------------------------------------- */
# define MINI_MAP_TILE_SIZE		15
# define MINI_MAP_PLAYER_SIZE	4
# define MINI_MAP_MARGIN		20
/* -------------------------------------------------------------------------- */
/*                           !! TO BE CALCULATED !!                           */
/* -------------------------------------------------------------------------- */
/* ------------ MINI_MOVE_SPEED = MINI_MAP_TILE_SIZE / MOVE_SPEED ----------- */
# define MINI_MOVE_SPEED		1.5
/* ---------------- MINI_MAP_WIDTH = MINI_MAP_TILE_SIZE * 20 ---------------- */
# define MINI_MAP_WIDTH			300
/* ---------------- MINI_MAP_HEIGHT = MINI_MAP_TILE_SIZE * 10 --------------- */
# define MINI_MAP_HEIGHT		150
/* -------------------------------------------------------------------------- */
/*                                 Structures                                 */
/* -------------------------------------------------------------------------- */
typedef struct s_mini_map
{
	void	*floor;
	void	*wall;
	void	*player;
} t_mini_map;

typedef struct s_door
{
	void	**door;
	int		**door_data;
	int		door_side;
} t_door;

typedef struct	s_cub_bonus
{
	t_cub		*cub;
	t_door		door;
	t_mini_map	mini_map;
} t_cub_bonus;

int			cub3d_bonus(int ac, char **av);
void		ft_check_map_bonus(t_cub *cub);
/* --------------------------------- Render --------------------------------- */
void		update_all_bonus(t_cub_bonus *cub_bonus);
int			render_frame_bonus(t_cub_bonus *cub_bonus);
/* ----------------------------- Wall Collision ----------------------------- */
int			check_wall_collision(int new_x, int new_y, t_cub *cub);
/* -------------------------------- Mini Map -------------------------------- */
t_mini_map	init_mini_map(t_cub *cub);
int			put_mini_map(t_cub_bonus *cub_bonus);
void		mlx_change_img_color(void *img, int color);
#endif