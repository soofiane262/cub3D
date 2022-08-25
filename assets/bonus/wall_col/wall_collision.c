/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_collision.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 18:36:30 by sel-mars          #+#    #+#             */
/*   Updated: 2022/08/25 16:49:47 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

int	check_wall_collision(int new_x, int new_y, t_cub *cub)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	if (cub->player.mvt == W)
	{
		x = floor((new_x + PLAYER_SIZE / 2 + MOVE_SPEED * cos(cub->player.rotation)) / TILE_SIZE);
		y = floor((new_y + PLAYER_SIZE / 2 + MOVE_SPEED * sin(cub->player.rotation)) / TILE_SIZE);
	}
	else if (cub->player.mvt == S)
	{
		x = floor((new_x + PLAYER_SIZE / 2 - MOVE_SPEED * cos(cub->player.rotation)) / TILE_SIZE);
		y = floor((new_y + PLAYER_SIZE / 2 - MOVE_SPEED * sin(cub->player.rotation)) / TILE_SIZE);
	}
	else if (cub->player.mvt == A)
	{
		x = floor((new_x + PLAYER_SIZE / 2 + MOVE_SPEED * cos(M_PI_2 - cub->player.rotation)) / TILE_SIZE);
		y = floor((new_y + PLAYER_SIZE / 2 - MOVE_SPEED * sin(M_PI_2 - cub->player.rotation)) / TILE_SIZE);
	}
	else if (cub->player.mvt == D)
	{
		x = floor((new_x + PLAYER_SIZE / 2 - MOVE_SPEED * cos(M_PI_2 - cub->player.rotation)) / TILE_SIZE);
		y = floor((new_y + PLAYER_SIZE / 2 + MOVE_SPEED * sin(M_PI_2 - cub->player.rotation)) / TILE_SIZE);
	}
	if (cub->map.map[y][x] != '0')
		return (1);
	return (0);
}

