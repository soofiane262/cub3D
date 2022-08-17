/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 18:11:02 by sel-mars          #+#    #+#             */
/*   Updated: 2022/08/17 12:37:34 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	mlx_change_image_color(void *img, int color, int width, int height)
{
	int		idx[2];
	int		coord[2];
	int		endian;
	int		*buff;

	buff = (int *)mlx_get_data_addr(img, &coord[0], &coord[1], &endian);
	coord[1] /= 4;
	idx[0] = 0;
	while (idx[0] < height)
	{
		idx[1] = 0;
		while (idx[1] < width)
		{
			buff[idx[0] * coord[1] + idx[1]] = color;
			idx[1]++;
		}
		idx[0]++;
	}
}

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
