/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 18:00:15 by sel-mars          #+#    #+#             */
/*   Updated: 2022/09/08 19:56:28 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	mlx_change_img_color(void *img, int color)
{
	int		idx[2];
	int		coord[2];
	int		endian;
	int		*buff;

	buff = (int *)mlx_get_data_addr(img, &coord[0], &coord[1], &endian);
	coord[1] /= 4;
	idx[0] = 0;
	while (idx[0] < MINI_MAP_TILE_SIZE)
	{
		idx[1] = 0;
		while (idx[1] < MINI_MAP_TILE_SIZE)
		{
			buff[idx[0] * coord[1] + idx[1]] = color;
			idx[1]++;
		}
		idx[0]++;
	}
}

void	init_mini_map(t_cub_bonus *cub_bonus)
{
	int	tmp;

	cub_bonus->mini_map.player = mlx_xpm_file_to_image(
			cub_bonus->cub->mlx.mlx, "textures/red_dot_10x10.xpm", &tmp, &tmp);
}

void	paint_mini_map(t_cub_bonus *cub_bonus)
{
	int	i[2];
	int	j[2];

	i[0] = (cub_bonus->cub->player.y_pos + TILE_SIZE / 2) / TILE_SIZE;
	j[0] = MINI_MAP_HEIGHT / 2 + MINI_MAP_MARGIN + - MINI_MAP_TILE_SIZE / 2;
	while (i[0] >= 0 && j[0] >= MINI_MAP_MARGIN + 2)
	{
		i[1] = (cub_bonus->cub->player.x_pos + TILE_SIZE / 2) / TILE_SIZE;
		j[1] = MINI_MAP_WIDTH / 2 + MINI_MAP_MARGIN + - MINI_MAP_TILE_SIZE / 2;
		while (i[1] >= 0 && j[1] >= MINI_MAP_MARGIN + 2)
		{
			if (cub_bonus->cub->map.map[i[0]][i[1]] == '0')
				// mlx_put_image_to_window(cub_bonus->cub->mlx.mlx, cub_bonus->cub->mlx.win, cub_bonus->mini_map.floor, j[1], j[0]);
				paint_square_to_master(cub_bonus, j, MINI_MAP_TILE_SIZE, cub_bonus->cub->params.f_color);
			else if (cub_bonus->cub->map.map[i[0]][i[1]] == '1')
				// mlx_put_image_to_window(cub_bonus->cub->mlx.mlx, cub_bonus->cub->mlx.win, cub_bonus->mini_map.wall, j[1], j[0]);
				paint_square_to_master(cub_bonus, j, MINI_MAP_TILE_SIZE, argb_to_int(0, 40, 89, 202));
			j[1] -= MINI_MAP_TILE_SIZE;
			i[1]--;
		}
		j[0] -= MINI_MAP_TILE_SIZE;
		i[0]--;
	}
	i[0] = (cub_bonus->cub->player.y_pos + TILE_SIZE / 2) / TILE_SIZE;
	j[0] = MINI_MAP_HEIGHT / 2 + MINI_MAP_MARGIN + - MINI_MAP_TILE_SIZE / 2;
	while (i[0] >= 0 && j[0] >= MINI_MAP_MARGIN + 2)
	{
		i[1] = (cub_bonus->cub->player.x_pos + TILE_SIZE / 2) / TILE_SIZE;
		j[1] = MINI_MAP_WIDTH / 2 + MINI_MAP_MARGIN + - MINI_MAP_TILE_SIZE / 2;
		while (i[1] < cub_bonus->cub->map.width && j[1] < MINI_MAP_WIDTH - 2)
		{
			if (cub_bonus->cub->map.map[i[0]][i[1]] == '0')
				// mlx_put_image_to_window(cub_bonus->cub->mlx.mlx, cub_bonus->cub->mlx.win, cub_bonus->mini_map.floor, j[1], j[0]);
				paint_square_to_master(cub_bonus, j, MINI_MAP_TILE_SIZE, cub_bonus->cub->params.f_color);
			else if (cub_bonus->cub->map.map[i[0]][i[1]] == '1')
				// mlx_put_image_to_window(cub_bonus->cub->mlx.mlx, cub_bonus->cub->mlx.win, cub_bonus->mini_map.wall, j[1], j[0]);
				paint_square_to_master(cub_bonus, j, MINI_MAP_TILE_SIZE, argb_to_int(0, 40, 89, 202));
			j[1] += MINI_MAP_TILE_SIZE;
			i[1]++;
		}
		j[0] -= MINI_MAP_TILE_SIZE;
		i[0]--;
	}
	i[0] = (cub_bonus->cub->player.y_pos + TILE_SIZE / 2) / TILE_SIZE;
	j[0] = MINI_MAP_HEIGHT / 2 + MINI_MAP_MARGIN + - MINI_MAP_TILE_SIZE / 2;
	while (i[0] < cub_bonus->cub->map.height && j[0] < MINI_MAP_HEIGHT - 2)
	{
		i[1] = (cub_bonus->cub->player.x_pos + TILE_SIZE / 2) / TILE_SIZE;
		j[1] = MINI_MAP_WIDTH / 2 + MINI_MAP_MARGIN + - MINI_MAP_TILE_SIZE / 2;
		while (i[1] >= 0 && j[1] >= MINI_MAP_MARGIN + 2)
		{
			if (cub_bonus->cub->map.map[i[0]][i[1]] == '0')
				// mlx_put_image_to_window(cub_bonus->cub->mlx.mlx, cub_bonus->cub->mlx.win, cub_bonus->mini_map.floor, j[1], j[0]);
				paint_square_to_master(cub_bonus, j, MINI_MAP_TILE_SIZE, cub_bonus->cub->params.f_color);
			else if (cub_bonus->cub->map.map[i[0]][i[1]] == '1')
				// mlx_put_image_to_window(cub_bonus->cub->mlx.mlx, cub_bonus->cub->mlx.win, cub_bonus->mini_map.wall, j[1], j[0]);
				paint_square_to_master(cub_bonus, j, MINI_MAP_TILE_SIZE, argb_to_int(0, 40, 89, 202));
			j[1] -= MINI_MAP_TILE_SIZE;
			i[1]--;
		}
		j[0] += MINI_MAP_TILE_SIZE;
		i[0]++;
	}
	i[0] = (cub_bonus->cub->player.y_pos + TILE_SIZE / 2) / TILE_SIZE;
	j[0] = MINI_MAP_HEIGHT / 2 + MINI_MAP_MARGIN + - MINI_MAP_TILE_SIZE / 2;
	while (i[0] < cub_bonus->cub->map.height && j[0] < MINI_MAP_HEIGHT - 2)
	{
		i[1] = (cub_bonus->cub->player.x_pos + TILE_SIZE / 2) / TILE_SIZE;
		j[1] = MINI_MAP_WIDTH / 2 + MINI_MAP_MARGIN + - MINI_MAP_TILE_SIZE / 2;
		while (i[1] < cub_bonus->cub->map.width && j[1] < MINI_MAP_WIDTH - 2)
		{
			if (cub_bonus->cub->map.map[i[0]][i[1]] == '0')
				// mlx_put_image_to_window(cub_bonus->cub->mlx.mlx, cub_bonus->cub->mlx.win, cub_bonus->mini_map.floor, j[1], j[0]);
				paint_square_to_master(cub_bonus, j, MINI_MAP_TILE_SIZE, cub_bonus->cub->params.f_color);
			else if (cub_bonus->cub->map.map[i[0]][i[1]] == '1')
				// mlx_put_image_to_window(cub_bonus->cub->mlx.mlx, cub_bonus->cub->mlx.win, cub_bonus->mini_map.wall, j[1], j[0]);
				paint_square_to_master(cub_bonus, j, MINI_MAP_TILE_SIZE, argb_to_int(0, 40, 89, 202));
			j[1] += MINI_MAP_TILE_SIZE;
			i[1]++;
		}
		j[0] += MINI_MAP_TILE_SIZE;
		i[0]++;
	}
	mlx_put_image_to_window(cub_bonus->cub->mlx.mlx, cub_bonus->cub->mlx.win, cub_bonus->mini_map.player,
		MINI_MAP_WIDTH / 2 + MINI_MAP_MARGIN - (MINI_MAP_PLAYER_SIZE / 2) - 2,
		MINI_MAP_HEIGHT / 2 + MINI_MAP_MARGIN - (MINI_MAP_PLAYER_SIZE / 2) - 2);
}