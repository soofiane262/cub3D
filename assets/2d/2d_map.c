/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 12:25:51 by sel-mars          #+#    #+#             */
/*   Updated: 2022/08/03 19:33:29 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

#include <stdio.h>

int	put_mini_map(t_cub *cub)
{
	int	i[2];
	int	j[2];

	mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.win,
		cub->mini_map.background, MINI_MAP_MARGIN, MINI_MAP_MARGIN);
	i[0] = cub->player.y_pos / TILE_SIZE;
	j[0] = MINI_MAP_HEIGHT / 2 + cub->mini_map.diff[0];
	while (i[0] >= 0 && j[0] >= MINI_MAP_MARGIN + 2)
	{
		i[1] = cub->player.x_pos / TILE_SIZE;
		j[1] = MINI_MAP_WIDTH / 2 + cub->mini_map.diff[1];
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
	i[0] = cub->player.y_pos / TILE_SIZE;
	j[0] = MINI_MAP_HEIGHT / 2 + cub->mini_map.diff[0];
	while (i[0] >= 0 && j[0] >= MINI_MAP_MARGIN + 2)
	{
		i[1] = cub->player.x_pos / TILE_SIZE;
		j[1] = MINI_MAP_WIDTH / 2 + cub->mini_map.diff[1];
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
	i[0] = cub->player.y_pos / TILE_SIZE;
	j[0] = MINI_MAP_HEIGHT / 2 + cub->mini_map.diff[0];
	while (i[0] < cub->map.height && j[0] < MINI_MAP_HEIGHT - 2)
	{
		i[1] = cub->player.x_pos / TILE_SIZE;
		j[1] = MINI_MAP_WIDTH / 2 + cub->mini_map.diff[1];
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
	i[0] = cub->player.y_pos / TILE_SIZE;
	j[0] = MINI_MAP_HEIGHT / 2 + cub->mini_map.diff[0];
	while (i[0] < cub->map.height && j[0] < MINI_MAP_HEIGHT - 2)
	{
		i[1] = cub->player.x_pos / TILE_SIZE;
		j[1] = MINI_MAP_WIDTH / 2 + cub->mini_map.diff[1];
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
		MINI_MAP_WIDTH / 2 + MINI_MAP_MARGIN - (MINI_MAP_TILE_SIZE - PLAYER_SIZE) / 2,
		MINI_MAP_HEIGHT / 2 + MINI_MAP_MARGIN - (MINI_MAP_TILE_SIZE - PLAYER_SIZE) / 2);
	// mlx_pixel_put(cub->mlx.mlx, cub->mlx.win, MINI_MAP_WIDTH / 2 + MINI_MAP_MARGIN, MINI_MAP_HEIGHT / 2 + MINI_MAP_MARGIN, rgb_to_int(255, 255, 255));
	return (0);
}

void	mlx_put_line(int x_start, int y_start, double x_end, double y_end, int color, t_mlx mlx_ptrs)
{
	int			i;
	int			j;
	double		m;
	double		n;


	if (y_start == (int)y_end || x_start == (int)x_end)
	{
		i = fmin(y_start, (int)y_end);
		while (i <= fmax(y_start, (int)y_end))
		{
			j = fmin(x_start, (int)x_end);
			while (j <= fmax(x_start, (int)x_end))
			{
				mlx_pixel_put(mlx_ptrs.mlx, mlx_ptrs.win, j, i, color);
				j++;
			}
			i++;
		}
		return ;
	}
	m = ((y_end - y_start) / (x_end - x_start));
	n = y_start - ((y_end - y_start) / (x_end - x_start)) * x_start;
	i = fmin(y_start, (int)y_end);
	while (i <= fmax(y_start, (int)y_end))
	{
		j = fmin(x_start, (int)x_end);
		while (j <= fmax(x_start, (int)x_end))
		{
			if (fabs((m * j + n - i)) <= 1)
				mlx_pixel_put(mlx_ptrs.mlx, mlx_ptrs.win, j, i, color);
			j++;
		}
		i++;
	}
}

void	mlx_put_rays(t_cub *cub)
{
	int		i;
	t_ray	*ray_head;

	cub->ray = raycast(cub);
	ray_head = cub->ray;
	i = -1;
	while (++i < NB_RAYS)
	{
		mlx_put_line(cub->player.x_pos + TILE_SIZE / 2, cub->player.y_pos + TILE_SIZE / 2,
			cub->ray->wall_x, cub->ray->wall_y, rgb_to_int(217, 56, 62), cub->mlx);
		cub->ray = cub->ray->next;
	}
	cub->ray = ray_head;
	ray_free(cub);
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
			if (cub->map.map[i][j] == '0')
				mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.win, 
					cub->mlx.floor, j * TILE_SIZE, i * TILE_SIZE);
			else if (cub->map.map[i][j] == '1')
				mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.win, 
					cub->mlx.north, j * TILE_SIZE, i * TILE_SIZE);
			j++;
		}
		i++;
	}
	mlx_put_rays(cub);
	mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.win,
		cub->mlx.player, cub->player.x_pos + (TILE_SIZE - PLAYER_SIZE) / 2,
		cub->player.y_pos + (TILE_SIZE - PLAYER_SIZE) / 2);
	return (0);
}

void	mlx_change_image_color(void *img, int color, int img_size)
{
	int		idx[2];
	int		coord[2];
	int		endian;
	int		*buff;

	buff = (int *)mlx_get_data_addr(img, &coord[0], &coord[1], &endian);
	coord[1] /= 4;
	idx[0] = 0;
	while (idx[0] < img_size)
	{
		idx[1] = 0;
		while (idx[1] < img_size)
		{
			buff[idx[0] * coord[1] + idx[1]] = color;
			idx[1]++;
		}
		idx[0]++;
	}
}

void	mlx_change_mini_map_bg_color(t_cub *cub)
{
	int		idx[2];
	int		coord[2];
	int		endian;
	int		*buff;

	buff = (int *)mlx_get_data_addr(cub->mini_map.background, &coord[0], &coord[1], &endian);
	coord[1] /= 4;
	idx[0] = 0;
	while (idx[0] < MINI_MAP_HEIGHT)
	{
		idx[1] = 0;
		while (idx[1] < MINI_MAP_WIDTH)
		{
			if (idx[0] == 0 || idx[0] == 1 || idx[0] == MINI_MAP_HEIGHT - 2 || idx[0] == MINI_MAP_HEIGHT - 1
				|| idx[1] == 0 || idx[1] == 1 || idx[1] == MINI_MAP_WIDTH - 2 || idx[1] == MINI_MAP_WIDTH - 1)
				buff[idx[0] * coord[1] + idx[1]] = rgb_to_int(255, 255, 255);
			else
				buff[idx[0] * coord[1] + idx[1]] = rgb_to_int(109, 109, 125);
			idx[1]++;
		}
		idx[0]++;
	}
}

// void	mlx_change_player_color(void *img, int color, int f_color)
// {
// 	int		idx[2];
// 	int		coord[2];
// 	int		endian;
// 	int		*buff;
// 	int		rad;

// 	rad = TILE_SIZE / 4;
// 	buff = (int *)mlx_get_data_addr(img, &coord[0], &coord[1], &endian);
// 	coord[1] /= 4;
// 	idx[0] = 0;
// 	while (idx[0] < TILE_SIZE)
// 	{
// 		idx[1] = 0;
// 		while (idx[1] < TILE_SIZE)
// 		{
// 			if (sqrt((TILE_SIZE / 2 - idx[1]) * (TILE_SIZE / 2 - idx[1]) + (TILE_SIZE / 2 - idx[0]) * (TILE_SIZE / 2 - idx[0])) < rad)
// 				buff[idx[0] * coord[1] + idx[1]] = color;
// 			else
// 				buff[idx[0] * coord[1] + idx[1]] = f_color;
// 			idx[1]++;
// 		}
// 		idx[0]++;
// 	}
// }

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
	cub->mlx.north = mlx_xpm_file_to_image(cub->mlx.mlx, cub->params.no_text, &tmp, &tmp);
	cub->mlx.south = mlx_xpm_file_to_image(cub->mlx.mlx, cub->params.so_text, &tmp, &tmp);
	cub->mlx.east = mlx_xpm_file_to_image(cub->mlx.mlx, cub->params.ea_text, &tmp, &tmp);
	cub->mlx.west = mlx_xpm_file_to_image(cub->mlx.mlx, cub->params.we_text, &tmp, &tmp);

	cub->mlx.floor = mlx_new_image(cub->mlx.mlx, TILE_SIZE, TILE_SIZE);
	mlx_change_image_color(cub->mlx.floor, cub->params.f_color, TILE_SIZE);
	cub->mlx.ceiling = mlx_new_image(cub->mlx.mlx, TILE_SIZE, TILE_SIZE);
	mlx_change_image_color(cub->mlx.ceiling, cub->params.c_color, TILE_SIZE);
	cub->mlx.player = mlx_xpm_file_to_image(cub->mlx.mlx,
		"./textures/red_dot_10x10.xpm", &tmp, &tmp);

	
	
	cub->mini_map.background = mlx_new_image(cub->mlx.mlx, MINI_MAP_WIDTH, MINI_MAP_HEIGHT);
	mlx_change_mini_map_bg_color(cub);
	cub->mini_map.floor = mlx_new_image(cub->mlx.mlx, MINI_MAP_TILE_SIZE, MINI_MAP_TILE_SIZE);
	mlx_change_image_color(cub->mini_map.floor, cub->params.f_color, MINI_MAP_TILE_SIZE);
	cub->mini_map.wall = mlx_new_image(cub->mlx.mlx, MINI_MAP_TILE_SIZE, MINI_MAP_TILE_SIZE);
	mlx_change_image_color(cub->mini_map.wall, rgb_to_int(32, 35, 214), MINI_MAP_TILE_SIZE);
	cub->mini_map.player = mlx_xpm_file_to_image(cub->mlx.mlx,
		"./textures/red_dot_10x10.xpm", &tmp, &tmp);
	
	

	return (0);
}
