/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 18:00:15 by sel-mars          #+#    #+#             */
/*   Updated: 2022/08/04 18:01:22 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// void	mlx_change_mini_map_bg_color(t_cub *cub)
// {
// 	int		idx[2];
// 	int		coord[2];
// 	int		endian;
// 	int		*buff;

// 	buff = (int *)mlx_get_data_addr(cub->mini_map.background, &coord[0], &coord[1], &endian);
// 	coord[1] /= 4;
// 	idx[0] = 0;
// 	while (idx[0] < MINI_MAP_HEIGHT)
// 	{
// 		idx[1] = 0;
// 		while (idx[1] < MINI_MAP_WIDTH)
// 		{
// 			if (idx[0] == 0 || idx[0] == 1 || idx[0] == MINI_MAP_HEIGHT - 2 || idx[0] == MINI_MAP_HEIGHT - 1
// 				|| idx[1] == 0 || idx[1] == 1 || idx[1] == MINI_MAP_WIDTH - 2 || idx[1] == MINI_MAP_WIDTH - 1)
// 				buff[idx[0] * coord[1] + idx[1]] = rgb_to_int(255, 255, 255);
// 			else
// 				buff[idx[0] * coord[1] + idx[1]] = rgb_to_int(109, 109, 125);
// 			idx[1]++;
// 		}
// 		idx[0]++;
// 	}
// }

int	put_mini_map(t_cub *cub)
{
	int	i[2];
	int	j[2];

	// mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.win,
		// cub->mini_map.background, MINI_MAP_MARGIN, MINI_MAP_MARGIN);
	i[0] = (cub->player.y_pos + TILE_SIZE / 2) / TILE_SIZE;
	j[0] = MINI_MAP_HEIGHT / 2 + MINI_MAP_MARGIN + - MINI_MAP_TILE_SIZE / 2 + cub->mini_map.offset[0];
	while (i[0] >= 0 && j[0] >= MINI_MAP_MARGIN + 2)
	{
		i[1] = (cub->player.x_pos + TILE_SIZE / 2) / TILE_SIZE;
		j[1] = MINI_MAP_WIDTH / 2 + MINI_MAP_MARGIN + - MINI_MAP_TILE_SIZE / 2 + cub->mini_map.offset[1];
		while (i[1] >= 0 && j[1] >= MINI_MAP_MARGIN + 2)
		{
			if (cub->map.map[i[0]][i[1]] == '0')
				mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.win, cub->mini_map.floor, j[1], j[0]);
			else if (cub->map.map[i[0]][i[1]] == '1')
				mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.win, cub->mini_map.wall, j[1], j[0]);
			j[1] -= MINI_MAP_TILE_SIZE;
			i[1]--;
		}
		j[0] -= MINI_MAP_TILE_SIZE;
		i[0]--;
	}
	i[0] = (cub->player.y_pos + TILE_SIZE / 2) / TILE_SIZE;
	j[0] = MINI_MAP_HEIGHT / 2 + MINI_MAP_MARGIN + - MINI_MAP_TILE_SIZE / 2 + cub->mini_map.offset[0];
	while (i[0] >= 0 && j[0] >= MINI_MAP_MARGIN + 2)
	{
		i[1] = (cub->player.x_pos + TILE_SIZE / 2) / TILE_SIZE;
		j[1] = MINI_MAP_WIDTH / 2 + MINI_MAP_MARGIN + - MINI_MAP_TILE_SIZE / 2 + cub->mini_map.offset[1];
		while (i[1] < cub->map.width && j[1] < MINI_MAP_WIDTH - 2)
		{
			if (cub->map.map[i[0]][i[1]] == '0')
				mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.win, cub->mini_map.floor, j[1], j[0]);
			else if (cub->map.map[i[0]][i[1]] == '1')
				mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.win, cub->mini_map.wall, j[1], j[0]);
			j[1] += MINI_MAP_TILE_SIZE;
			i[1]++;
		}
		j[0] -= MINI_MAP_TILE_SIZE;
		i[0]--;
	}
	i[0] = (cub->player.y_pos + TILE_SIZE / 2) / TILE_SIZE;
	j[0] = MINI_MAP_HEIGHT / 2 + MINI_MAP_MARGIN + - MINI_MAP_TILE_SIZE / 2 + cub->mini_map.offset[0];
	while (i[0] < cub->map.height && j[0] < MINI_MAP_HEIGHT - 2)
	{
		i[1] = (cub->player.x_pos + TILE_SIZE / 2) / TILE_SIZE;
		j[1] = MINI_MAP_WIDTH / 2 + MINI_MAP_MARGIN + - MINI_MAP_TILE_SIZE / 2 + cub->mini_map.offset[1];
		while (i[1] >= 0 && j[1] >= MINI_MAP_MARGIN + 2)
		{
			if (cub->map.map[i[0]][i[1]] == '0')
				mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.win, cub->mini_map.floor, j[1], j[0]);
			else if (cub->map.map[i[0]][i[1]] == '1')
				mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.win, cub->mini_map.wall, j[1], j[0]);
			j[1] -= MINI_MAP_TILE_SIZE;
			i[1]--;
		}
		j[0] += MINI_MAP_TILE_SIZE;
		i[0]++;
	}
	i[0] = (cub->player.y_pos + TILE_SIZE / 2) / TILE_SIZE;
	j[0] = MINI_MAP_HEIGHT / 2 + MINI_MAP_MARGIN + - MINI_MAP_TILE_SIZE / 2 + cub->mini_map.offset[0];
	while (i[0] < cub->map.height && j[0] < MINI_MAP_HEIGHT - 2)
	{
		i[1] = (cub->player.x_pos + TILE_SIZE / 2) / TILE_SIZE;
		j[1] = MINI_MAP_WIDTH / 2 + MINI_MAP_MARGIN + - MINI_MAP_TILE_SIZE / 2 + cub->mini_map.offset[1];
		while (i[1] < cub->map.width && j[1] < MINI_MAP_WIDTH - 2)
		{
			if (cub->map.map[i[0]][i[1]] == '0')
				mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.win, cub->mini_map.floor, j[1], j[0]);
			else if (cub->map.map[i[0]][i[1]] == '1')
				mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.win, cub->mini_map.wall, j[1], j[0]);
			j[1] += MINI_MAP_TILE_SIZE;
			i[1]++;
		}
		j[0] += MINI_MAP_TILE_SIZE;
		i[0]++;
	}
	mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.win, cub->mini_map.player,
		MINI_MAP_WIDTH / 2 + MINI_MAP_MARGIN - MINI_MAP_PLAYER_SIZE / 2,
		MINI_MAP_HEIGHT / 2 + MINI_MAP_MARGIN - MINI_MAP_PLAYER_SIZE / 2);
	cub->mini_map.offset[0] = 0;
	cub->mini_map.offset[1] = 0;
	// mlx_pixel_put(cub->mlx.mlx, cub->mlx.win, MINI_MAP_WIDTH / 2 + MINI_MAP_MARGIN, MINI_MAP_HEIGHT / 2 + MINI_MAP_MARGIN, rgb_to_int(0, 0, 0));
	return (0);
}