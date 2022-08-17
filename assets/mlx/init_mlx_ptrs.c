/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx_ptrs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 15:23:36 by sel-mars          #+#    #+#             */
/*   Updated: 2022/08/17 12:37:02 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	init_mlx_and_win(t_cub *cub)
{
	cub->mlx.mlx = mlx_init();
	if (!cub->mlx.mlx)
		ft_map_param_error(cub,
				"Error: Failed to set up connection to graphical system");
	cub->mlx.win = mlx_new_window(cub->mlx.mlx, WIN_WIDTH, WIN_HEIGHT,
			"cub3D");
	if (!cub->mlx.win)
		ft_map_param_error(cub,
				"Error: Failed to create a new window");
}

void	init_mlx_ptrs(t_cub *cub)
{
	init_mlx_and_win(cub);
	init_walls(cub);
	cub->mlx.master = mlx_new_image(cub->mlx.mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!cub->mlx.master)
		mlx_img_error(cub, "Error: Failed to create Master image", 4);
}
