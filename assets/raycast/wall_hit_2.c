/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_hit_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 22:43:34 by kid-bouh          #+#    #+#             */
/*   Updated: 2022/09/08 22:58:36 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

t_tmp_ray	horizontal_hit_wall(t_tmp_ray ret, t_cub *cub)
{
	ret.wall_hit_y = ret.y_intersept;
	ret.wall_hit_x = ret.x_intersept;
	ret.wall_distance = hypot((cub->player.y_pos + TILE_SIZE / 2
				- ret.y_intersept), (cub->player.x_pos + TILE_SIZE / 2
				- ret.x_intersept));
	return (ret);
}

t_tmp_ray	horizontal_hit_door(t_tmp_ray ret, t_cub *cub)
{
	ret.door_exists = true;
	ret.door_hit_y = ret.y_intersept;
	ret.door_hit_x = ret.x_intersept;
	ret.door_distance = hypot((cub->player.y_pos + TILE_SIZE / 2
				- ret.y_intersept), (cub->player.x_pos + TILE_SIZE / 2
				- ret.x_intersept));
	return (ret);
}
