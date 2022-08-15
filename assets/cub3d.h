/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 16:01:56 by sel-mars          #+#    #+#             */
/*   Updated: 2022/08/10 19:38:11 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
/* -------------------------------------------------------------------------- */
/*                                  Includes                                  */
/* -------------------------------------------------------------------------- */
/* ------------------------------------ - ----------------------------------- */
/* ------------------------------ Header Files ------------------------------ */
# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include "../gnl/get_next_line.h"
/* -------------------------------- Libraries ------------------------------- */
# include <fcntl.h>
# include <stdbool.h>
# include <math.h>
/* -------------------------------------------------------------------------- */
/*                                   Defines                                  */
/* -------------------------------------------------------------------------- */
/* ------------------------------------ - ----------------------------------- */
/* --------------------------------- General -------------------------------- */
# define ON_DESTROY				17
# define ON_KEYPRESS			2
# define ON_KEYRELEASE			3
# define ESC					53
# define W						13
# define S						1
# define A						0
# define D						2
# define LEFT_ARROW				123
# define RIGHT_ARROW			124
/* -------------------------------- Mandatory ------------------------------- */
# define TILE_SIZE				100
# define PLAYER_SIZE			10
# define WIN_WIDTH				1000
# define WIN_HEIGHT				700
# define MOVE_SPEED				10
# define MINI_MOVE_SPEED		MINI_MAP_TILE_SIZE / MOVE_SPEED
# define ROT_SPEED				5 * M_PI / 180
# define FOV					60
# define STRIP_WIDTH			1
# define NB_RAYS				WIN_WIDTH / STRIP_WIDTH
/* ---------------------------------- Bonus --------------------------------- */
# define MINI_MAP_TILE_SIZE		15
# define MINI_MAP_PLAYER_SIZE	4
# define MINI_MAP_MARGIN		20
# define MINI_MAP_WIDTH			MINI_MAP_TILE_SIZE * 20
# define MINI_MAP_HEIGHT		MINI_MAP_TILE_SIZE * 10
/* -------------------------------------------------------------------------- */
/*                                 Structures                                 */
/* -------------------------------------------------------------------------- */
typedef struct s_params
{
	int		nb_params;
	int		no_param;
	char	*no_text;
	int		so_param;
	char	*so_text;
	int		ea_param;
	char	*ea_text;
	int		we_param;
	char	*we_text;
	int		f_param;
	int		f_color;
	int		f_red;
	int		f_green;
	int		f_blue;
	int		c_param;
	int		c_color;
	int		c_red;
	int		c_green;
	int		c_blue;
}	t_params;

typedef struct s_map
{
	int		width;
	int		height;
	int		tile_size_mini_map;
	int		mini_map_width;
	int		mini_map_height;
	char	**map;
}	t_map;

typedef struct s_mini_map
{
	int		width;
	int		height;
	int		offset[2];
	void	*background;
	void	*floor;
	void	*wall;
	void	*player;
}	t_mini_map;

typedef struct s_player
{
	float	x_pos;
	float	y_pos;
	int		turn;
	int		mvt;
	double	rotation;
	char	orient;
}	t_player;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*master;
	int		*master_data;
	void	*wall_north;
	int		*wall_no_data;
	int		wall_no_side;
	void	*wall_south;
	int		*wall_so_data;
	int		wall_so_side;
	void	*wall_east;
	int		*wall_ea_data;
	int		wall_ea_side;
	void	*wall_west;
	int		*wall_we_data;
	int		wall_we_side;
}	t_mlx;

typedef struct s_ray
{
	double			ray_angle;
	float			wall_x;
	float			wall_y;
	double			distance;
	char			orientation;
	struct s_ray	*next;
}	t_ray;

typedef struct s_tmp_ray
{
	double	ray_angle;
	float	wall_x;
	float	wall_y;
	double	distance;
	float	x_intersept;
	float	y_intersept;
	float	x_step;
	float	y_step;
}	t_tmp_ray;

typedef struct s_cub
{
	char		*tmp_str;
	int			tmp_int;
	int			tmp_int2;
	bool		error;
	char		*buff;
	int			map_fd;
	char		*map_path;
	t_ray		*ray;
	t_params	params;
	t_map		map;
	t_mini_map	mini_map;
	t_player	player;
	t_mlx		mlx;
}	t_cub;

int		cub3d(int ac, char **av);
t_cub	*parsing(int ac, char **av);

//	general
int	argb_to_int(int alpha, int red, int green, int blue);
int	ft_put_error(char *error);
int	skip_space(char *str, int i);

//	parsing
void	init_params(t_cub *cub);
int	ft_map_param_error(t_cub *cub, char *str);
int	check_map_surroundings(t_cub *cub);
int	check_space_surroundings(t_cub *cub);
int	check_map_content(t_cub *cub);
int	check_map(t_cub *cub);
int	ft_map_param_error(t_cub *cub, char *str);
int	read_map_file(t_cub *cub);


//	mlx
int		init_mlx_ptrs(t_cub *cub);
int		init_north_wall(t_cub *cub);
int		init_south_wall(t_cub *cub);
int		init_east_wall(t_cub *cub);
int		init_west_wall(t_cub *cub);
int		mlx_img_error(t_cub *cub, char *error, int wall_to_destroy);

//	render
void	update_all(t_cub *cub);



//	2d_map
int		ft_2d_map(t_cub *cub);

void	mlx_put_line(int x_start, int y_start, double x_end, double y_end, int color,
	void *mlx, void *win);


//	mini_map
// int	put_mini_map(t_cub *cub);




//	raycast
void	raycast(t_cub *cub);
void	ray_free(t_cub *cub);


//	key_hook
int	key_press(int key, t_cub *cub);
int	key_release(int key, t_cub *cub);

//	key_hooks
int	leave(t_cub *cub);
int	render_frame(t_cub *cub);


#endif