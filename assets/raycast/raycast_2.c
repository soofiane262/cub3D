/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 23:39:06 by kid-bouh          #+#    #+#             */
/*   Updated: 2022/09/08 23:40:12 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

static void	choose_nearest_hit_2(t_ray *ray, t_tmp_ray hor, t_tmp_ray ver)
{
	ray->wall_distance = fmin(ver.wall_distance, hor.wall_distance);
	ray->wall_hit_x = fma(ver.wall_hit_x,
			(ver.wall_distance < hor.wall_distance),
			(ver.wall_distance >= hor.wall_distance) * hor.wall_hit_x);
	ray->wall_hit_y = fma(ver.wall_hit_y,
			(ver.wall_distance < hor.wall_distance),
			(ver.wall_distance >= hor.wall_distance) * hor.wall_hit_y);
	if (hor.wall_distance < ver.wall_distance && sin(ray->angle) > 0.0)
		ray->wall_orientation = 'N';
	else if (hor.wall_distance < ver.wall_distance && sin(ray->angle) < 0.0)
		ray->wall_orientation = 'S';
	else if (hor.wall_distance >= ver.wall_distance && cos(ray->angle) < 0.0)
		ray->wall_orientation = 'E';
	else
		ray->wall_orientation = 'W';
}

void	choose_nearest_hit(t_ray *ray, t_tmp_ray hor, t_tmp_ray ver)
{
	if (hor.door_exists || ver.door_exists)
	{
		ray->door_exists = true;
		ray->door_distance = fmin(ver.door_distance, hor.door_distance);
		ray->door_hit_x = fma(ver.door_hit_x,
				(ver.door_distance < hor.door_distance),
				(ver.door_distance >= hor.door_distance) * hor.door_hit_x);
		ray->door_hit_y = fma(ver.door_hit_y,
				(ver.door_distance < hor.door_distance),
				(ver.door_distance >= hor.door_distance) * hor.door_hit_y);
		if (hor.door_distance < ver.door_distance && sin(ray->angle) > 0.0)
		ray->door_orientation = 'N';
		else if (hor.door_distance < ver.door_distance && sin(ray->angle) < 0.0)
			ray->door_orientation = 'S';
		else if (hor.door_distance >= ver.door_distance
			&& cos(ray->angle) < 0.0)
			ray->door_orientation = 'E';
		else
			ray->door_orientation = 'W';
	}
	else
		ray->door_exists = false;
	choose_nearest_hit_2(ray, hor, ver);
}
