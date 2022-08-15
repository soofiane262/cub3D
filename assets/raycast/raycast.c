/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 16:50:43 by sel-mars          #+#    #+#             */
/*   Updated: 2022/08/10 20:08:52 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_tmp_ray	vertical_wall_hit(t_cub *cub, t_ray *ray, float *diff_y, float *diff_x)
{
	float		next[2];
	t_tmp_ray	ret;

	ret.distance = WIN_WIDTH * WIN_HEIGHT;
	ret.x_intersept = fma(floor((cub->player.x_pos + TILE_SIZE / 2) / TILE_SIZE), TILE_SIZE, 
		(cos(ray->ray_angle) > 0.0) * TILE_SIZE);
	ret.y_intersept = (cub->player.y_pos + TILE_SIZE / 2) + (ret.x_intersept - (cub->player.x_pos + TILE_SIZE / 2)) * tan(ray->ray_angle);

	ret.x_step = fma(TILE_SIZE, 1, (cos(ray->ray_angle) < 0.0) * -2 * TILE_SIZE);
	ret.y_step = TILE_SIZE * tan(ray->ray_angle);
	if ((sin(ray->ray_angle) < 0.0 && ret.y_step > 0)
		|| (sin(ray->ray_angle) > 0.0 && ret.y_step < 0))
		ret.y_step *= -1;
	next[1] = ret.x_intersept;
	next[0] = ret.y_intersept;
	if (cos(ray->ray_angle) < 0.0)
		*diff_x += 0.0001;
	if (sin(ray->ray_angle) < 0.0)
		*diff_y += 0.0001;
	while (next[0] >= 0 && next[0] < cub->map.height * TILE_SIZE - 1
		&& next[1] >= 0 && next[1] < cub->map.width * TILE_SIZE - 1)
	{
		if ((!ret.x_step && !ret.y_step)
			|| sin(ray->ray_angle) == 1.0
			|| sin(ray->ray_angle) == -1.0)
			break ;
		if (cub->map.map[(int)((next[0] - *diff_y) / TILE_SIZE)][(int)((next[1] - *diff_x) / TILE_SIZE)] != '0')
		{
			ret.wall_y = next[0];
			ret.wall_x = next[1];
			ret.distance = hypot((cub->player.y_pos + TILE_SIZE / 2 - next[0]), (cub->player.x_pos + TILE_SIZE / 2 - next[1]));
			break ;
		}
		next[1] += ret.x_step;
		next[0] += ret.y_step;
	}
	return (ret);
}

t_tmp_ray	horizontal_wall_hit(t_cub *cub, t_ray *ray, float *diff_y, float *diff_x)
{
	float		diff[2];
	float		next[2];
	t_tmp_ray	ret;

	diff[0] = 0;
	diff[1] = 0;
	ret.distance = WIN_WIDTH * WIN_HEIGHT;
	ret.y_intersept = fma(floor((cub->player.y_pos + TILE_SIZE / 2) / TILE_SIZE), TILE_SIZE, 
		(sin(ray->ray_angle) > 0.0) * TILE_SIZE);
	ret.x_intersept = (cub->player.x_pos + TILE_SIZE / 2) + (ret.y_intersept - (cub->player.y_pos + TILE_SIZE / 2)) / tan(ray->ray_angle);
	ret.y_step = fma(TILE_SIZE, 1, (sin(ray->ray_angle) < 0.0) * -2 * TILE_SIZE);
	ret.x_step = TILE_SIZE / tan(ray->ray_angle);
	if ((cos(ray->ray_angle) < 0.0 && ret.x_step > 0)
		|| (cos(ray->ray_angle) > 0.0 && ret.x_step < 0))
		ret.x_step *= -1;
	next[1] = ret.x_intersept;
	next[0] = ret.y_intersept;
	if (cos(ray->ray_angle) < 0.0)
		*diff_x += 0.0001;
	if (sin(ray->ray_angle) < 0.0)
		*diff_y += 0.0001;
	while (next[0] >= 0 && next[0] < cub->map.height * TILE_SIZE - 1
		&& next[1] >= 0 && next[1] < cub->map.width * TILE_SIZE - 1)
	{
		if ((!ret.x_step && !ret.y_step)
			|| cos(ray->ray_angle) == 1.0
			|| cos(ray->ray_angle) == -1.0)
			break ;
		if (cub->map.map[(int)((next[0] - *diff_y) / TILE_SIZE)][(int)((next[1] - *diff_x) / TILE_SIZE)] != '0')
		{
			ret.wall_y = next[0];
			ret.wall_x = next[1];
			ret.distance = hypot((cub->player.y_pos + TILE_SIZE / 2 - next[0]), (cub->player.x_pos + TILE_SIZE / 2 - next[1]));
			break ;
		}
		next[1] += ret.x_step;
		next[0] += ret.y_step;
	}
	return (ret);
}

void	raycast(t_cub *cub)
{
	int			i;
	int			j;
	double		ray_angle;
	float		diff[2];
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
		tmp[0] = horizontal_wall_hit(cub, ray, &diff[0], &diff[1]);
		// Vertically
		tmp[1] = vertical_wall_hit(cub, ray, &diff[0], &diff[1]);
		j = 0;
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
