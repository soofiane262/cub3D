/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 16:50:43 by sel-mars          #+#    #+#             */
/*   Updated: 2022/09/08 20:11:30 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	choose_nearest_hit(t_ray *ray, t_tmp_ray hor, t_tmp_ray ver)
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

static void	get_diff(t_ray *ray, float *diff_x, float *diff_y)
{
	*diff_y = 0;
	*diff_x = 0;
	if (cos(ray->angle) < 0.0)
		*diff_x += 0.001;
	if (sin(ray->angle) < 0.0)
		*diff_y += 0.001;
}

static double	increment_ray_angle(double angle)
{
	return (angle + (((double)FOV * M_PI) / (180 * NB_RAYS)));
}

void	raycast(t_cub *cub)
{
	int			i;
	float		diff[2];
	t_tmp_ray	tmp[2];
	t_ray		*ray;
	t_ray		*ray_head;

	ray = (t_ray *)malloc(sizeof(t_ray));
	ray_head = ray;
	ray->angle = cub->player.rotation - (FOV * M_PI / 360);
	i = -1;
	while (++i < NB_RAYS)
	{
		ray->next = NULL;
		get_diff(ray, &diff[1], &diff[0]);
		tmp[0] = horizontal_hit(cub, ray, diff);
		tmp[1] = vertical_hit(cub, ray, diff);
		choose_nearest_hit(ray, tmp[0], tmp[1]);
		if (i < NB_RAYS - 1)
		{
			ray->next = (t_ray *)malloc(sizeof(t_ray));
			ray->next->angle = increment_ray_angle(ray->angle);
		}
		ray = ray->next;
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
