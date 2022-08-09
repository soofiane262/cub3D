/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 16:01:56 by sel-mars          #+#    #+#             */
/*   Updated: 2022/08/09 13:06:07 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include "../gnl/get_next_line.h"
# include <fcntl.h>
# include <stdbool.h>
# include <math.h>
 
# define	TILE_SIZE				100
# define	PLAYER_SIZE				10
# define	WIN_WIDTH				1080
# define	WIN_HEIGHT				1000

# define	STRIP_WIDTH				1
# define	NB_RAYS					WIN_WIDTH / STRIP_WIDTH

# define	MINI_MAP_TILE_SIZE		15
# define	MINI_MAP_PLAYER_SIZE	4
# define	MINI_MAP_MARGIN			20
# define	MINI_MAP_WIDTH			MINI_MAP_TILE_SIZE * 20
# define	MINI_MAP_HEIGHT			MINI_MAP_TILE_SIZE * 10

# define	MOVE_SPEED				10
# define	MINI_MOVE_SPEED			MINI_MAP_TILE_SIZE / MOVE_SPEED
# define	ROT_SPEED				5 * M_PI / 180
# define	FOV						60

# define	ON_DESTROY				17
# define	ON_KEYPRESS				2
# define	ON_KEYRELEASE			3

# define	ESC						53
# define	W						13
# define	S						1
# define	A						0
# define	D						2
# define	LEFT_ARROW				123
# define	RIGHT_ARROW				124

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
} t_params;

typedef struct s_map
{
	int		width;
	int		height;
	int		tile_size_mini_map;
	int		mini_map_width;
	int		mini_map_height;
	char	**map;
} t_map;

typedef struct s_mini_map
{
	int		width;
	int		height;
	int		offset[2];
	void	*background;
	void	*floor;
	void	*wall;
	void	*player;
} t_mini_map;

typedef struct s_player
{
	int		x_pos;
	int		y_pos;
	int		radius;
	int		turn;
	int		mvt;
	double	rotation;
	char	orient;
} t_player;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*master;
	int		*master_data;
	int		wall_line_bytes;
	void	*wall_no;
	int		*wall_no_data;
	void	*wall_so;
	int		*wall_so_data;
	void	*wall_ea;
	int		*wall_ea_data;
	void	*wall_we;
	int		*wall_we_data;
} t_mlx;

typedef struct s_ray
{
	double	ray_angle;
	int		wall_x;
	int		wall_y;
	double	distance;
	char	orientation;
	struct s_ray	*next;
} t_ray;

typedef struct s_tmp_ray
{
	double	ray_angle;
	int		wall_x;
	int		wall_y;
	double	distance;
	int		x_intersept;
	int		y_intersept;
	int		x_step;
	int		y_step;
} t_tmp_ray;

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
} t_cub;

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

//	2d_map
int		init_mlx_ptrs(t_cub *cub);
int		ft_2d_map(t_cub *cub);
void	update(t_cub *cub);

void	mlx_put_line(int x_start, int y_start, double x_end, double y_end, int color,
	void *mlx, void *win);


//	3d
void	ft_3d(t_cub *cub);


//	mini_map
int	put_mini_map(t_cub *cub);




//	raycast
void	raycast(t_cub *cub);
void	ray_free(t_cub *cub);


//	hooks
int	leave(t_cub *cub);
int	key_press(int key, t_cub *cub);
int	key_release(int key, t_cub *cub);
int	render_frame(t_cub *cub);


#endif