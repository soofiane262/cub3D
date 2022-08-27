/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 15:28:23 by sel-mars          #+#    #+#             */
/*   Updated: 2022/08/27 11:26:16 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	paint_horizontal_wall_pixel(t_cub_bonus *cub_bonus, float start[2],
	float end[2], int idx[2])
{
	int	dx;
	int	dy;

	if (cub_bonus->cub->ray->orientation == 'N')
	{
		dx = ((int)cub_bonus->cub->ray->hit_x % TILE_SIZE)
			* ((float)cub_bonus->cub->mlx.wall_no_side / TILE_SIZE);
		dy = (idx[0] - start[0])
			* ((float)cub_bonus->cub->mlx.wall_no_side / (end[0] - start[0]));
		cub_bonus->cub->mlx.master_data[idx[0] * WIN_WIDTH + idx[1]]
			= cub_bonus->cub->mlx.wall_no_data[dy * cub_bonus->cub->mlx.wall_no_side + dx];
	}
	else
	{
		dx = ((int)cub_bonus->cub->ray->hit_x % TILE_SIZE)
			* ((float)cub_bonus->cub->mlx.wall_so_side / TILE_SIZE);
		dy = (idx[0] - start[0])
			* ((float)cub_bonus->cub->mlx.wall_so_side / (end[0] - start[0]));
		cub_bonus->cub->mlx.master_data[idx[0] * WIN_WIDTH + idx[1]]
			= cub_bonus->cub->mlx.wall_so_data[dy * cub_bonus->cub->mlx.wall_so_side + dx];
	}
}

static void	paint_horizontal_pixel(t_cub_bonus *cub_bonus, float start[2],
	float end[2], int idx[2])
{
	int	dx;
	int	dy;
	int	i;

	if (cub_bonus->cub->ray->elt == '1')
		paint_horizontal_wall_pixel(cub_bonus, start, end, idx);
	else
	{
		if (cub_bonus->cub->ray->distance < TILE_SIZE)
			i = 1;
		else
			i = 0;
		dx = ((int)cub_bonus->cub->ray->hit_x % TILE_SIZE)
			* ((float)cub_bonus->door.door_side / TILE_SIZE);
		dy = (idx[0] - start[0])
			* ((float)cub_bonus->door.door_side / (end[0] - start[0]));
		cub_bonus->cub->mlx.master_data[idx[0] * WIN_WIDTH + idx[1]]
			= cub_bonus->door.door_data[i][dy * cub_bonus->door.door_side + dx];
	}
}

static void	paint_vertical_wall_pixel(t_cub_bonus *cub_bonus, float start[2],
	float end[2], int idx[2])
{
	int	dx;
	int	dy;

	if (cub_bonus->cub->ray->orientation == 'E')
	{
		dx = ((int)cub_bonus->cub->ray->hit_y % TILE_SIZE)
			* ((float)cub_bonus->cub->mlx.wall_ea_side / TILE_SIZE);
		dy = (idx[0] - start[0])
			* ((float)cub_bonus->cub->mlx.wall_ea_side / (end[0] - start[0]));
		cub_bonus->cub->mlx.master_data[idx[0] * WIN_WIDTH + idx[1]]
			= cub_bonus->cub->mlx.wall_ea_data[dy * cub_bonus->cub->mlx.wall_ea_side + dx];
	}
	else
	{
		dx = ((int)cub_bonus->cub->ray->hit_y % TILE_SIZE)
			* ((float)cub_bonus->cub->mlx.wall_we_side / TILE_SIZE);
		dy = (idx[0] - start[0])
			* ((float)cub_bonus->cub->mlx.wall_we_side / (end[0] - start[0]));
		cub_bonus->cub->mlx.master_data[idx[0] * WIN_WIDTH + idx[1]]
			= cub_bonus->cub->mlx.wall_we_data[dy * cub_bonus->cub->mlx.wall_we_side + dx];
	}
}

static void	paint_vertical_pixel(t_cub_bonus *cub_bonus, float start[2],
	float end[2], int idx[2])
{
	int	dx;
	int	dy;
	int	i;

	if (cub_bonus->cub->ray->elt == '1')
		paint_vertical_wall_pixel(cub_bonus, start, end, idx);
	else
	{
		if (cub_bonus->cub->ray->distance < TILE_SIZE)
			i = 1;
		else
			i = 0;
		dx = ((int)cub_bonus->cub->ray->hit_y % TILE_SIZE)
			* ((float)cub_bonus->door.door_side / TILE_SIZE);
		dy = (idx[0] - start[0])
			* ((float)cub_bonus->door.door_side / (end[0] - start[0]));
		cub_bonus->cub->mlx.master_data[idx[0] * WIN_WIDTH + idx[1]]
			=cub_bonus->door.door_data[i][dy * cub_bonus->door.door_side + dx];
	}
}

static void	paint_master_strip(t_cub_bonus *cub_bonus, float start[2], float end[2])
{
	int	i[2];

	i[0] = 0;
	while (i[0] < WIN_HEIGHT)
	{
		i[1] = (int)start[1];
		while (i[1] < (int)end[1])
		{
			if (i[0] >= (int)start[0] && i[0] <= (int)end[0]
				&& (cub_bonus->cub->ray->orientation == 'N'
					|| cub_bonus->cub->ray->orientation == 'S'))
				paint_horizontal_pixel(cub_bonus, start, end, i);
			else if (i[0] >= (int)start[0] && i[0] <= (int)end[0])
				paint_vertical_pixel(cub_bonus, start, end, i);
			else if (i[0] <= WIN_HEIGHT / 2)
				cub_bonus->cub->mlx.master_data[i[0] * WIN_WIDTH + i[1]]
					= cub_bonus->cub->params.c_color;
			else
				cub_bonus->cub->mlx.master_data[i[0] * WIN_WIDTH + i[1]]
					= cub_bonus->cub->params.f_color;
			i[1]++;
		}
		i[0]++;
	}
}

static void	paint_master_bonus(t_cub_bonus *cub_bonus)
{
	int		i;
	t_ray	*head;
	float	start[2];
	float	end[2];
	double	ray_correct_distance;

	cub_bonus->cub->mlx.master_data = (int *)mlx_get_data_addr(cub_bonus->cub->mlx.master,
			&i, &i, &i);
	i = 0;
	head = cub_bonus->cub->ray;
	while (cub_bonus->cub->ray)
	{
		ray_correct_distance = cub_bonus->cub->ray->distance
			* cos(cub_bonus->cub->ray->angle - cub_bonus->cub->player.rotation);
		end[0] = ((float)TILE_SIZE / ray_correct_distance)
			* (WIN_WIDTH / 2) / fabs(tan(FOV * M_PI / 360));
		start[0] = (WIN_HEIGHT / 2) - (end[0] / 2);
		end[0] += start[0];
		start[1] = i * STRIP_WIDTH;
		end[1] = start[1] + STRIP_WIDTH;
		paint_master_strip(cub_bonus, start, end);
		i++;
		cub_bonus->cub->ray = cub_bonus->cub->ray->next;
	}
	cub_bonus->cub->ray = head;
}

// void	put_2d(t_cub *cub)
// {
// 	t_map_2d	map_2d;
// 	int			i;
// 	int			j;

// 	map_2d.floor = mlx_new_image(cub->mlx.mlx, TILE_SIZE, TILE_SIZE);
// 	mlx_change_img_color(map_2d.floor, cub->params.f_color);
// 	map_2d.wall = mlx_new_image(cub->mlx.mlx, TILE_SIZE, TILE_SIZE);
// 	mlx_change_img_color(map_2d.wall, cub->params.c_color);
// 	map_2d.player = mlx_xpm_file_to_image(cub->mlx.mlx, "textures/red_dot_10x10.xpm", &i, &i);
// 	i = -1;
// 	while (++i < cub->map.height && i < WIN_HEIGHT)
// 	{
// 		j = -1;
// 		while (++j < cub->map.width && j < WIN_WIDTH)
// 		{
// 			if (cub->map.map[i][j] == '1')
// 				mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.win, map_2d.wall, j * TILE_SIZE, i * TILE_SIZE);
// 			else if (cub->map.map[i][j] == '0')
// 				mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.win, map_2d.floor, j * TILE_SIZE, i * TILE_SIZE);
// 		}
// 	}
// 	ft_putendl_fd("check\n\n", 1);
// 	// mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.win, map_2d.player, cub->player.x_pos, cub->player.y_pos);
// }

int	render_frame_bonus(t_cub_bonus *cub_bonus)
{
	update_all_bonus(cub_bonus);
	raycast(cub_bonus->cub);
	paint_master_bonus(cub_bonus);
	ray_free(cub_bonus->cub);
	mlx_clear_window(cub_bonus->cub->mlx.mlx, cub_bonus->cub->mlx.win);
	// ft_putendl_fd("start\n\n", 1);
	// put_2d(cub_bonus->cub);
	// ft_putendl_fd("end\n\n", 1);
	mlx_put_image_to_window(cub_bonus->cub->mlx.mlx, cub_bonus->cub->mlx.win, cub_bonus->cub->mlx.master, 0, 0);
	put_mini_map(cub_bonus);
	return (0);
}
