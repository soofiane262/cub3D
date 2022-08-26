/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leave.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 19:06:11 by sel-mars          #+#    #+#             */
/*   Updated: 2022/08/26 14:59:46 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

#include <stdio.h>

static void	free_all(t_cub *cub)
{
	int	i;

	free(cub->map_path);
	free(cub->params.no_text);
	free(cub->params.so_text);
	free(cub->params.ea_text);
	free(cub->params.we_text);
	i = 0;
	while (i < cub->map.height)
	{
		free(cub->map.map[i]);
		cub->map.map[i++] = NULL;
	}
	free(cub->map.map);
	cub->map.map = NULL;
}

static void	destroy_all(t_cub *cub)
{
	mlx_destroy_image(cub->mlx.mlx, cub->mlx.wall_north);
	mlx_destroy_image(cub->mlx.mlx, cub->mlx.wall_south);
	mlx_destroy_image(cub->mlx.mlx, cub->mlx.wall_east);
	mlx_destroy_image(cub->mlx.mlx, cub->mlx.wall_west);
	mlx_clear_window(cub->mlx.mlx, cub->mlx.win);
	mlx_destroy_image(cub->mlx.mlx, cub->mlx.master);
	mlx_destroy_window(cub->mlx.mlx, cub->mlx.win);
}

int	leave(t_cub *cub)
{
	free_all(cub);
	destroy_all(cub);
	free(cub);
	cub = NULL;
	while(1)
	;
	exit(0);
	return (0);
}
