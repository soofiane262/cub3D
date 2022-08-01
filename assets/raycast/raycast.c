/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 16:50:43 by sel-mars          #+#    #+#             */
/*   Updated: 2022/08/01 19:02:38 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

#include <stdio.h>

t_ray	*raycast(t_cub *cub)
{
	int			i;
	int			j;
	bool		wall_found;
	double		ray_angle;
	int			next_x;
	int			next_y;
	t_tmp_ray	tmp[2];
	t_ray		*ray;
	t_ray		*ray_head;

	ray_angle = cub->player.rotation - (FOV * M_PI / 360);
	// ray_angle = cub->player.rotation;
	ray = NULL;
	ray_head = NULL;
	ray = (t_ray *)malloc(sizeof(t_ray));
	ray_head = ray;
	i = -1;
	// while (++i < 1)
	while (++i < NB_RAYS)
	{
		ray->next = NULL;
		ray_angle = fma(fmod(ray_angle, (2 * M_PI)), 1, (ray_angle < 0) * 2 * M_PI);
		ray->ray_angle = ray_angle;
		// tmp[0].wall_x = 0;
		// tmp[0].wall_y = 0;
		// tmp[1].wall_x = 0;
		// tmp[1].wall_y = 0;

		
printf("Angle == %dº\n\n", (int)round((ray_angle * 180 / M_PI)));



// puts("--Horizontally");
		//	Horizontally
		wall_found = false;
		tmp[0].distance = WIN_WIDTH * WIN_HEIGHT;
		tmp[0].y_intersept = fma(floor((cub->player.y_pos + TILE_SIZE / 2) / TILE_SIZE), TILE_SIZE, 
			(ray_angle > 0 && ray_angle < M_PI) * TILE_SIZE);
		tmp[0].x_intersept = (cub->player.x_pos + TILE_SIZE / 2) + (tmp[0].y_intersept - (cub->player.y_pos + TILE_SIZE / 2)) / tan(ray_angle);
		tmp[0].y_step = fma(TILE_SIZE, 1, (ray_angle >= M_PI && ray_angle <= 2 * M_PI) * -2 * TILE_SIZE);
		tmp[0].x_step = TILE_SIZE / tan(ray_angle);
		if ((ray_angle > M_PI_2 && ray_angle < 3 * M_PI_2 && tmp[0].x_step > 0) 
			|| ((ray_angle > 3 * M_PI_2 || ray_angle < M_PI_2) && tmp[0].x_step < 0))
			tmp[0].x_step *= -1;
		
		// tmp[0].x_step = fma(TILE_SIZE / tan(ray_angle), 
		// 	((ray_angle >= M_PI_2 && ray_angle <= 3 * M_PI_2 && TILE_SIZE / tan(ray_angle) > 0) 
		// 	|| (!(ray_angle >= M_PI_2 && ray_angle <= 3 * M_PI_2) && TILE_SIZE / tan(ray_angle) < 0)) * -1
		// 	, 0);

// printf("Horizontal x_step = %d\nHorizontal y_step = %d\n\n", tmp[0].x_step, tmp[0].y_step);


// 		if ((int)round((ray_angle * 180 / M_PI)) == 180)
// 		{
// 			tmp[0].wall_x = 0;
// 			tmp[0].wall_y = cub->player.y_pos + TILE_SIZE / 2;
// 		}
// 		else if (!(int)round((ray_angle * 180 / M_PI)) && (int)round((ray_angle * 180 / M_PI)) == 360)
// 		{
// 			tmp[0].wall_x = (cub->map.width - 1) * TILE_SIZE;
// 			tmp[0].wall_y = cub->player.y_pos + TILE_SIZE / 2;
// 		}
// 		else
// 		{
			next_x = tmp[0].x_intersept;
			next_y = tmp[0].y_intersept;
			if (ray_angle > M_PI && ray_angle < 2 * M_PI)
				next_y--;
// puts("--Horizontally");
			// puts("Before");
			while ((int)round((ray_angle * 180 / M_PI))
				&& (int)round((ray_angle * 180 / M_PI)) != 180
				&& (int)round((ray_angle * 180 / M_PI)) != 360
				&& next_y >= 0 && next_y < (cub->map.height - 1) * TILE_SIZE
				&& next_x >= 0 && next_x < (cub->map.width - 1) * TILE_SIZE)
			{
				if (!tmp[0].x_step && !tmp[0].y_step)
					break ;
				// printf("Max\t%d - %d\nActual\t%d - %d\n\n", (cub->map.height - 2) * TILE_SIZE, (cub->map.width - 2) * TILE_SIZE, next_y, next_x);

				if (cub->map.map[(int)floor(next_y / TILE_SIZE)][(int)floor(next_x / TILE_SIZE)] != '0')
				{
					wall_found = true;
					tmp[0].wall_y = next_y;
					tmp[0].wall_x = next_x;
					tmp[0].distance = hypot((next_y - cub->player.y_pos + TILE_SIZE / 2), (next_x - cub->player.x_pos + TILE_SIZE / 2));
					break ;
				}
			puts("H Loop");
				next_x += tmp[0].x_step;
				next_y += tmp[0].y_step;
			}
// puts("--Horizontally");
			// puts("After");
// 		}



// puts("--Vertically");
		//	Vertically
		wall_found = false;
		tmp[1].distance = WIN_WIDTH * WIN_HEIGHT;
		tmp[1].x_intersept = fma(floor((cub->player.x_pos + TILE_SIZE / 2) / TILE_SIZE), TILE_SIZE, 
			(!(ray_angle > M_PI_2 && ray_angle < 3 * M_PI_2)) * TILE_SIZE);
		tmp[1].y_intersept = (cub->player.y_pos + TILE_SIZE / 2) + (tmp[1].x_intersept - (cub->player.x_pos + TILE_SIZE / 2)) * tan(ray_angle);
		tmp[1].x_step = fma(TILE_SIZE, 1, (ray_angle > M_PI_2 && ray_angle < 3 * M_PI_2) * -2 * TILE_SIZE);
		tmp[1].y_step = TILE_SIZE * tan(ray_angle);
		if ((ray_angle > M_PI && tmp[1].y_step > 0) 
			|| (ray_angle < M_PI && tmp[1].y_step < 0))
			tmp[1].y_step *= -1;
		
		
		// tmp[1].y_step = fma(TILE_SIZE * tan(ray_angle), 
		// 	((ray_angle > M_PI && ray_angle < 2 * M_PI && TILE_SIZE / tan(ray_angle) > 0) 
		// 	|| (ray_angle < M_PI && TILE_SIZE / tan(ray_angle) < 0)) * -1
		// 	, 0);
		
// printf("Vertical x_step = %d\nVertical y_step = %d\n\n", tmp[1].x_step, tmp[1].y_step);
// exit(0);
		
		// if ((int)round((ray_angle * 180 / M_PI)) == 180)
		// {
		// 	tmp[1].wall_x = 0;
		// 	tmp[1].wall_y = cub->player.y_pos + TILE_SIZE / 2;
		// }
		// else if (!(int)round((ray_angle * 180 / M_PI)) && (int)round((ray_angle * 180 / M_PI)) == 360)
		// {
		// 	tmp[1].wall_x = (cub->map.width - 1) * TILE_SIZE;
		// 	tmp[1].wall_y = cub->player.y_pos + TILE_SIZE / 2;
		// }
		// else
		// {
			next_x = tmp[1].x_intersept;
			next_y = tmp[1].y_intersept;
			if (ray_angle > M_PI_2 && ray_angle < 3 * M_PI_2)
				next_x--;
// puts("--Vertically");
			// puts("Before");
			while ((int)round((ray_angle * 180 / M_PI)) != 90
				&& (int)round((ray_angle * 180 / M_PI)) != 270
				&& next_y >= 0 && next_y < (cub->map.height - 1) * TILE_SIZE
				&& next_x >= 0 && next_x < (cub->map.width - 1) * TILE_SIZE)
			{
				if (!tmp[1].x_step && !tmp[1].y_step)
					break ;
				// printf("Max\t%d - %d\nActual\t%d - %d\n\n", (cub->map.height - 2) * TILE_SIZE, (cub->map.width - 2) * TILE_SIZE, next_y, next_x);

				if (cub->map.map[(int)floor(next_y / TILE_SIZE)][(int)floor(next_x / TILE_SIZE)] != '0')
				{
					wall_found = true;
					tmp[1].wall_y = next_y;
					tmp[1].wall_x = next_x;
					tmp[1].distance = hypot((next_y - cub->player.y_pos + TILE_SIZE / 2), (next_x - cub->player.x_pos + TILE_SIZE / 2));
					break ;
				}
				next_x += tmp[1].x_step;
				next_y += tmp[1].y_step;


			puts("V Loop");

// puts("--Vertically");
// printf("Vertical next_x = %d\nVertical next_y = %d\n\n", next_x, next_y);
// exit(0);

			}
			puts("End");
		// }




		j = 0;
		if (tmp[0].distance > tmp[1].distance)
			j = 1;
		

		ray->distance = tmp[j].distance;
		ray->wall_x = tmp[j].wall_x;
		ray->wall_y = tmp[j].wall_y;
		ray->hit_is_v = (j == 1);


printf("distance\t==\t%d\nwall_x\t\t==\t%d\nwall_y\t\t==\t%d\n\n", ray->distance, ray->wall_x, ray->wall_y);


		if (i < NB_RAYS - 1)
			ray->next = (t_ray *)malloc(sizeof(t_ray));
		ray = ray->next;
		ray_angle += ((((double)FOV * M_PI) / (180 * NB_RAYS)));
	}
	return (ray_head);
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
