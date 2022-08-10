/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_collision.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 18:36:30 by sel-mars          #+#    #+#             */
/*   Updated: 2022/08/10 18:37:17 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	check_wall_collision(int new_x, int new_y, int key, t_cub *cub)
{
	int	x;
	int	y;

	x = 0;
	y= 0;
	if (key == W)
	{
		x = floor((new_x + PLAYER_SIZE / 2 + MOVE_SPEED * cos(cub->player.rotation)) / TILE_SIZE);
		y = floor((new_y + PLAYER_SIZE / 2 + MOVE_SPEED * sin(cub->player.rotation)) / TILE_SIZE);
	}
	else if (key == S)
	{
		x = floor((new_x + PLAYER_SIZE / 2 - MOVE_SPEED * cos(cub->player.rotation)) / TILE_SIZE);
		y = floor((new_y + PLAYER_SIZE / 2 - MOVE_SPEED * sin(cub->player.rotation)) / TILE_SIZE);
	}
	else if (key == A)
	{
		x = floor((new_x + PLAYER_SIZE / 2 + MOVE_SPEED * cos(M_PI_2 - cub->player.rotation)) / TILE_SIZE);
		y = floor((new_y + PLAYER_SIZE / 2 - MOVE_SPEED * sin(M_PI_2 - cub->player.rotation)) / TILE_SIZE);
	}
	else if (key == D)
	{
		x = floor((new_x + PLAYER_SIZE / 2 - MOVE_SPEED * cos(M_PI_2 - cub->player.rotation)) / TILE_SIZE);
		y = floor((new_y + PLAYER_SIZE / 2 + MOVE_SPEED * sin(M_PI_2 - cub->player.rotation)) / TILE_SIZE);
	}
	if (cub->map.map[y][x] == '1' || cub->map.map[y][x] == ' ')
		return (1);
	return (0);
}

