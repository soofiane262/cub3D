/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 19:35:24 by sel-mars          #+#    #+#             */
/*   Updated: 2022/08/25 18:23:40 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static float	update_player_y_pos(t_cub *cub)
{
	float	new_pos;

	if (cub->player.mvt == W)
		new_pos = cub->player.y_pos + MOVE_SPEED * sin(cub->player.rotation);
	else if (cub->player.mvt == S)
		new_pos = cub->player.y_pos - MOVE_SPEED * sin(cub->player.rotation);
	else if (cub->player.mvt == A)
		new_pos = cub->player.y_pos - MOVE_SPEED
			* sin(M_PI_2 - cub->player.rotation);
	else
		new_pos = cub->player.y_pos + MOVE_SPEED
			* sin(M_PI_2 - cub->player.rotation);
	return (new_pos);
}

static float	update_player_x_pos(t_cub *cub)
{
	float	new_pos;

	if (cub->player.mvt == W)
		new_pos = cub->player.x_pos + MOVE_SPEED * cos(cub->player.rotation);
	else if (cub->player.mvt == S)
		new_pos = cub->player.x_pos - MOVE_SPEED * cos(cub->player.rotation);
	else if (cub->player.mvt == A)
		new_pos = cub->player.x_pos + MOVE_SPEED
			* cos(M_PI_2 - cub->player.rotation);
	else
		new_pos = cub->player.x_pos - MOVE_SPEED
			* cos(M_PI_2 - cub->player.rotation);
	return (new_pos);
}

void	update_all_bonus(t_cub *cub)
{
	float	new[2];

	if (cub->player.mvt == W || cub->player.mvt == S
		|| cub->player.mvt == A || cub->player.mvt == D)
	{
		new[0] = update_player_y_pos(cub);
		new[1] = update_player_x_pos(cub);
		if (new[0] > TILE_SIZE && new[0] < (cub->map.height - 2) * TILE_SIZE
			&& new[1] > TILE_SIZE && new[1] < (cub->map.width - 2) * TILE_SIZE
			&& !check_wall_collision(new[1], new[0], cub))
		{
			cub->player.y_pos = new[0];
			cub->player.x_pos = new[1];
		}
	}
	if (cub->player.turn == LEFT_ARROW)
		cub->player.rotation -= ROT_SPEED;
	else if (cub->player.turn == RIGHT_ARROW)
		cub->player.rotation += ROT_SPEED;
}
