/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 16:01:56 by sel-mars          #+#    #+#             */
/*   Updated: 2022/07/25 19:05:28 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include "../gnl/get_next_line.h"
# include <fcntl.h>
# include <stdbool.h>

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
	char	**map;	
} t_map;

typedef struct s_player
{
	int		x_pos;
	int		y_pos;
	char	orient;	
} t_player;

typedef struct s_cub
{
	char		*tmp_str;
	int			tmp_int;
	bool		error;
	char		*buff;
	int			map_fd;
	char		*map_path;
	t_params	params;
	t_map		map;
	t_player	player;
} t_cub;

int		cub3d(int ac, char **av);
t_cub	*parsing(int ac, char **av);
#endif