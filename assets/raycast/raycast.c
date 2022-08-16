/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 16:50:43 by sel-mars          #+#    #+#             */
/*   Updated: 2022/08/16 16:46:00 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	choose_nearest_wall(t_ray *ray, t_tmp_ray hor, t_tmp_ray ver)
{
	if (hor.distance < ver.distance)
	{
		ray->distance = hor.distance;
		ray->wall_x = hor.wall_x;
		ray->wall_y = hor.wall_y;
		if (sin(ray->angle) > 0.0)
			ray->orientation = 'N';
		else
			ray->orientation = 'S';
	}
	else
	{
		ray->distance = ver.distance;
		ray->wall_x = ver.wall_x;
		ray->wall_y = ver.wall_y;
		if (cos(ray->angle) < 0.0)
			ray->orientation = 'E';
		else
			ray->orientation = 'W';
	}
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
		tmp[0] = horizontal_wall_hit(cub, ray, diff);
		tmp[1] = vertical_wall_hit(cub, ray, diff);
		choose_nearest_wall(ray, tmp[0], tmp[1]);
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
