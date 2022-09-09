/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint_wall_door_pixel.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 01:23:44 by kid-bouh          #+#    #+#             */
/*   Updated: 2022/09/09 01:27:56 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	paint_horizontal_wall_pixel(t_cub_bonus *cub_bonus, float start[3],
	float end[3], int idx[2])
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
			= cub_bonus->cub->mlx.wall_no_data[dy
			* cub_bonus->cub->mlx.wall_no_side + dx];
	}
	else
	{
		dx = ((int)cub_bonus->cub->ray->wall_hit_x % TILE_SIZE)
			* ((float)cub_bonus->cub->mlx.wall_so_side / TILE_SIZE);
		dy = (idx[0] - start[0])
			* ((float)cub_bonus->cub->mlx.wall_so_side / (end[0] - start[0]));
		cub_bonus->cub->mlx.master_data[idx[0] * WIN_WIDTH + idx[1]]
			= cub_bonus->cub->mlx.wall_so_data[dy
			* cub_bonus->cub->mlx.wall_so_side + dx];
	}
}

void	paint_vertical_wall_pixel(t_cub_bonus *cub_bonus, float start[3],
	float end[3], int idx[2])
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
			= cub_bonus->cub->mlx.wall_ea_data[dy
			* cub_bonus->cub->mlx.wall_ea_side + dx];
	}
	else
	{
		dx = ((int)cub_bonus->cub->ray->wall_hit_y % TILE_SIZE)
			* ((float)cub_bonus->cub->mlx.wall_we_side / TILE_SIZE);
		dy = (idx[0] - start[0])
			* ((float)cub_bonus->cub->mlx.wall_we_side / (end[0] - start[0]));
		cub_bonus->cub->mlx.master_data[idx[0] * WIN_WIDTH + idx[1]]
			= cub_bonus->cub->mlx.wall_we_data[dy
			* cub_bonus->cub->mlx.wall_we_side + dx];
	}
}

void	paint_horizontal_door_pixel(t_cub_bonus *cub_bonus, float start,
	float end, int idx[2])
{
	int	dx;
	int	dy;
	int	i;

	i = 0;
	if (cub_bonus->cub->ray->door_distance < 2 * TILE_SIZE)
		i = 1;
	dx = ((int)cub_bonus->cub->ray->door_hit_x % TILE_SIZE)
		* ((float)cub_bonus->door.door_side / TILE_SIZE);
	dy = (idx[0] - start)
		* ((float)cub_bonus->door.door_side / (end - start));
	if (cub_bonus->door.door_data[i][dy * cub_bonus->door.door_side + dx]
		!= argb_to_int(255, 0, 0, 0))
		cub_bonus->cub->mlx.master_data[idx[0] * WIN_WIDTH + idx[1]]
			= cub_bonus->door.door_data[i][dy * cub_bonus->door.door_side + dx];
}

void	paint_vertical_door_pixel(t_cub_bonus *cub_bonus, float start,
	float end, int idx[2])
{
	int	dx;
	int	dy;
	int	i;

	i = 0;
	if (cub_bonus->cub->ray->door_distance < 2 * TILE_SIZE)
		i = 1;
	dx = ((int)cub_bonus->cub->ray->door_hit_y % TILE_SIZE)
		* ((float)cub_bonus->door.door_side / TILE_SIZE);
	dy = (idx[0] - start)
		* ((float)cub_bonus->door.door_side / (end - start));
	if (cub_bonus->door.door_data[i][dy * cub_bonus->door.door_side + dx]
		!= argb_to_int(255, 0, 0, 0))
		cub_bonus->cub->mlx.master_data[idx[0] * WIN_WIDTH + idx[1]]
			= cub_bonus->door.door_data[i][dy * cub_bonus->door.door_side + dx];
}
