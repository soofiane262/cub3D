/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 21:37:54 by kid-bouh          #+#    #+#             */
/*   Updated: 2022/08/22 02:27:57 by kid-bouh         ###   ########.fr       */
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

int	ft_check_color(t_cub *cub, int color)
{
	int		i;
	int		j;
	char	*tmp;

	cub->count++;
	i = skip_space(cub->buff, 2);
	j = skip_space_rv(cub->buff, ft_strlen(cub->buff) - 2);
	tmp = ft_substr(cub->buff, i, j - i + 1);
	color = get_color(tmp, 0, 0);
	if (tmp)
	{
		free(tmp);
		tmp = NULL;
	}
	if (color == -1)
		cub->error_parse = 5;
	return (color);
}

char	*ft_check_path_texture(t_cub *cub)
{
	int		i;
	int		j;
	int		fd;
	char	*str;

	cub->count++;
	i = skip_space(cub->buff, 2);
	j = skip_space_rv(cub->buff, ft_strlen(cub->buff) - 2);
	str = ft_substr(cub->buff, i, j - i + 1);
	if (check_extension(str, ".xpm"))
		cub->error_parse = 3;
	else
	{
		fd = open(str, O_RDWR);
		if (fd == -1)
			cub->error_parse = 4;
		else
			close(fd);
	}
	return (str);
}
