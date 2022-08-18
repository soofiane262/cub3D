/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 16:56:25 by sel-mars          #+#    #+#             */
/*   Updated: 2022/08/18 16:58:01 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_args(int ac, char **av)
{
	int	fd;

	if (ac == 1)
		exit(ft_put_error("Error: Missing path to map file"));
	else if (ac > 2)
		exit(ft_put_error("Error: Too many arguments"));
	else if (!ft_strnstr(av[1], ".cub", ft_strlen(av[1]))
			|| ft_strncmp(ft_strnstr(av[1], ".cub", ft_strlen(av[1])), ".cub", 5))
		exit(ft_put_error("Error: Wrong map extension"));
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		exit(ft_put_error("Error: Unable to open map file"));
	close(fd);
}

void	check_map_error(int line_idx, int count, int error, t_cub *cub)
{
	if (line_idx == 0 || (!cub->buff && count == 0))
		ft_map_param_error(cub, "Error: Empty map file");
	else if (error == 1)
		ft_map_param_error(cub, "Error: Found duplicate parameter");
	else if (error == 2)
		ft_map_param_error(cub, "Error: Found unidentified parameter");
	else if (error == 3)
		ft_map_param_error(cub, "Error: Texture extension has to be `.xpm`");
	else if (error == 4)
		ft_map_param_error(cub, "Error: Unable to open texture file");
	else if (error == 5)
		ft_map_param_error(cub, "Error: Wrong color syntax");
	else if (count != 6)
		ft_map_param_error(cub, "Error: Missing one or multiple parameter·s");
}
