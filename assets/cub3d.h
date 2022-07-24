/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 16:01:56 by sel-mars          #+#    #+#             */
/*   Updated: 2022/07/24 19:28:12 by sel-mars         ###   ########.fr       */
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
	bool	no_param;
	char	*no_text;
	bool	so_param;
	char	*so_text;
	bool	ea_param;
	char	*ea_text;
	bool	we_param;
	char	*we_text;
	int		f_color;
	int		f_red;
	int		f_green;
	int		f_blue;
	int		c_color;
	int		c_red;
	int		c_green;
	int		c_blue;
} t_params;

typedef struct s_cub
{
	char		*tmp_str;
	char		*buff;
	int			map_fd;
	t_params	params;
} t_cub;

int		cub3d(int ac, char **av);
t_cub	*parsing(int ac, char **av);
#endif