/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 21:38:10 by kid-bouh          #+#    #+#             */
/*   Updated: 2022/08/22 02:28:03 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_check_map_2(t_cub *cub, int i, int j, int *k)
{
	if (ft_strchr("NSWE", cub->map.map[i][j]))
	{
		cub->player.x_pos = j * TILE_SIZE;
		cub->player.y_pos = i * TILE_SIZE;
		cub->player.orient = cub->map.map[i][j];
		if (cub->player.orient == 'N')
			cub->player.rotation = 3 * M_PI_2;
		else if (cub->player.orient == 'S')
		cub->player.rotation = M_PI_2;
		else if (cub->player.orient == 'W')
			cub->player.rotation = M_PI;
		else if (cub->player.orient == 'E')
			cub->player.rotation = 0;
		cub->map.map[i][j] = '0';
		(*k) += 1;
	}
	if (cub->map.map[i][j] == '0'
		&& ((cub->map.map[i + 1][j] && cub->map.map[i + 1][j] == ' ')
		|| (cub->map.map[i - 1][j] && cub->map.map[i - 1][j] == ' ' )
		|| (cub->map.map[i][j + 1] && cub->map.map[i][j + 1] == ' ')
		|| (cub->map.map[i][j - 1] && cub->map.map[i][j - 1] == ' ')))
		ft_map_param_error(cub,
			"Error: Map must be surrounded by walls");
}

void	ft_check_map(t_cub *cub)
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
			if (!ft_strchr("01NSWE ", cub->map.map[i][j]))
				ft_map_param_error(cub,
					"Error: Encountered unexpected charachter in map");
			ft_check_map_2(cub, i, j, &k);
			j++;
		}
		i++;
	}
	if (k == 0)
		ft_map_param_error(cub, "Error: Missing player's starting pos·dir");
	else if (k > 1)
		ft_map_param_error(cub,
			"Error: Player's starting pos·dir must be unique");
}

void	fill_map_2(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (cub->buff)
	{
		cub->map.map[i] = malloc(sizeof(char) * (cub->map.width + 1));
		if (!cub->map.map[i])
			ft_map_param_error(cub, "Error: Unable to allocate memory");
		j = -1;
		while (cub->buff[++j] && cub->buff[j] != '\n')
			cub->map.map[i][j] = cub->buff[j];
		while (j < cub->map.width)
			cub->map.map[i][j++] = ' ';
		cub->map.map[i][j] = '\0';
		i++;
		free(cub->buff);
		cub->buff = get_next_line(cub->map_fd);
	}
	cub->map.map[i] = NULL;
}

void	fill_map(t_cub *cub, int k)
{
	cub->map_fd = open(cub->map_path, O_RDONLY);
	cub->buff = get_next_line(cub->map_fd);
	while (cub->buff && k > 1)
	{
		k--;
		free(cub->buff);
		cub->buff = get_next_line(cub->map_fd);
	}
	cub->map.map = (char **)malloc(sizeof(char *) * (cub->map.height + 1));
	if (!cub->map.map)
		ft_map_param_error(cub, "Error: Unable to allocate memory");
	fill_map_2(cub);
}
