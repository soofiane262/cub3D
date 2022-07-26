/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 15:28:23 by sel-mars          #+#    #+#             */
/*   Updated: 2022/07/26 18:37:38 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

#include <time.h>

int	leave(t_cub *cub)
{
	int	i;

	free(cub->map_path);
	free(cub->params.no_text);
	free(cub->params.so_text);
	free(cub->params.ea_text);
	free(cub->params.we_text);
	i = 0;
	while (i < cub->map.height)
	{
		free(cub->map.map[i]);
		cub->map.map[i++] = NULL;
	}
	free(cub->map.map);
	cub->map.map = NULL;
	mlx_destroy_window(cub->mlx.mlx_ptr, cub->mlx.win_ptr);
	free(cub);
	cub = NULL;
	exit(0);
	return (0);
}

// void	mlx_put_line(int x, int y, int color, t_mlx mlx_ptrs)
// {
// 	int	i;

// 	i = 0;
// 	while (i < TILE_SIZE)
// 	{
// 		mlx_pixel_put(mlx_ptrs.mlx_ptr, mlx_ptrs.win_ptr,
// 			x, y + i, color);
// 		i++;
// 	}
// }

int	render_frame(t_cub *cub)
{
	(void)cub;
	return (0);
}

int	key_hook(int key, t_cub *cub)
{
	(void)cub;
	if (key == 53)
		leave(cub);
	else if (key == 13)
	{
		// W
	}
	else if (key == 0)
	{
		// A
	}
	else if (key == 1)
	{
		// S
	}
	else if (key == 2)
	{
		// D
	}
	else if (key == 123)
	{
		// <- (Left)
	}
	else if (key == 124)
	{
		// -> (Right)
	}
	else if (key == 125)
	{
		// (Down)
	}
	else if (key == 126)
	{
		// ^ (Up)
	}
	// ft_putnbr_fd(key, 1);
	// ft_putendl_fd("", 1);
	return (0);
}
