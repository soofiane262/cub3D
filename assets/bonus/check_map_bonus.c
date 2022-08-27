/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 21:38:10 by kid-bouh          #+#    #+#             */
/*   Updated: 2022/08/27 11:45:26 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	ft_check_map_2(t_cub *cub, int i, int j, int *k)
{
	if (ft_strchr("NSWE", cub->map.map[i][j]))
	{
		cub->player.x_pos = j * TILE_SIZE;
		cub->player.y_pos = i * TILE_SIZE;
		cub->player.orient = cub->map.map[i][j];
		cub->player.rotation = 3 * M_PI_2;
		if (cub->player.orient == 'S')
		cub->player.rotation = M_PI_2;
		else if (cub->player.orient == 'W')
			cub->player.rotation = M_PI;
		else if (cub->player.orient == 'E')
			cub->player.rotation = 0;
		cub->map.map[i][j] = '0';
		(*k) += 1;
	}
	else if (
		((i == 0 || j == 0 || i == cub->map.height - 1
				|| j == cub->map.width - 1) && cub->map.map[i][j] != '1'
		&& cub->map.map[i][j] != ' ') || (cub->map.map[i][j] == ' '
		&& (
			(int_in_range(i + 1, 0, cub->map.height - 1) && int_in_range(j, 0, cub->map.width - 1)
			&& !ft_strchr("1 ", cub->map.map[i + 1][j]))
		|| (int_in_range(i - 1, 0, cub->map.height - 1) && int_in_range(j, 0, cub->map.width - 1)
			&& !ft_strchr("1 ", cub->map.map[i - 1][j]))
		|| (int_in_range(i, 0, cub->map.height - 1) && int_in_range(j + 1, 0, cub->map.width - 1)
			&& !ft_strchr("1 ", cub->map.map[i][j + 1]))
		|| (int_in_range(i, 0, cub->map.height - 1) && int_in_range(j - 1, 0, cub->map.width - 1)
			&& !ft_strchr("1 ", cub->map.map[i][j - 1]))
		)))
		ft_map_param_error(cub, 0,
			"Error: Map must be surrounded by walls");
}

void	ft_check_map_bonus(t_cub *cub)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (i < cub->map.height)
	{
		j = 0;
		while (j < cub->map.width)
		{
			if (!ft_strchr("01NSWED ", cub->map.map[i][j]))
				ft_map_param_error(cub, 0,
					"Error: Encountered unexpected charachter in map");
			ft_check_map_2(cub, i, j, &k);
			j++;
		}
		i++;
	}
	if (k == 0)
		ft_map_param_error(cub, 0, "Error: Missing player's starting pos·dir");
	else if (k > 1)
		ft_map_param_error(cub, 0,
			"Error: Player's starting pos·dir must be unique");
}
