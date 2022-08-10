/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx_ptrs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 15:23:36 by sel-mars          #+#    #+#             */
/*   Updated: 2022/08/10 19:17:45 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	init_mlx_and_win(t_cub *cub)
{
	cub->mlx.mlx = mlx_init();
	if (!cub->mlx.mlx)
		return (ft_map_param_error(cub,
				"Error: Failed to set up connection to graphical system"));
	cub->mlx.win = mlx_new_window(cub->mlx.mlx, WIN_WIDTH, WIN_HEIGHT,
			"cub3D");
	if (!cub->mlx.win)
		return (ft_map_param_error(cub,
				"Error: Failed to create a new window"));
	return (0);
}

int	init_mlx_ptrs(t_cub *cub)
{
	if (init_mlx_and_win(cub)
		|| init_north_wall(cub) || init_south_wall(cub)
		|| init_east_wall(cub) || init_west_wall(cub))
		return (1);
	cub->mlx.master = mlx_new_image(cub->mlx.mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!cub->mlx.master)
		return (mlx_img_error(cub, "Error: Failed to create Master image", 4));
	return (0);
}
