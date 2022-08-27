/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_hit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 16:28:15 by sel-mars          #+#    #+#             */
/*   Updated: 2022/08/27 11:23:29 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static t_tmp_ray	init_vertical_tmp_ray(t_cub *cub, t_ray *ray)
{
	t_tmp_ray	ret;

	ret.distance = WIN_WIDTH * WIN_HEIGHT;
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

	ret.distance = WIN_WIDTH * WIN_HEIGHT;
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
		if ((!ret.x_step && !ret.y_step)
			|| sin(ray->angle) == 1.0
			|| sin(ray->angle) == -1.0)
			break ;
		if (cub->map.map[(int)((ret.y_intersept - diff[0]) / TILE_SIZE)]
			[(int)((ret.x_intersept - diff[1]) / TILE_SIZE)] != '0')
		{
			if (cub->map.map[(int)((ret.y_intersept - diff[0]) / TILE_SIZE)]
				[(int)((ret.x_intersept - diff[1]) / TILE_SIZE)] == 'D')
				ret.elt = 'D';
			else
				ret.elt = '1';
			ret.hit_y = ret.y_intersept;
			ret.hit_x = ret.x_intersept;
			ret.distance = hypot((cub->player.y_pos + TILE_SIZE / 2
						- ret.y_intersept), (cub->player.x_pos + TILE_SIZE / 2
						- ret.x_intersept));
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
		if (cub->map.map[(int)((ret.y_intersept - diff[0]) / TILE_SIZE)]
				[(int)((ret.x_intersept - diff[1]) / TILE_SIZE)] != '0')
		{
			if (cub->map.map[(int)((ret.y_intersept - diff[0]) / TILE_SIZE)]
					[(int)((ret.x_intersept - diff[1]) / TILE_SIZE)] == 'D')
				ret.elt = 'D';
			else
				ret.elt = '1';
			ret.hit_y = ret.y_intersept;
			ret.hit_x = ret.x_intersept;
			ret.distance = hypot((cub->player.y_pos + TILE_SIZE / 2
						- ret.y_intersept), (cub->player.x_pos + TILE_SIZE / 2
						- ret.x_intersept));
			break ;
		}
		ret.x_intersept += ret.x_step;
		ret.y_intersept += ret.y_step;
	}
	return (ret);
}
