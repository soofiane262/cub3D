/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 16:30:25 by sel-mars          #+#    #+#             */
/*   Updated: 2022/08/10 18:26:04 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	init_north_wall(t_cub *cub)
{
	int	tmp[2];

	cub->mlx.wall_north = mlx_xpm_file_to_image(cub->mlx.mlx,
			cub->params.no_text, &tmp[0], &tmp[1]);
	if (!cub->mlx.wall_north)
		return (mlx_img_error(cub,
				"Error: Failed to read north texture XPM file", 0));
	else if (tmp[0] != tmp[1])
		return (mlx_img_error(cub,
				"Error: North texture is not square", 1));
	cub->mlx.wall_no_data = (int *)mlx_get_data_addr(cub->mlx.wall_north,
			&tmp[0], &cub->mlx.wall_no_side, &tmp[1]);
	cub->mlx.wall_no_side /= 4;
	return (0);
}

int	init_south_wall(t_cub *cub)
{
	int	tmp[2];

	cub->mlx.wall_south = mlx_xpm_file_to_image(cub->mlx.mlx,
			cub->params.so_text, &tmp[0], &tmp[1]);
	if (!cub->mlx.wall_south)
		return (mlx_img_error(cub,
				"Error: Failed to read south texture XPM file", 1));
	else if (tmp[0] != tmp[1])
		return (mlx_img_error(cub,
				"Error: South texture is not square", 2));
	cub->mlx.wall_so_data = (int *)mlx_get_data_addr(cub->mlx.wall_south,
			&tmp[0], &cub->mlx.wall_so_side, &tmp[1]);
	cub->mlx.wall_so_side /= 4;
	return (0);
}

int	init_east_wall(t_cub *cub)
{
	int	tmp[2];

	cub->mlx.wall_east = mlx_xpm_file_to_image(cub->mlx.mlx,
			cub->params.ea_text, &tmp[0], &tmp[1]);
	if (!cub->mlx.wall_north)
		return (mlx_img_error(cub,
				"Error: Failed to read east texture XPM file", 2));
	else if (tmp[0] != tmp[1])
		return (mlx_img_error(cub,
				"Error: East texture is not square", 3));
	cub->mlx.wall_ea_data = (int *)mlx_get_data_addr(cub->mlx.wall_east,
			&tmp[0], &cub->mlx.wall_ea_side, &tmp[1]);
	cub->mlx.wall_ea_side /= 4;
	return (0);
}

int	init_west_wall(t_cub *cub)
{
	int	tmp[2];

	cub->mlx.wall_west = mlx_xpm_file_to_image(cub->mlx.mlx,
			cub->params.we_text, &tmp[0], &tmp[1]);
	if (!cub->mlx.wall_north)
		return (mlx_img_error(cub,
				"Error: Failed to read west texture XPM file", 3));
	else if (tmp[0] != tmp[1])
		return (mlx_img_error(cub,
				"Error: West texture is not square", 4));
	cub->mlx.wall_we_data = (int *)mlx_get_data_addr(cub->mlx.wall_west,
			&tmp[0], &cub->mlx.wall_we_side, &tmp[1]);
	cub->mlx.wall_we_side /= 4;
	return (0);
}
