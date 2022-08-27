/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 15:28:23 by sel-mars          #+#    #+#             */
/*   Updated: 2022/08/27 18:18:58 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	paint_horizontal_wall_pixel(t_cub *cub, float start[2],
	float end[2], int idx[2])
{
	int	dx;
	int	dy;

	if (cub->ray->wall_orientation == 'N')
	{
		dx = ((int)cub->ray->wall_hit_x % TILE_SIZE)
			* ((float)cub->mlx.wall_no_side / TILE_SIZE);
		dy = (idx[0] - start[0])
			* ((float)cub->mlx.wall_no_side / (end[0] - start[0]));
		cub->mlx.master_data[idx[0] * WIN_WIDTH + idx[1]]
			= cub->mlx.wall_no_data[dy * cub->mlx.wall_no_side + dx];
	}
	else
	{
		dx = ((int)cub->ray->wall_hit_x % TILE_SIZE)
			* ((float)cub->mlx.wall_so_side / TILE_SIZE);
		dy = (idx[0] - start[0])
			* ((float)cub->mlx.wall_so_side / (end[0] - start[0]));
		cub->mlx.master_data[idx[0] * WIN_WIDTH + idx[1]]
			= cub->mlx.wall_so_data[dy * cub->mlx.wall_so_side + dx];
	}
}

static void	paint_vertical_wall_pixel(t_cub *cub, float start[2],
	float end[2], int idx[2])
{
	int	dx;
	int	dy;

	if (cub->ray->wall_orientation == 'E')
	{
		dx = ((int)cub->ray->wall_hit_y % TILE_SIZE)
			* ((float)cub->mlx.wall_ea_side / TILE_SIZE);
		dy = (idx[0] - start[0])
			* ((float)cub->mlx.wall_ea_side / (end[0] - start[0]));
		cub->mlx.master_data[idx[0] * WIN_WIDTH + idx[1]]
			= cub->mlx.wall_ea_data[dy * cub->mlx.wall_ea_side + dx];
	}
	else
	{
		dx = ((int)cub->ray->wall_hit_y % TILE_SIZE)
			* ((float)cub->mlx.wall_we_side / TILE_SIZE);
		dy = (idx[0] - start[0])
			* ((float)cub->mlx.wall_we_side / (end[0] - start[0]));
		cub->mlx.master_data[idx[0] * WIN_WIDTH + idx[1]]
			= cub->mlx.wall_we_data[dy * cub->mlx.wall_we_side + dx];
	}
}

static void	paint_master_strip(t_cub *cub, float start[2], float end[2])
{
	int	i[2];

	i[0] = 0;
	while (i[0] < WIN_HEIGHT)
	{
		i[1] = (int)start[1];
		while (i[1] < (int)end[1])
		{
			if (i[0] >= (int)start[0] && i[0] <= (int)end[0]
				&& (cub->ray->wall_orientation == 'N'
					|| cub->ray->wall_orientation == 'S'))
				paint_horizontal_wall_pixel(cub, start, end, i);
			else if (i[0] >= (int)start[0] && i[0] <= (int)end[0])
				paint_vertical_wall_pixel(cub, start, end, i);
			else if (i[0] <= WIN_HEIGHT / 2)
				cub->mlx.master_data[i[0] * WIN_WIDTH + i[1]]
					= cub->params.c_color;
			else
				cub->mlx.master_data[i[0] * WIN_WIDTH + i[1]]
					= cub->params.f_color;
			i[1]++;
		}
		i[0]++;
	}
}

static void	paint_master(t_cub *cub)
{
	int		i;
	t_ray	*head;
	float	start[2];
	float	end[2];
	double	ray_correct_distance;

	cub->mlx.master_data = (int *)mlx_get_data_addr(cub->mlx.master,
			&i, &i, &i);
	i = 0;
	head = cub->ray;
	while (cub->ray)
	{
		ray_correct_distance = cub->ray->wall_distance
			* cos(cub->ray->angle - cub->player.rotation);
		end[0] = ((float)TILE_SIZE / ray_correct_distance)
			* (WIN_WIDTH / 2) / fabs(tan(FOV * M_PI / 360));
		start[0] = (WIN_HEIGHT / 2) - (end[0] / 2);
		end[0] += start[0];
		start[1] = i * STRIP_WIDTH;
		end[1] = start[1] + STRIP_WIDTH;
		paint_master_strip(cub, start, end);
		i++;
		cub->ray = cub->ray->next;
	}
	cub->ray = head;
}

int	render_frame(t_cub *cub)
{
	update_all(cub);
	raycast(cub);
	paint_master(cub);
	ray_free(cub);
	mlx_clear_window(cub->mlx.mlx, cub->mlx.win);
	mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.win, cub->mlx.master, 0, 0);
	return (0);
}
