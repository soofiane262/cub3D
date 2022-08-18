/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 18:11:02 by sel-mars          #+#    #+#             */
/*   Updated: 2022/08/18 18:45:39 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	mlx_img_error(t_cub *cub, char *error, int wall_to_destroy)
{
	mlx_destroy_window(cub->mlx.mlx, cub->mlx.win);
	if (wall_to_destroy--)
		mlx_destroy_image(cub->mlx.mlx, cub->mlx.wall_north);
	if (wall_to_destroy--)
		mlx_destroy_image(cub->mlx.mlx, cub->mlx.wall_south);
	if (wall_to_destroy--)
		mlx_destroy_image(cub->mlx.mlx, cub->mlx.wall_east);
	if (wall_to_destroy)
		mlx_destroy_image(cub->mlx.mlx, cub->mlx.wall_west);
	ft_map_param_error(cub, error);
}
