/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 15:23:36 by sel-mars          #+#    #+#             */
/*   Updated: 2022/08/10 15:36:40 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	init_mlx_ptrs(t_cub *cub)
{
	int	tmp;

	cub->mlx.mlx = mlx_init();
	if (!cub->mlx.mlx)
		return (ft_map_param_error(cub,
			"Error: Failed to set up the connection to the graphical system"));
	cub->mlx.win = mlx_new_window(cub->mlx.mlx, WIN_WIDTH, WIN_HEIGHT,
		"cub3D");
	if (!cub->mlx.win)
		return (ft_map_param_error(cub,
			"Error: Failed to create a new window"));
	cub->mlx.wall_north = mlx_xpm_file_to_image(cub->mlx.mlx, cub->params.no_text, &tmp, &tmp);
	cub->mlx.wall_no_data = (int *)mlx_get_data_addr(cub->mlx.wall_north, &tmp, &cub->mlx.wall_line_bytes, &tmp);
	cub->mlx.wall_line_bytes /= 4;
	cub->mlx.wall_so = mlx_xpm_file_to_image(cub->mlx.mlx, cub->params.so_text, &tmp, &tmp);
	cub->mlx.wall_so_data = (int *)mlx_get_data_addr(cub->mlx.wall_so, &tmp, &tmp, &tmp);
	cub->mlx.wall_ea = mlx_xpm_file_to_image(cub->mlx.mlx, cub->params.ea_text, &tmp, &tmp);
	cub->mlx.wall_ea_data = (int *)mlx_get_data_addr(cub->mlx.wall_ea, &tmp, &tmp, &tmp);
	cub->mlx.wall_we = mlx_xpm_file_to_image(cub->mlx.mlx, cub->params.we_text, &tmp, &tmp);
	cub->mlx.wall_we_data = (int *)mlx_get_data_addr(cub->mlx.wall_we, &tmp, &tmp, &tmp);
	cub->mlx.master = mlx_new_image(cub->mlx.mlx, WIN_WIDTH, WIN_HEIGHT);
	cub->mini_map.floor = mlx_new_image(cub->mlx.mlx, MINI_MAP_TILE_SIZE, MINI_MAP_TILE_SIZE);
	mlx_change_image_color(cub->mini_map.floor, cub->params.f_color, MINI_MAP_TILE_SIZE, MINI_MAP_TILE_SIZE);
	cub->mini_map.wall = mlx_new_image(cub->mlx.mlx, MINI_MAP_TILE_SIZE, MINI_MAP_TILE_SIZE);
	mlx_change_image_color(cub->mini_map.wall, argb_to_int(0, 32, 35, 214), MINI_MAP_TILE_SIZE, MINI_MAP_TILE_SIZE);
	cub->mini_map.player = mlx_xpm_file_to_image(cub->mlx.mlx,
		"./textures/red_dot_4x4.xpm", &tmp, &tmp);
	return (0);
}
