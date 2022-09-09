/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint_master.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 11:23:24 by sel-mars          #+#    #+#             */
/*   Updated: 2022/09/09 01:32:54 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

static void	paint_master_strip_2(t_cub_bonus *cub_bonus,
	float start[3], float end[3], int i[2])
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
}

static void	paint_master_strip(t_cub_bonus *cub_bonus,
	float start[3], float end[3])
{
	int	i[2];

	i[0] = 0;
	while (i[0] < WIN_HEIGHT)
	{
		i[1] = (int)start[1];
		while (i[1] < (int)end[1])
		{
			paint_master_strip_2(cub_bonus, start, end, i);
			if (cub_bonus->cub->ray->door_exists
				&& cub_bonus->cub->ray->door_distance
				<= cub_bonus->cub->ray->wall_distance)
			{
				if (i[0] >= (int)start[2] && i[0] <= (int)end[2]
					&& (cub_bonus->cub->ray->door_orientation == 'N'
						|| cub_bonus->cub->ray->door_orientation == 'S'))
					paint_horizontal_door_pixel(cub_bonus, start[2], end[2], i);
				else if (i[0] >= (int)start[2] && i[0] <= (int)end[2])
					paint_vertical_door_pixel(cub_bonus, start[2], end[2], i);
			}
			i[1]++;
		}
		i[0]++;
	}
}

static void	paint_all_to_master(t_cub_bonus *cub_bonus, int idx)
{
	float	start[3];
	float	end[3];
	double	ray_correct_distance;

	ray_correct_distance = cub_bonus->cub->ray->wall_distance
		* cos(cub_bonus->cub->ray->angle - cub_bonus->cub->player.rotation);
	end[0] = ((float)TILE_SIZE / ray_correct_distance)
		* (WIN_WIDTH / 2) / fabs(tan(FOV * M_PI / 360));
	start[0] = (WIN_HEIGHT / 2) - (end[0] / 2);
	end[0] += start[0];
	start[1] = idx * STRIP_WIDTH;
	end[1] = start[1] + STRIP_WIDTH;
	if (cub_bonus->cub->ray->door_exists
		&& cub_bonus->cub->ray->door_distance
		<= cub_bonus->cub->ray->wall_distance)
	{
		ray_correct_distance = cub_bonus->cub->ray->door_distance
			* cos(cub_bonus->cub->ray->angle - cub_bonus->cub->player.rotation);
		end[2] = ((float)TILE_SIZE / ray_correct_distance)
			* (WIN_WIDTH / 2) / fabs(tan(FOV * M_PI / 360));
		start[2] = (WIN_HEIGHT / 2) - (end[2] / 2);
		end[2] += start[2];
	}
	paint_master_strip(cub_bonus, start, end);
}

void	paint_master_bonus(t_cub_bonus *cub_bonus)
{
	int		idx;
	t_ray	*head;

	cub_bonus->cub->mlx.master_data = (int *)mlx_get_data_addr(
			cub_bonus->cub->mlx.master, &idx, &idx, &idx);
	idx = 0;
	head = cub_bonus->cub->ray;
	while (cub_bonus->cub->ray)
	{
		paint_all_to_master(cub_bonus, idx);
		idx++;
		cub_bonus->cub->ray = cub_bonus->cub->ray->next;
	}
	cub_bonus->cub->ray = head;
}
