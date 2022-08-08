/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 17:34:13 by sel-mars          #+#    #+#             */
/*   Updated: 2022/08/08 12:56:42 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

#include <stdio.h>

void	mlx_put_rectangle(int x, int y, int width, int height, int color, t_mlx mlx)
{
	int	i;
	int	j;

	i = y;
	while (i < y + height)
	{
		j = x;
		while (j < x + width)
		{
			if (i >= 0 && j >= 0)
				mlx_pixel_put(mlx.mlx, mlx.win, j, i, color);
			j++;
		}
		i++;
	}
}

void	put_3d_walls(t_cub *cub)
{
	int 	i;
	t_ray	*head;
	int		coord[2];
	int		dim[2];
	int		rayCorrectDistance;

	raycast(cub);
	head = cub->ray;
	dim[1] = STRIP_WIDTH;
	i = 0;
	while (cub->ray)
	{
		rayCorrectDistance = cub->ray->distance * cos(cub->ray->ray_angle - cub->player.rotation);
		dim[0] = ((float)TILE_SIZE / rayCorrectDistance) * (WIN_WIDTH / 2) / fabs(tan(FOV * M_PI / 360));
		coord[0] = (WIN_HEIGHT / 2) - (dim[0] / 2);
		coord[1] = i * STRIP_WIDTH;
		mlx_put_rectangle(coord[1], coord[0], dim[1], dim[0], argb_to_int(
			abs(rayCorrectDistance - (cub->farthest_wall_hit - cub->nearest_wall_hit))
			, 224, 202, 92), cub->mlx);
		i++;
		cub->ray = cub->ray->next;
	}
	cub->ray = head;
	ray_free(cub);
}

void	ft_3d(t_cub *cub)
{
	// mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.win, cub->mlx.ceiling, 0, 0);
	// mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.win, cub->mlx.floor, 0, WIN_HEIGHT / 2);
	put_3d_walls(cub);
}
