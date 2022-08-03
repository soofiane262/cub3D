/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 13:04:08 by sel-mars          #+#    #+#             */
/*   Updated: 2022/08/03 19:32:10 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_args(int ac, char **av)
{
	int	fd;

	if (ac == 1)
		return (ft_put_error("Error: No map path"));
	else if (ac > 2)
		return (ft_put_error("Error: To many arguments"));
	else if (!ft_strnstr(av[1], ".cub", ft_strlen(av[1]))
		|| ft_strncmp(ft_strnstr(av[1], ".cub", ft_strlen(av[1])), ".cub", 5))
		return (ft_put_error("Error: Wrong map extension"));
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (ft_put_error("Error: Couldn't open map file"));
	close(fd);
	return (0);
}

void	init_params(t_cub *cub)
{
	cub->params.no_param = 0;
	cub->params.so_param = 0;
	cub->params.ea_param = 0;
	cub->params.we_param = 0;
	cub->params.f_param = 0;
	cub->params.c_param = 0;
	cub->map.height = 0;
	cub->map.width = 0;
	cub->player.radius = 3;
	cub->player.turn = -1;
	cub->player.mvt = -1;
	cub->mini_map.height = MINI_MAP_HEIGHT / MINI_MAP_TILE_SIZE;
	cub->mini_map.width = MINI_MAP_WIDTH / MINI_MAP_TILE_SIZE;
	cub->mini_map.diff[0] = MINI_MAP_TILE_SIZE - (MINI_MAP_TILE_SIZE - PLAYER_SIZE) / 2;
	cub->mini_map.diff[1] = MINI_MAP_TILE_SIZE - (MINI_MAP_TILE_SIZE - PLAYER_SIZE) / 2;
}

t_cub	*parsing(int ac, char **av)
{
	t_cub	*cub;

	if (check_args(ac, av))
		return (NULL);
	cub = (t_cub *)malloc(sizeof(t_cub));
	cub->map_path = ft_strdup(av[1]);
	cub->map_fd = open(av[1], O_RDONLY);
	if (read_map_file(cub) || check_map(cub))
		return (NULL);
	return (cub);
}
