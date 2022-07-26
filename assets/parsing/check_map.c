/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 12:11:39 by sel-mars          #+#    #+#             */
/*   Updated: 2022/07/26 18:48:04 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_map_param_error(t_cub *cub, char *str)
{
	int	i;

	free(cub->map_path);
	if (cub->params.no_param)
		free(cub->params.no_text);
	if (cub->params.so_param)
		free(cub->params.so_text);
	if (cub->params.ea_param)
		free(cub->params.ea_text);
	if (cub->params.we_param)
		free(cub->params.we_text);
	i = 0;
	while (i < cub->map.height)
	{
		free(cub->map.map[i]);
		cub->map.map[i++] = NULL;
	}
	if (i)
	{
		free(cub->map.map);
		cub->map.map = NULL;
	}
	free(cub);
	cub = NULL;
	return (ft_put_error(str));
}

int	check_map_surroundings(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < cub->map.width)
	{
		if (!ft_strchr(" 1", cub->map.map[0][i])
			|| !ft_strchr(" 1", cub->map.map[cub->map.height - 1][i]))
		return (ft_map_param_error(cub, "Error: Map error"));
		i++;
	}
	i = 0;
	while (i < cub->map.height)
	{
		if (!ft_strchr(" 1", cub->map.map[i][0]) 
			|| !ft_strchr(" 1", cub->map.map[i][cub->map.width - 1]))
		return (ft_map_param_error(cub, "Error: Map error"));
		i++;
	}
	return (0);
}

int	check_space_surroundings(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (i < cub->map.height)
	{
		j = 0;
		while (j < cub->map.width)
		{
			if (cub->map.map[i][j] == ' '
				&& (
					(i - 1 >= 0 && !ft_strchr(" 1", cub->map.map[i - 1][j]))
					|| (i + 1 < cub->map.height
					&& !ft_strchr(" 1", cub->map.map[i + 1][j]))
					|| (j - 1 >= 0&& !ft_strchr(" 1", cub->map.map[i][j - 1]))
					|| (j + 1 < cub->map.width
					&& !ft_strchr(" 1", cub->map.map[i][j + 1]))
				))
			return (ft_map_param_error(cub, "Error: Map error"));
			j++;
		}
		i++;
	}
	return (0);
}

int	check_map_content(t_cub *cub)
{
	int	i;
	int	j;
	int	x;

	i = 0;
	x = 0;
	while (i < cub->map.height)
	{
		j = 0;
		while (j < cub->map.width)
		{
			if (!ft_strchr("01NSEW ", cub->map.map[i][j]) || x > 1)
				return (ft_map_param_error(cub, "Error: Map error"));
			else if (ft_strchr("NSEW", cub->map.map[i][j]))
			{
				x++;
				cub->player.x_pos = j;
				cub->player.y_pos = i;
				cub->player.orient = cub->map.map[i][j];
				cub->map.map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	check_map(t_cub *cub)
{
	int	i;

	i = 0;
	while (cub->map.map[i])
	{
		if (check_map_surroundings(cub) || check_space_surroundings(cub)
			|| check_map_content(cub))
			return (1);
		i++;
	}
	return (0);
}
