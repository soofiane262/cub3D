/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 15:28:23 by sel-mars          #+#    #+#             */
/*   Updated: 2022/08/27 18:21:52 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	paint_horizontal_wall_pixel(t_cub_bonus *cub_bonus, float start[2],
	float end[2], int idx[2])
{
	int	dx;
	int	dy;

	if (cub_bonus->cub->ray->wall_orientation == 'N')
	{
		dx = ((int)cub_bonus->cub->ray->wall_hit_x % TILE_SIZE)
			* ((float)cub_bonus->cub->mlx.wall_no_side / TILE_SIZE);
		dy = (idx[0] - start[0])
			* ((float)cub_bonus->cub->mlx.wall_no_side / (end[0] - start[0]));
		cub_bonus->cub->mlx.master_data[idx[0] * WIN_WIDTH + idx[1]]
			= cub_bonus->cub->mlx.wall_no_data[dy * cub_bonus->cub->mlx.wall_no_side + dx];
	}
	else
	{
		dx = ((int)cub_bonus->cub->ray->wall_hit_x % TILE_SIZE)
			* ((float)cub_bonus->cub->mlx.wall_so_side / TILE_SIZE);
		dy = (idx[0] - start[0])
			* ((float)cub_bonus->cub->mlx.wall_so_side / (end[0] - start[0]));
		cub_bonus->cub->mlx.master_data[idx[0] * WIN_WIDTH + idx[1]]
			= cub_bonus->cub->mlx.wall_so_data[dy * cub_bonus->cub->mlx.wall_so_side + dx];
	}
}

static void	paint_vertical_wall_pixel(t_cub_bonus *cub_bonus, float start[2],
	float end[2], int idx[2])
{
	int	dx;
	int	dy;

	if (cub_bonus->cub->ray->wall_orientation == 'E')
	{
		dx = ((int)cub_bonus->cub->ray->wall_hit_y % TILE_SIZE)
			* ((float)cub_bonus->cub->mlx.wall_ea_side / TILE_SIZE);
		dy = (idx[0] - start[0])
			* ((float)cub_bonus->cub->mlx.wall_ea_side / (end[0] - start[0]));
		cub_bonus->cub->mlx.master_data[idx[0] * WIN_WIDTH + idx[1]]
			= cub_bonus->cub->mlx.wall_ea_data[dy * cub_bonus->cub->mlx.wall_ea_side + dx];
	}
	else
	{
		dx = ((int)cub_bonus->cub->ray->wall_hit_y % TILE_SIZE)
			* ((float)cub_bonus->cub->mlx.wall_we_side / TILE_SIZE);
		dy = (idx[0] - start[0])
			* ((float)cub_bonus->cub->mlx.wall_we_side / (end[0] - start[0]));
		cub_bonus->cub->mlx.master_data[idx[0] * WIN_WIDTH + idx[1]]
			= cub_bonus->cub->mlx.wall_we_data[dy * cub_bonus->cub->mlx.wall_we_side + dx];
	}
}

static void	paint_horizontal_door_pixel(t_cub_bonus *cub_bonus, float start[2],
	float end[2], int idx[2])
{
	int	dx;
	int	dy;
	int	i;

	i = 0;
	if (cub_bonus->cub->ray->door_distance < 2 *TILE_SIZE)
		i = 1;
	dx = ((int)cub_bonus->cub->ray->door_hit_x % TILE_SIZE)
		* ((float)cub_bonus->door.door_side / TILE_SIZE);
	dy = (idx[0] - start[0])
		* ((float)cub_bonus->door.door_side / (end[0] - start[0]));
	if (cub_bonus->door.door_data[i][dy * cub_bonus->door.door_side + dx]
		!= argb_to_int(255, 0, 0, 0))
		cub_bonus->cub->mlx.master_data[idx[0] * WIN_WIDTH + idx[1]]
			= cub_bonus->door.door_data[i][dy * cub_bonus->door.door_side + dx];
}

static void	paint_vertical_door_pixel(t_cub_bonus *cub_bonus, float start[2],
	float end[2], int idx[2])
{
	int	dx;
	int	dy;
	int	i;

	i = 0;
	if (cub_bonus->cub->ray->door_distance < 2 *TILE_SIZE)
		i = 1;
	dx = ((int)cub_bonus->cub->ray->door_hit_y % TILE_SIZE)
		* ((float)cub_bonus->door.door_side / TILE_SIZE);
	dy = (idx[0] - start[0])
		* ((float)cub_bonus->door.door_side / (end[0] - start[0]));
	if (cub_bonus->door.door_data[i][dy * cub_bonus->door.door_side + dx]
		!= argb_to_int(255, 0, 0, 0))
		cub_bonus->cub->mlx.master_data[idx[0] * WIN_WIDTH + idx[1]]
			= cub_bonus->door.door_data[i][dy * cub_bonus->door.door_side + dx];
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
				&& (cub_bonus->cub->ray->wall_orientation == 'N'
					|| cub_bonus->cub->ray->wall_orientation == 'S'))
				paint_horizontal_wall_pixel(cub_bonus, start, end, i);
			else if (i[0] >= (int)start[0] && i[0] <= (int)end[0])
				paint_vertical_wall_pixel(cub_bonus, start, end, i);
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

static void	paint_doors_in_master(t_cub_bonus *cub_bonus, int idx)
{
	int		i[2];
	float	start[2];
	float	end[2];
	double	ray_correct_distance;

	ray_correct_distance = cub_bonus->cub->ray->door_distance
		* cos(cub_bonus->cub->ray->angle - cub_bonus->cub->player.rotation);
	end[0] = ((float)TILE_SIZE / ray_correct_distance)
		* (WIN_WIDTH / 2) / fabs(tan(FOV * M_PI / 360));
	start[0] = (WIN_HEIGHT / 2) - (end[0] / 2);
	end[0] += start[0];
	start[1] = idx * STRIP_WIDTH;
	end[1] = start[1] + STRIP_WIDTH;
	i[0] = 0;
	while (i[0] < WIN_HEIGHT)
	{
		i[1] = (int)start[1];
		while (i[1] < (int)end[1])
		{
			if (i[0] >= (int)start[0] && i[0] <= (int)end[0]
				&& (cub_bonus->cub->ray->door_orientation == 'N'
				|| cub_bonus->cub->ray->door_orientation == 'S'))
				paint_horizontal_door_pixel(cub_bonus, start, end, i);
			else if (i[0] >= (int)start[0] && i[0] <= (int)end[0])
				paint_vertical_door_pixel(cub_bonus, start, end, i);
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
		ray_correct_distance = cub_bonus->cub->ray->wall_distance
			* cos(cub_bonus->cub->ray->angle - cub_bonus->cub->player.rotation);
		end[0] = ((float)TILE_SIZE / ray_correct_distance)
			* (WIN_WIDTH / 2) / fabs(tan(FOV * M_PI / 360));
		start[0] = (WIN_HEIGHT / 2) - (end[0] / 2);
		end[0] += start[0];
		start[1] = i * STRIP_WIDTH;
		end[1] = start[1] + STRIP_WIDTH;
		paint_master_strip(cub_bonus, start, end);
		if (cub_bonus->cub->ray->door_exists
			&& cub_bonus->cub->ray->door_distance <= cub_bonus->cub->ray->wall_distance)
			paint_doors_in_master(cub_bonus, i);
		i++;
		cub_bonus->cub->ray = cub_bonus->cub->ray->next;
	}
	cub_bonus->cub->ray = head;
}

void	paint_square_to_master(t_cub_bonus *cub_bonus, int coord[2], int size, int color)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = -1;
	y = coord[0];
	while (++i < size)
	{
		j = -1;
		x = coord[1];
		while (++j < size)
		{
			cub_bonus->cub->mlx.master_data[y * WIN_WIDTH + x] = color;
			x++;
		}
		y++;
	}
}

void	paint_gun_to_master(t_cub_bonus *cub_bonus)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = -1;
	y = WIN_HEIGHT - cub_bonus->gun.gun_height;
	while (++i < cub_bonus->gun.gun_height)
	{
		j = -1;
		x = WIN_WIDTH / 2 - cub_bonus->gun.gun_side / 2;
		while (++j < cub_bonus->gun.gun_side)
		{
			if (cub_bonus->gun.gun_data
				[cub_bonus->gun.idx]
				[i * cub_bonus->gun.gun_side + j]
				!= argb_to_int(255, 0, 0, 0))
			cub_bonus->cub->mlx.master_data[y * WIN_WIDTH + x]
				= cub_bonus->gun.gun_data
				[cub_bonus->gun.idx]
				[i * cub_bonus->gun.gun_side + j];
			x++;
		}
	y++;
	}
}

int	render_frame_bonus(t_cub_bonus *cub_bonus)
{
	update_all_bonus(cub_bonus);
	raycast(cub_bonus->cub);
	paint_master_bonus(cub_bonus);
	ray_free(cub_bonus->cub);
	paint_mini_map(cub_bonus);
	paint_gun_to_master(cub_bonus);
	mlx_clear_window(cub_bonus->cub->mlx.mlx, cub_bonus->cub->mlx.win);
	mlx_put_image_to_window(cub_bonus->cub->mlx.mlx, cub_bonus->cub->mlx.win, cub_bonus->cub->mlx.master, 0, 0);
	mlx_put_image_to_window(cub_bonus->cub->mlx.mlx, cub_bonus->cub->mlx.win, cub_bonus->mini_map.player,
		MINI_MAP_WIDTH / 2 + MINI_MAP_MARGIN - (MINI_MAP_PLAYER_SIZE / 2) - 2,
		MINI_MAP_HEIGHT / 2 + MINI_MAP_MARGIN - (MINI_MAP_PLAYER_SIZE / 2) - 2);
	return (0);
}
