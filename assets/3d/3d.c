/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 17:34:13 by sel-mars          #+#    #+#             */
/*   Updated: 2022/08/09 12:05:21 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

#include <stdio.h>

void	mlx_put_strip(int start[2], int end[2], int data[4], t_cub *cub)
{
	int	i[2];
	// int	j;

	i[0] = 0;
		// j = 0;
	while (i[0] < WIN_HEIGHT)
	{
		i[1] = start[1];
		while (i[1] < end[1])
		{
			if (i[0] >= start[0] && i[0] <= end[0])
			{
				// cub->mlx.master_data[i[0] * data[1] + i[1]] = argb_to_int(data[3], 255, 187, 69);
				if (cub->ray->orientation == 'N')
					cub->mlx.master_data[i[0] * data[1] + i[1]] = argb_to_int(data[3], 255, 187, 69);
				else if (cub->ray->orientation == 'S')
					cub->mlx.master_data[i[0] * data[1] + i[1]] = argb_to_int(data[3], 52, 52, 235);
				else if (cub->ray->orientation == 'E')
					cub->mlx.master_data[i[0] * data[1] + i[1]] = argb_to_int(data[3], 192, 57, 196);
				else if (cub->ray->orientation == 'W')
					cub->mlx.master_data[i[0] * data[1] + i[1]] = argb_to_int(data[3], 47, 194, 78);
			}

// ft_putendl_fd("check", 1);

				
			// if (i[0] >= start[0] && i[0] <= end[0]
			// 	&& (cub->ray->orientation == 'N' || cub->ray->orientation == 'S'))
			// {
			// 		cub->mlx.master_data[i[0] * data[1] + i[1]] = cub->mlx.wall_no_data
			// 		[0];
			// 			// ft_putnbr_fd((cub->ray->wall_y / TILE_SIZE) * TILE_SIZE, 1);
			// 			// ft_putendl_fd("", 1);
			// }
			// else if (i[0] >= start[0] && i[0] <= end[0]
			// 	&& (cub->ray->orientation == 'E' || cub->ray->orientation == 'W'))
			// {
			// 		cub->mlx.master_data[i[0] * data[1] + i[1]] = cub->mlx.wall_ea_data
			// 		[0];
			// 			// ft_putnbr_fd((cub->ray->wall_y / TILE_SIZE) * TILE_SIZE, 1);
			// 			// ft_putendl_fd("", 1);
			// }

			else if (i[0] <= WIN_HEIGHT / 2)
				cub->mlx.master_data[i[0] * data[1] + i[1]] = cub->params.c_color;
			else
				cub->mlx.master_data[i[0] * data[1] + i[1]] = cub->params.f_color;
			i[1]++;
		}
		i[0]++;
	}
}

// void	mlx_put_rectangle(int x_start, int y_start, int x_end, int y_end, int color, t_mlx mlx)
// {
// 	int	i;
// 	int	j;

// 	i = y_start;
// 	while (i < y_end)
// 	{
// 		j = x_start;
// 		while (j < x_end)
// 		{
// 			if (i >= 0 && j >= 0)
// 				mlx_pixel_put(mlx.mlx, mlx.win, j, i, color);
// 			j++;
// 		}
// 		i++;
// 	}
// }

void	make_master(t_cub *cub)
{
	int 	i;
	t_ray	*head;
	int		start[2];
	int		end[2];
	double	rayCorrectDistance;



	int		data[4];
	cub->mlx.master_data = (int *)mlx_get_data_addr(cub->mlx.master, &data[0], &data[1], &data[2]);
	data[1] /= 4;


	head = cub->ray;
	i = 0;
	while (cub->ray)
	{
		rayCorrectDistance = cub->ray->distance * cos(cub->ray->ray_angle - cub->player.rotation);
		end[0] = ((float)TILE_SIZE / rayCorrectDistance) * (WIN_WIDTH / 2) / fabs(tan(FOV * M_PI / 360));
		start[0] = (WIN_HEIGHT / 2) - (end[0] / 2);
		end[0] += start[0];
		start[1] = i * STRIP_WIDTH;
		end[1] = start[1] + STRIP_WIDTH;
		data[3] = (rayCorrectDistance / 10) * (rayCorrectDistance / 10 <= 150) + (rayCorrectDistance / 10 > 150) * 150;
		mlx_put_strip(start, end, data, cub);
		i++;
		cub->ray = cub->ray->next;
	}
	cub->ray = head;
}

void	ft_3d(t_cub *cub)
{
	raycast(cub);
	make_master(cub);
	ray_free(cub);
}
