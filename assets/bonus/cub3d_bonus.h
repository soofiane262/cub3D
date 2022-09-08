/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 16:01:56 by sel-mars          #+#    #+#             */
/*   Updated: 2022/09/08 19:48:56 by kid-bouh         ###   ########.fr       */
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
# define ON_BUTTONPRESS			4
# define ON_BUTTONRELEASE		5
# define ON_MOUSEMOVE			6
# define MINI_MAP_TILE_SIZE		15
# define MINI_MAP_PLAYER_SIZE	4
# define MINI_MAP_MARGIN		10
/* -------------------------------------------------------------------------- */
/*                           !! TO BE CALCULATED !!                           */
/* -------------------------------------------------------------------------- */
/* ------------ MINI_MOVE_SPEED = MINI_MAP_TILE_SIZE / MOVE_SPEED ----------- */
# define MINI_MOVE_SPEED		1.5
/* ---------------- MINI_MAP_WIDTH = MINI_MAP_TILE_SIZE * 10 ---------------- */
# define MINI_MAP_WIDTH			200
/* ---------------- MINI_MAP_HEIGHT = MINI_MAP_TILE_SIZE * 10 --------------- */
# define MINI_MAP_HEIGHT		150
/* -------------------------------------------------------------------------- */
/*                                 Structures                                 */
/* -------------------------------------------------------------------------- */
typedef struct s_mini_map
{
	void	*player;
} t_mini_map;

typedef struct s_door
{
	bool	door_open;
	void	**door;
	int		**door_data;
	int		door_side;
} t_door;

typedef struct s_mouse
{
	bool	clicked_left;
	bool	clicked_right;
	float	angle;
} t_mouse;

typedef struct s_gun
{
	int		idx;
	int		counter;
	void	**gun;
	int		**gun_data;
	int		gun_side;
	int		gun_height;
} t_gun;

typedef struct	s_cub_bonus
{
	t_cub		*cub;
	t_mouse		mouse;
	t_gun		gun;
	t_door		door;
	t_mini_map	mini_map;
} t_cub_bonus;

int		cub3d_bonus(int ac, char **av);
void	ft_check_map_bonus(t_cub *cub);
int		leave_bonus(t_cub_bonus *cub_bonus);
/* --------------------------------- Render --------------------------------- */
void	update_all_bonus(t_cub_bonus *cub_bonus);
int		render_frame_bonus(t_cub_bonus *cub_bonus);
void	paint_master_bonus(t_cub_bonus *cub_bonus);
/* ----------------------------- Wall Collision ----------------------------- */
int		check_wall_collision(int new_x, int new_y, t_cub *cub);
/* -------------------------------- Mini Map -------------------------------- */
void	init_mini_map(t_cub_bonus *cub_bonus);
void	paint_mini_map(t_cub_bonus *cub_bonus);
void	mlx_change_img_color(void *img, int color);
void	paint_square_to_master(t_cub_bonus *cub_bonus, int coord[2],
	int size, int color);

int	button_press(int button, int x, int y, t_cub_bonus *cub_bonus);
int	button_release(int button, int x, int y, t_cub_bonus *cub_bonus);
int	mouse_move(int x, int y, t_cub_bonus *cub_bonus);

#endif