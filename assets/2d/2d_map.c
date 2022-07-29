/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 12:25:51 by sel-mars          #+#    #+#             */
/*   Updated: 2022/07/29 19:34:43 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

#include <stdio.h>

// #include <stdio.h>

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
// 		mlx_pixel_put(cub->mlx.mlx, cub->mlx.win,
// 			i + WIN_HEIGHT - MARGIN_2D_MAP - cub->map.height_2d,
// 			i + WIN_HEIGHT - MARGIN_2D_MAP,
// 			rgb_to_int(255, 255, 255));
// 		i++;
// 	}
// 	return (0);
// }

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
			if (fabs((m * j + n - i)) <= (double)1)
				mlx_pixel_put(mlx_ptrs.mlx, mlx_ptrs.win, j, i, color);
			if ((fabs(x_start - x_end) < (double)2 || fabs(y_start - y_end) < (double)2)
				&& fabs((m * j + n - i)) <= (double)2 && fabs((m * j + n - i)) > (double)1)
				mlx_pixel_put(mlx_ptrs.mlx, mlx_ptrs.win, j, i, color);
			j++;
		}
		i++;
	}
}

void	mlx_put_rays(t_cub *cub)
{
	// int		i;
	// double	ray_angle;
	
	// i = -1;
	// ray_angle = cub->player.rotation - (FOV * M_PI / 360);
	// while (++i < NB_RAYS)
	// {
	// 	mlx_put_line(cub->player.x_pos + TILE_SIZE / 2, cub->player.y_pos + TILE_SIZE / 2,
	// 		cub->player.x_pos + TILE_SIZE / 2 + RAY_SIZE * (double)cos(ray_angle),
	// 		cub->player.y_pos + TILE_SIZE / 2 + RAY_SIZE * (double)sin(ray_angle),
	// 		rgb_to_int(217, 56, 62), cub->mlx);
	// 	ray_angle += ((((double)FOV * M_PI) / (180 * NB_RAYS)));
	// }

	// 	// ray_angle = fmod(ray_angle, (2 * M_PI));


		mlx_put_line(cub->player.x_pos + TILE_SIZE / 2, cub->player.y_pos + TILE_SIZE / 2,
			cub->player.x_pos + TILE_SIZE / 2 + RAY_SIZE * (double)cos(cub->player.rotation),
			cub->player.y_pos + TILE_SIZE / 2 + RAY_SIZE * (double)sin(cub->player.rotation),
			rgb_to_int(217, 56, 62), cub->mlx);
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
		cub->mlx.player_dot, cub->player.x_pos + 4, cub->player.y_pos + 4);
	return (0);
}

void	mlx_change_image_color(void *img, int color)
{
	// int		i;
	int		idx[2];
	int		coord[2];
	int		endian;
	int		*buff;

	buff = (int *)mlx_get_data_addr(img, &coord[0], &coord[1], &endian);
	coord[1] /= 4;
	idx[0] = 0;
	while (idx[0] < TILE_SIZE)
	{
		idx[1] = 0;
		while (idx[1] < TILE_SIZE)
		{
			buff[idx[0] * coord[1] + idx[1]] = color;
			idx[1]++;
		}
		idx[0]++;
	}
}

void	mlx_change_player_color(void *img, int color, int f_color)
{
	// int		i;
	int		idx[2];
	int		coord[2];
	int		endian;
	int		*buff;
	int		rad;

	rad = TILE_SIZE / 4;

	buff = (int *)mlx_get_data_addr(img, &coord[0], &coord[1], &endian);
	coord[1] /= 4;
	idx[0] = 0;
	while (idx[0] < TILE_SIZE)
	{
		idx[1] = 0;
		while (idx[1] < TILE_SIZE)
		{
			if (sqrt((TILE_SIZE / 2 - idx[1]) * (TILE_SIZE / 2 - idx[1]) + (TILE_SIZE / 2 - idx[0]) * (TILE_SIZE / 2 - idx[0])) < rad)
				buff[idx[0] * coord[1] + idx[1]] = color;
			else
				buff[idx[0] * coord[1] + idx[1]] = f_color;
			idx[1]++;
		}
		idx[0]++;
	}
}

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
	cub->mlx.player_dot = mlx_xpm_file_to_image(cub->mlx.mlx, "./textures/red_dot_32x32.xpm", &tmp, &tmp);

	cub->mlx.floor = mlx_new_image(cub->mlx.mlx, TILE_SIZE, TILE_SIZE);
	mlx_change_image_color(cub->mlx.floor, cub->params.f_color);
	cub->mlx.ceiling = mlx_new_image(cub->mlx.mlx, TILE_SIZE, TILE_SIZE);
	mlx_change_image_color(cub->mlx.ceiling, cub->params.c_color);
	// cub->mlx.space = mlx_new_image(cub->mlx.mlx, TILE_SIZE, TILE_SIZE);
	// mlx_change_image_color(cub->mlx.space, 0x000000);
	// cub->mlx.player_dot = mlx_new_image(cub->mlx.mlx, TILE_SIZE, TILE_SIZE);
	// mlx_change_player_color(cub->mlx.player_dot, rgb_to_int(217, 56, 62), cub->params.f_color);


	// if (!cub->mlx.north)
	return (0);
}
