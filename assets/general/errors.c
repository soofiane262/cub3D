/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 18:33:03 by sel-mars          #+#    #+#             */
/*   Updated: 2022/08/26 16:38:30 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_put_error(char *error)
{
	ft_putendl_fd(error, 2);
	return (1);
}

static void	ft_map_param_error_2(t_cub *cub, char *str)
{
	int	i;

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
	exit(ft_put_error(str));
}

void	ft_map_param_error(t_cub *cub, int error, char *str)
{
	if (error == -1)
		free(cub->buff);
	free(cub->map_path);
	if (cub->params.no_text)
		free(cub->params.no_text);
	if (cub->params.so_text)
		free(cub->params.so_text);
	if (cub->params.ea_text)
		free(cub->params.ea_text);
	if (cub->params.we_text)
		free(cub->params.we_text);
	ft_map_param_error_2(cub, str);
}
