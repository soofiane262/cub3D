/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 16:50:43 by sel-mars          #+#    #+#             */
/*   Updated: 2022/08/09 14:33:07 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

#include <stdio.h>

void	raycast(t_cub *cub)
{
	int			i;
	int			j;
	double		ray_angle;
	float		diff[2];
	float		next_x;
	float		next_y;
	t_tmp_ray	tmp[2];
	t_ray		*ray;
	t_ray		*ray_head;

	ray_angle = cub->player.rotation - (FOV * M_PI / 360);
	ray = (t_ray *)malloc(sizeof(t_ray));
	ray_head = ray;
	i = -1;
	while (++i < NB_RAYS)
	{
		diff[0] = 0;
		diff[1] = 0;
		ray->next = NULL;
		ray->ray_angle = ray_angle;
		// Horizontally
		tmp[0].distance = WIN_WIDTH * WIN_HEIGHT;

		// if (sin(ray->ray_angle) > 0)
		// 	tmp[0].y_intersept = TILE_SIZE * (int)(cub->player.y_pos / TILE_SIZE);
		// else
		// 	tmp[0].y_intersept = TILE_SIZE * (int)(cub->player.y_pos / TILE_SIZE) + TILE_SIZE;
		// tmp[0].x_intersept = cub->player.x_pos + (cub->player.y_pos - tmp[0].y_intersept) / tan(ray->ray_angle);

		tmp[0].y_intersept = fma(floor((cub->player.y_pos + TILE_SIZE / 2) / TILE_SIZE), TILE_SIZE, 
			(sin(ray->ray_angle) > 0.0) * TILE_SIZE);
		tmp[0].x_intersept = (cub->player.x_pos + TILE_SIZE / 2) + (tmp[0].y_intersept - (cub->player.y_pos + TILE_SIZE / 2)) / tan(ray->ray_angle);

		tmp[0].y_step = fma(TILE_SIZE, 1, (sin(ray->ray_angle) < 0.0) * -2 * TILE_SIZE);
		tmp[0].x_step = TILE_SIZE / tan(ray->ray_angle);
		if ((cos(ray->ray_angle) < 0.0 && tmp[0].x_step > 0)
			|| (cos(ray->ray_angle) > 0.0 && tmp[0].x_step < 0))
			tmp[0].x_step *= -1;
		next_x = tmp[0].x_intersept;
		next_y = tmp[0].y_intersept;
		if (cos(ray->ray_angle) < 0.0)
			diff[1] += 0.01;
		else if (cos(ray->ray_angle) > 0.0)
			diff[1] -= 0.01;
		if (sin(ray->ray_angle) < 0.0)
			diff[0] += 0.01;
		else if (sin(ray->ray_angle) > 0.0)
			diff[0] -= 0.01;
		while (next_y >= 0 && next_y < cub->map.height * TILE_SIZE - 1
			&& next_x >= 0 && next_x < cub->map.width * TILE_SIZE - 1)
		{
			if ((!tmp[0].x_step && !tmp[0].y_step)
				|| cos(ray->ray_angle) == 1.0
				|| cos(ray->ray_angle) == -1.0)
				break ;
			if (cub->map.map[(int)((next_y - diff[0]) / TILE_SIZE)][(int)((next_x - diff[1]) / TILE_SIZE)] != '0')
			{
				tmp[0].wall_y = next_y;
				tmp[0].wall_x = next_x;
				tmp[0].distance = hypot((cub->player.y_pos + TILE_SIZE / 2 - next_y), (cub->player.x_pos + TILE_SIZE / 2 - next_x));
				break ;
			}
			next_x += tmp[0].x_step;
			next_y += tmp[0].y_step;
		}
		// Vertically
		tmp[1].distance = WIN_WIDTH * WIN_HEIGHT;

		// if (cos(ray->ray_angle) > 0)
			// tmp[1].x_intersept = TILE_SIZE * (int)(cub->player.x_pos / TILE_SIZE) + TILE_SIZE;
		// else
			// tmp[1].x_intersept = TILE_SIZE * (int)(cub->player.x_pos / TILE_SIZE);
		// tmp[1].y_intersept = cub->player.y_pos + (tmp[1].x_intersept - cub->player.x_pos) * tan(ray->ray_angle);

		tmp[1].x_intersept = fma(floor((cub->player.x_pos + TILE_SIZE / 2) / TILE_SIZE), TILE_SIZE, 
			(cos(ray->ray_angle) > 0.0) * TILE_SIZE);
		tmp[1].y_intersept = (cub->player.y_pos + TILE_SIZE / 2) + (tmp[1].x_intersept - (cub->player.x_pos + TILE_SIZE / 2)) * tan(ray->ray_angle);

		tmp[1].x_step = fma(TILE_SIZE, 1, (cos(ray->ray_angle) < 0.0) * -2 * TILE_SIZE);
		tmp[1].y_step = TILE_SIZE * tan(ray->ray_angle);
		if ((sin(ray->ray_angle) < 0.0 && tmp[1].y_step > 0)
			|| (sin(ray->ray_angle) > 0.0 && tmp[1].y_step < 0))
			tmp[1].y_step *= -1;
		next_x = tmp[1].x_intersept;
		next_y = tmp[1].y_intersept;
		if (cos(ray->ray_angle) < 0.0)
			diff[1] += 0.01;
		else if (cos(ray->ray_angle) > 0.0)
			diff[1] -= 0.01;
		if (sin(ray->ray_angle) < 0.0)
			diff[0] += 0.01;
		else if (sin(ray->ray_angle) > 0.0)
			diff[0] -= 0.01;
		while (next_y >= 0 && next_y < cub->map.height * TILE_SIZE - 1
			&& next_x >= 0 && next_x < cub->map.width * TILE_SIZE - 1)
		{
			if ((!tmp[1].x_step && !tmp[1].y_step)
				|| sin(ray->ray_angle) == 1.0
				|| sin(ray->ray_angle) == -1.0)
				break ;
			if (cub->map.map[(int)((next_y - diff[0]) / TILE_SIZE)][(int)((next_x - diff[1]) / TILE_SIZE)] != '0')
			{
				tmp[1].wall_y = next_y;
				tmp[1].wall_x = next_x;
				tmp[1].distance = hypot((cub->player.y_pos + TILE_SIZE / 2 - next_y), (cub->player.x_pos + TILE_SIZE / 2 - next_x));
				break ;
			}
			next_x += tmp[1].x_step;
			next_y += tmp[1].y_step;
		}
		j = 0;
		// if (tmp[0].distance == tmp[1].distance && ray->previous && (ray->previous->orientation == 'E' || ray->previous->orientation == 'W'))
		// {
			// puts("check\n\n\n");
		// }
		if (tmp[0].distance > tmp[1].distance)
			j = 1;
		ray->distance = tmp[j].distance;
		ray->wall_x = tmp[j].wall_x;
		ray->wall_y = tmp[j].wall_y;
		if (!j && sin(ray->ray_angle) > 0.0)
			ray->orientation = 'N';
		else if (!j && sin(ray->ray_angle) < 0.0)
			ray->orientation = 'S';
		else if (j == 1 && cos(ray->ray_angle) < 0.0)
			ray->orientation = 'E';
		else
			ray->orientation = 'W';
		if (i < NB_RAYS - 1)
			ray->next = (t_ray *)malloc(sizeof(t_ray));
		ray = ray->next;
		ray_angle += ((((double)FOV * M_PI) / (180 * NB_RAYS)));
	}
	cub->ray = ray_head;
}

void	ray_free(t_cub *cub)
{
	t_ray	*tmp_ray;

	while (cub->ray)
	{
		tmp_ray = cub->ray;
		cub->ray = cub->ray->next;
		free(tmp_ray);
		tmp_ray = NULL;
	}
}
