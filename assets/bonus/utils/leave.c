/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leave.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 12:18:28 by sel-mars          #+#    #+#             */
/*   Updated: 2022/09/05 12:48:06 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

static void	free_all(t_cub_bonus *cub_bonus)
{
	int	i;

	free(cub_bonus->cub->map_path);
	free(cub_bonus->cub->params.no_text);
	free(cub_bonus->cub->params.so_text);
	free(cub_bonus->cub->params.ea_text);
	free(cub_bonus->cub->params.we_text);
	i = 0;
	while (i < cub_bonus->cub->map.height)
	{
		free(cub_bonus->cub->map.map[i]);
		cub_bonus->cub->map.map[i++] = NULL;
	}
	free(cub_bonus->cub->map.map);
	cub_bonus->cub->map.map = NULL;
	free(cub_bonus->cub);
	cub_bonus->cub = NULL;
	free(cub_bonus->gun.gun);
	cub_bonus->gun.gun = NULL;
	free(cub_bonus->gun.gun_data);
	cub_bonus->gun.gun_data = NULL;
	free(cub_bonus->door.door);
	cub_bonus->door.door = NULL;
	free(cub_bonus->door.door_data);
	cub_bonus->door.door_data = NULL;
	free(cub_bonus);
	cub_bonus = NULL;
}

static void	destroy_all(t_cub_bonus *cub_bonus)
{
	int	idx;

	mlx_destroy_image(cub_bonus->cub->mlx.mlx, cub_bonus->cub->mlx.wall_north);
	mlx_destroy_image(cub_bonus->cub->mlx.mlx, cub_bonus->cub->mlx.wall_south);
	mlx_destroy_image(cub_bonus->cub->mlx.mlx, cub_bonus->cub->mlx.wall_east);
	mlx_destroy_image(cub_bonus->cub->mlx.mlx, cub_bonus->cub->mlx.wall_west);
	idx = -1;
	while (++idx < 11)
		mlx_destroy_image(cub_bonus->cub->mlx.mlx, cub_bonus->gun.gun[idx]);
	mlx_destroy_image(cub_bonus->cub->mlx.mlx, cub_bonus->door.door[0]);
	mlx_destroy_image(cub_bonus->cub->mlx.mlx, cub_bonus->door.door[1]);
	mlx_destroy_image(cub_bonus->cub->mlx.mlx, cub_bonus->mini_map.player);
	mlx_clear_window(cub_bonus->cub->mlx.mlx, cub_bonus->cub->mlx.win);
	mlx_destroy_image(cub_bonus->cub->mlx.mlx, cub_bonus->cub->mlx.master);
	mlx_destroy_window(cub_bonus->cub->mlx.mlx, cub_bonus->cub->mlx.win);
}

int	leave_bonus(t_cub_bonus *cub_bonus)
{
	destroy_all(cub_bonus);
	free_all(cub_bonus);
	exit(0);
	return (0);
}
