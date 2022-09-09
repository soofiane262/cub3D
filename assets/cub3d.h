/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 16:01:56 by sel-mars          #+#    #+#             */
/*   Updated: 2022/09/09 01:42:49 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
/* -------------------------------------------------------------------------- */
/*                                  Includes                                  */
/* -------------------------------------------------------------------------- */
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
# define TILE_SIZE				100
# define PLAYER_SIZE			10
# define WIN_WIDTH				1000
# define WIN_HEIGHT				700
# define MOVE_SPEED				10
# define FOV					60
# define STRIP_WIDTH			1
# define ROT_SPEED				0.1
/* -------------------------------------------------------------------------- */
/*                           !! TO BE CALCULATED !!                           */
/* -------------------------------------------------------------------------- */
/* -------------------- NB_RAYS = WIN_WIDTH / STRIP_WIDTH ------------------- */
# define NB_RAYS				1000
/* -------------------------------------------------------------------------- */
/*                                 Structures                                 */
/* -------------------------------------------------------------------------- */
typedef struct s_params
{
	char	*no_text;
	char	*so_text;
	char	*ea_text;
	char	*we_text;
	int		f_color;
	int		c_color;
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
	bool			door_exists;
	double			angle;
	float			wall_hit_x;
	float			wall_hit_y;
	double			wall_distance;
	float			door_hit_x;
	float			door_hit_y;
	double			door_distance;
	char			wall_orientation;
	char			door_orientation;
	struct s_ray	*next;
}	t_ray;

typedef struct s_tmp_ray
{
	bool	door_exists;
	double	angle;
	float	wall_hit_x;
	float	wall_hit_y;
	double	wall_distance;
	float	door_hit_x;
	float	door_hit_y;
	double	door_distance;
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
	int			error_parse;
	int			count;
	t_ray		*ray;
	t_params	params;
	t_map		map;
	t_player	player;
	t_mlx		mlx;
}	t_cub;

int			cub3d(int ac, char **av);
t_cub		*parsing(int ac, char **av);
/* --------------------------------- General -------------------------------- */
int			ft_put_error(char *error);
int			check_extension(char *str, char *ext);
int			argb_to_int(int alpha, int red, int green, int blue);
int			int_in_range(int to_check, int min, int max);
int			skip_space(char *str, int i);
int			skip_space_rv(char *str, int i);
char		*ft_check_path_texture(t_cub *cub);
int			get_color(char *str, int i, int j);
int			ft_check_color(t_cub *cub, int color);
void		ft_check_map(t_cub *cub);
/* --------------------------------- Parsing -------------------------------- */
void		ft_map_param_error(t_cub *cub, int error, char *str);
t_cub		*parsing(int ac, char **av);
int			parse_params(t_cub *cub);
/* ----------------------------------- mlx ---------------------------------- */
void		init_mlx_ptrs(t_cub *cub);
void		init_walls(t_cub *cub);
void		mlx_img_error(t_cub *cub, char *error, int wall_to_destroy);
int			leave(t_cub *cub);
int			key_press(int key, t_cub *cub);
int			key_release(int key, t_cub *cub);
/* --------------------------------- Raycast -------------------------------- */
void		raycast(t_cub *cub);
void		ray_free(t_cub *cub);
void		choose_nearest_hit(t_ray *ray, t_tmp_ray hor, t_tmp_ray ver);
t_tmp_ray	vertical_hit(t_cub *cub, t_ray *ray, float diff[2]);
t_tmp_ray	horizontal_hit(t_cub *cub, t_ray *ray, float diff[2]);
t_tmp_ray	vertical_hit_wall(t_tmp_ray ret, t_cub *cub);
t_tmp_ray	vertical_hit_door(t_tmp_ray ret, t_cub *cub);
t_tmp_ray	horizontal_hit_wall(t_tmp_ray ret, t_cub *cub);
t_tmp_ray	horizontal_hit_door(t_tmp_ray ret, t_cub *cub);
/* --------------------------------- Render --------------------------------- */
void		update_all(t_cub *cub);
int			render_frame(t_cub *cub);
#endif