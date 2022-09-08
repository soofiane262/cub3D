/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_hit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 16:28:15 by sel-mars          #+#    #+#             */
/*   Updated: 2022/09/08 20:47:30 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static t_tmp_ray	init_vertical_tmp_ray(t_cub *cub, t_ray *ray)
{
	t_tmp_ray	ret;

	ret.wall_distance = WIN_WIDTH * WIN_HEIGHT;
	ret.x_intersept = fma(floor((cub->player.x_pos + TILE_SIZE / 2)
				/ TILE_SIZE), TILE_SIZE,
			(cos(ray->angle) > 0.0) * TILE_SIZE);
	ret.y_intersept = (cub->player.y_pos + TILE_SIZE / 2)
		+ (ret.x_intersept - (cub->player.x_pos + TILE_SIZE / 2))
		* tan(ray->angle);
	ret.x_step = fma(TILE_SIZE, 1, (cos(ray->angle) < 0.0)
			* -2 * TILE_SIZE);
	ret.y_step = TILE_SIZE * tan(ray->angle);
	if ((sin(ray->angle) < 0.0 && ret.y_step > 0)
		|| (sin(ray->angle) > 0.0 && ret.y_step < 0))
		ret.y_step *= -1;
	return (ret);
}

static t_tmp_ray	init_horizontal_tmp_ray(t_cub *cub, t_ray *ray)
{
	t_tmp_ray	ret;

	ret.wall_distance = WIN_WIDTH * WIN_HEIGHT;
	ret.y_intersept = fma(floor((cub->player.y_pos + TILE_SIZE / 2)
				/ TILE_SIZE), TILE_SIZE,
			(sin(ray->angle) > 0.0) * TILE_SIZE);
	ret.x_intersept = (cub->player.x_pos + TILE_SIZE / 2)
		+ (ret.y_intersept - (cub->player.y_pos + TILE_SIZE / 2))
		/ tan(ray->angle);
	ret.y_step = fma(TILE_SIZE, 1, (sin(ray->angle) < 0.0)
			* -2 * TILE_SIZE);
	ret.x_step = TILE_SIZE / tan(ray->angle);
	if ((cos(ray->angle) < 0.0 && ret.x_step > 0)
		|| (cos(ray->angle) > 0.0 && ret.x_step < 0))
		ret.x_step *= -1;
	return (ret);
}

static t_tmp_ray	init_tmp_ray(t_cub *cub, t_ray *ray, char state)
{
	t_tmp_ray	ret;

	if (state == 'V')
		ret = init_vertical_tmp_ray(cub, ray);
	else
		ret = init_horizontal_tmp_ray(cub, ray);
	ret.door_exists = false;
	ret.door_distance = WIN_WIDTH * WIN_HEIGHT;
	ret.door_hit_x = WIN_WIDTH * WIN_HEIGHT;
	ret.door_hit_y = WIN_WIDTH * WIN_HEIGHT;
	return (ret);
}

t_tmp_ray	vertical_hit_wall(t_tmp_ray ret, t_cub *cub)
{
	ret.wall_hit_y = ret.y_intersept;
	ret.wall_hit_x = ret.x_intersept;
	ret.wall_distance = hypot((cub->player.y_pos + TILE_SIZE / 2
				- ret.y_intersept), (cub->player.x_pos + TILE_SIZE / 2
				- ret.x_intersept));
	return (ret);
}

t_tmp_ray	vertical_hit_door(t_tmp_ray ret, t_cub *cub)
{
	ret.door_exists = true;
	ret.door_hit_y = ret.y_intersept;
	ret.door_hit_x = ret.x_intersept;
	ret.door_distance = hypot((cub->player.y_pos + TILE_SIZE / 2
				- ret.y_intersept), (cub->player.x_pos + TILE_SIZE / 2
				- ret.x_intersept));
	return (ret);
}

t_tmp_ray	vertical_hit(t_cub *cub, t_ray *ray, float diff[2])
{
	t_tmp_ray	ret;

	ret = init_tmp_ray(cub, ray, 'V');
	while (ret.y_intersept >= 0 && ret.x_intersept >= 0
		&& ret.y_intersept < cub->map.height * TILE_SIZE - 1
		&& ret.x_intersept < cub->map.width * TILE_SIZE - 1)
	{
		if ((!ret.x_step && !ret.y_step) || sin(ray->angle) == 1.0
			|| sin(ray->angle) == -1.0)
			break ;
		if (!ret.door_exists
			&& cub->map.map[(int)((ret.y_intersept - diff[0]) / TILE_SIZE)]
				[(int)((ret.x_intersept - diff[1]) / TILE_SIZE)] == 'D')
			ret = vertical_hit_door(ret, cub);
		else if (cub->map.map[(int)((ret.y_intersept - diff[0]) / TILE_SIZE)]
			[(int)((ret.x_intersept - diff[1]) / TILE_SIZE)] != '0')
		{
			ret = vertical_hit_wall(ret, cub);
			break ;
		}
		ret.x_intersept += ret.x_step;
		ret.y_intersept += ret.y_step;
	}
	return (ret);
}

t_tmp_ray	horizontal_hit(t_cub *cub, t_ray *ray, float diff[2])
{
	t_tmp_ray	ret;

	ret = init_tmp_ray(cub, ray, 'H');
	while (ret.y_intersept >= 0 && ret.x_intersept >= 0
		&& ret.y_intersept < cub->map.height * TILE_SIZE - 1
		&& ret.x_intersept < cub->map.width * TILE_SIZE - 1)
	{
		if ((!ret.x_step && !ret.y_step)
			|| cos(ray->angle) == 1.0
			|| cos(ray->angle) == -1.0)
			break ;
		if (!ret.door_exists
			&& cub->map.map[(int)((ret.y_intersept - diff[0]) / TILE_SIZE)]
				[(int)((ret.x_intersept - diff[1]) / TILE_SIZE)] == 'D')
		{
			ret.door_exists = true;
			ret.door_hit_y = ret.y_intersept;
			ret.door_hit_x = ret.x_intersept;
			ret.door_distance = hypot((cub->player.y_pos + TILE_SIZE / 2
						- ret.y_intersept), (cub->player.x_pos + TILE_SIZE / 2
						- ret.x_intersept));
		}
		else if (cub->map.map[(int)((ret.y_intersept - diff[0]) / TILE_SIZE)]
				[(int)((ret.x_intersept - diff[1]) / TILE_SIZE)] != '0')
		{
			ret.wall_hit_y = ret.y_intersept;
			ret.wall_hit_x = ret.x_intersept;
			ret.wall_distance = hypot((cub->player.y_pos + TILE_SIZE / 2
						- ret.y_intersept), (cub->player.x_pos + TILE_SIZE / 2
						- ret.x_intersept));
			break ;
		}
		ret.x_intersept += ret.x_step;
		ret.y_intersept += ret.y_step;
	}
	return (ret);
}
