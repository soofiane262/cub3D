/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 15:28:23 by sel-mars          #+#    #+#             */
/*   Updated: 2022/09/05 12:50:23 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	paint_square_to_master(t_cub_bonus *cub_bonus, int coord[2], int size,
	int color)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = -1;
	y = coord[0];
	while (++i < size)
	{
		j = -1;
		x = coord[1];
		while (++j < size)
		{
			cub_bonus->cub->mlx.master_data[y * WIN_WIDTH + x] = color;
			x++;
		}
		y++;
	}
}

void	paint_gun_to_master(t_cub_bonus *cub_bonus)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = -1;
	y = WIN_HEIGHT - cub_bonus->gun.gun_height;
	while (++i < cub_bonus->gun.gun_height)
	{
		j = -1;
		x = WIN_WIDTH / 2 - cub_bonus->gun.gun_side / 2;
		while (++j < cub_bonus->gun.gun_side)
		{
			if (cub_bonus->gun.gun_data
				[cub_bonus->gun.idx]
				[i * cub_bonus->gun.gun_side + j]
				!= argb_to_int(255, 0, 0, 0))
			cub_bonus->cub->mlx.master_data[y * WIN_WIDTH + x]
					= cub_bonus->gun.gun_data
				[cub_bonus->gun.idx]
				[i * cub_bonus->gun.gun_side + j];
			x++;
		}
	y++;
	}
}

int	render_frame_bonus(t_cub_bonus *cub_bonus)
{
	if (cub_bonus->cub->player.mvt == ESC)
		leave_bonus(cub_bonus);
	update_all_bonus(cub_bonus);
	raycast(cub_bonus->cub);
	paint_master_bonus(cub_bonus);
	ray_free(cub_bonus->cub);
	paint_mini_map(cub_bonus);
	paint_gun_to_master(cub_bonus);
	mlx_clear_window(cub_bonus->cub->mlx.mlx, cub_bonus->cub->mlx.win);
	mlx_put_image_to_window(cub_bonus->cub->mlx.mlx, cub_bonus->cub->mlx.win,
		cub_bonus->cub->mlx.master, 0, 0);
	mlx_put_image_to_window(cub_bonus->cub->mlx.mlx, cub_bonus->cub->mlx.win,
		cub_bonus->mini_map.player,
		MINI_MAP_WIDTH / 2 + MINI_MAP_MARGIN - (MINI_MAP_PLAYER_SIZE / 2) - 2,
		MINI_MAP_HEIGHT / 2 + MINI_MAP_MARGIN - (MINI_MAP_PLAYER_SIZE / 2) - 2);
	return (0);
}
