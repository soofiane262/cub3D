/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 17:34:13 by sel-mars          #+#    #+#             */
/*   Updated: 2022/08/04 18:45:36 by sel-mars         ###   ########.fr       */
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

	raycast(cub);
	head = cub->ray;
	dim[1] = STRIP_WIDTH;
	i = 0;
	while (cub->ray)
	{
		// printf("cub->ray->distance = %d\ndist to proj plane = %f\n\n", cub->ray->distance, (WIN_WIDTH / 2) / fabs(tan(FOV * M_PI / 360)));
		dim[0] = ((float)TILE_SIZE / cub->ray->distance) * (WIN_WIDTH / 2) / fabs(tan(FOV * M_PI / 360));
		coord[0] = (WIN_HEIGHT / 2) - (dim[0] / 2);
		coord[1] = i * STRIP_WIDTH;
		// printf("x\t=\t%d\ny\t=\t%d\nwidth\t=\t%d\nheight\t=\t%d\n\n", coord[1], coord[0], dim[1], dim[0]);
		mlx_put_rectangle(coord[1], coord[0], dim[1], dim[0], rgb_to_int(255, 255, 255), cub->mlx);
		i++;
		cub->ray = cub->ray->next;
	}
	cub->ray = head;
	ray_free(cub);
}

void	ft_3d(t_cub *cub)
{
	put_3d_walls(cub);
}
