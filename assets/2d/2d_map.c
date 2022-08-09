/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 12:25:51 by sel-mars          #+#    #+#             */
/*   Updated: 2022/08/09 11:58:34 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// void	mlx_put_line(int x_start, int y_start, double x_end, double y_end, int color,
// 	void *mlx, void *win)
// {
// 	int			i;
// 	int			j;
// 	double		m;
// 	double		n;

// 	if (y_start == (int)y_end || x_start == (int)x_end)
// 	{
// 		i = fmin(y_start, (int)y_end);
// 		while (i <= fmax(y_start, (int)y_end))
// 		{
// 			j = fmin(x_start, (int)x_end);
// 			while (j <= fmax(x_start, (int)x_end))
// 			{
// 				mlx_pixel_put(mlx, win, j, i, color);
// 				j++;
// 			}
// 			i++;
// 		}
// 		return ;
// 	}
// 	m = ((y_end - y_start) / (x_end - x_start));
// 	n = y_start - ((y_end - y_start) / (x_end - x_start)) * x_start;
// 	i = fmin(y_start, (int)y_end);
// 	while (i <= fmax(y_start, (int)y_end))
// 	{
// 		j = fmin(x_start, (int)x_end);
// 		while (j <= fmax(x_start, (int)x_end))
// 		{
// 			if (fabs((m * j + n - i)) <= 1)
// 				mlx_pixel_put(mlx, win, j, i, color);
// 			j++;
// 		}
// 		i++;
// 	}
// }

// void	mlx_put_rays(t_cub *cub)
// {
// 	int		i;
// 	t_ray	*ray_head;

// 	cub->ray = raycast(cub);
// 	ray_head = cub->ray;
// 	i = -1;
// 	while (++i < NB_RAYS)
// 	{
// 		mlx_put_line(cub->player.x_pos + TILE_SIZE / 2, cub->player.y_pos + TILE_SIZE / 2,
// 			cub->ray->wall_x, cub->ray->wall_y, argb_to_int(0, 217, 56, 62), cub->mlx.mlx, cub->mlx.win);
// 		cub->ray = cub->ray->next;
// 	}
// 	cub->ray = ray_head;
// 	ray_free(cub);
// }

// int	ft_2d_map(t_cub *cub)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < cub->map.height)
// 	{
// 		j = 0;
// 		while (j < cub->map.width)
// 		{
// 			if (cub->map.map[i][j] == '0')
// 				mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.win, 
// 					cub->mlx.floor, j * TILE_SIZE, i * TILE_SIZE);
// 			else if (cub->map.map[i][j] == '1')
// 				mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.win, 
// 					cub->mlx.north, j * TILE_SIZE, i * TILE_SIZE);
// 			j++;
// 		}
// 		i++;
// 	}
// 	mlx_put_rays(cub);
// 	mlx_put_image_to_window(cub->mlx.mlx, cub->tmp_2d.win,
// 		cub->tmp_2d.player, cub->player.x_pos + (TILE_SIZE - PLAYER_SIZE) / 2,
// 		cub->player.y_pos + (TILE_SIZE - PLAYER_SIZE) / 2);
// 	return (0);
// }

void	mlx_change_image_color(void *img, int color, int img_width, int img_height)
{
	int		idx[2];
	int		coord[2];
	int		endian;
	int		*buff;

	buff = (int *)mlx_get_data_addr(img, &coord[0], &coord[1], &endian);
	coord[1] /= 4;
	idx[0] = 0;
	while (idx[0] < img_height)
	{
		idx[1] = 0;
		while (idx[1] < img_width)
		{
			buff[idx[0] * coord[1] + idx[1]] = color;
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
	cub->mlx.wall_no = mlx_xpm_file_to_image(cub->mlx.mlx, cub->params.no_text, &tmp, &tmp);
	cub->mlx.wall_no_data = (int *)mlx_get_data_addr(cub->mlx.wall_no, &tmp, &cub->mlx.wall_line_bytes, &tmp);
	cub->mlx.wall_line_bytes /= 4;
	cub->mlx.wall_so = mlx_xpm_file_to_image(cub->mlx.mlx, cub->params.so_text, &tmp, &tmp);
	cub->mlx.wall_so_data = (int *)mlx_get_data_addr(cub->mlx.wall_so, &tmp, &tmp, &tmp);
	cub->mlx.wall_ea = mlx_xpm_file_to_image(cub->mlx.mlx, cub->params.ea_text, &tmp, &tmp);
	cub->mlx.wall_ea_data = (int *)mlx_get_data_addr(cub->mlx.wall_ea, &tmp, &tmp, &tmp);
	cub->mlx.wall_we = mlx_xpm_file_to_image(cub->mlx.mlx, cub->params.we_text, &tmp, &tmp);
	cub->mlx.wall_we_data = (int *)mlx_get_data_addr(cub->mlx.wall_we, &tmp, &tmp, &tmp);
	cub->mlx.master = mlx_new_image(cub->mlx.mlx, WIN_WIDTH, WIN_HEIGHT);
	// cub->mlx.master_data = (int *)mlx_get_data_addr(cub->mlx.master, &tmp, &tmp, &tmp);


	// cub->mini_map.background = mlx_new_image(cub->mlx.mlx, MINI_MAP_WIDTH, MINI_MAP_HEIGHT);
	// mlx_change_mini_map_bg_color(cub);

	cub->mini_map.floor = mlx_new_image(cub->mlx.mlx, MINI_MAP_TILE_SIZE, MINI_MAP_TILE_SIZE);
	mlx_change_image_color(cub->mini_map.floor, cub->params.f_color, MINI_MAP_TILE_SIZE, MINI_MAP_TILE_SIZE);
	cub->mini_map.wall = mlx_new_image(cub->mlx.mlx, MINI_MAP_TILE_SIZE, MINI_MAP_TILE_SIZE);
	mlx_change_image_color(cub->mini_map.wall, argb_to_int(0, 32, 35, 214), MINI_MAP_TILE_SIZE, MINI_MAP_TILE_SIZE);
	cub->mini_map.player = mlx_xpm_file_to_image(cub->mlx.mlx,
		"./textures/red_dot_4x4.xpm", &tmp, &tmp);
	
	

	return (0);
}
