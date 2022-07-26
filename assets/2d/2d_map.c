/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 12:25:51 by sel-mars          #+#    #+#             */
/*   Updated: 2022/07/26 14:23:37 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// int	mini_map(t_cub *cub)
// {
// 	int	i;

// 	cub->map.tile_size_2d = sqrt((MAX_2D_WIDTH / cub->map.width)
// 		* (MAX_2D_HEIGHT / cub->map.height));
// 	cub->map.width_2d = cub->map.tile_size_2d * cub->map.width;
// 	cub->map.height_2d = cub->map.tile_size_2d * cub->map.height;
// 	i = MARGIN_2D_MAP;
// 	while (i < cub->map.height)
// 	{
// 		mlx_pixel_put(cub->mlx.mlx_ptr, cub->mlx.win_ptr,
// 			i + WIN_HEIGHT - MARGIN_2D_MAP - cub->map.height_2d,
// 			i + WIN_HEIGHT - MARGIN_2D_MAP,
// 			rgb_to_int(255, 255, 255));
// 		i++;
// 	}
// 	return (0);
// }

void	mlx_put_tile(int x_start, int y_start, int color, t_mlx mlx_ptrs)
{
	int	i;
	int	j;

	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			mlx_pixel_put(mlx_ptrs.mlx_ptr, mlx_ptrs.win_ptr,
				x_start + j, y_start + i, color);
			j++;
		}
		i++;
	}
}

int	ft_2d_map(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (i < cub->map.height)
	{
		j = 0;
		while (j < cub->map.width)
		{
			if (cub->map.map[i][j] == '1')
				mlx_put_tile(j * TILE_SIZE, i * TILE_SIZE, rgb_to_int(73, 64, 255), cub->mlx);
			else if (cub->map.map[i][j] == '0')
				mlx_put_tile(j * TILE_SIZE, i * TILE_SIZE, cub->params.f_color, cub->mlx);
			else if (ft_strchr("NSEW", cub->map.map[i][j]))
				mlx_put_tile(j * TILE_SIZE, i * TILE_SIZE, rgb_to_int(217, 56, 62), cub->mlx);
			else
				mlx_put_tile(j * TILE_SIZE, i * TILE_SIZE, rgb_to_int(0, 0, 0), cub->mlx);
			j++;
		}
		i++;
	}
	return (0);
}

int	init_mlx_ptrs(t_cub *cub)
{
	cub->mlx.mlx_ptr = mlx_init();
	if (!cub->mlx.mlx_ptr)
		return (ft_map_param_error(cub,
			"Error: Failed to set up the connection to the graphical system"));
	cub->mlx.win_ptr = mlx_new_window(cub->mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT,
		"cub3D");
	if (!cub->mlx.win_ptr)
		return (ft_map_param_error(cub,
			"Error: Failed to create a new window"));
	return (0);
}
