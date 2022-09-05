/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 21:38:05 by kid-bouh          #+#    #+#             */
/*   Updated: 2022/09/05 12:48:48 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	fill_map_2(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (cub->buff)
	{
		cub->map.map[i] = malloc(sizeof(char) * (cub->map.width + 1));
		if (!cub->map.map[i])
			ft_map_param_error(cub, -1, "Error: Unable to allocate memory");
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

static void	fill_map(t_cub *cub, int k)
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
		ft_map_param_error(cub, -1, "Error: Unable to allocate memory");
	fill_map_2(cub);
}

static void	init_params(t_cub *cub, char *map_path)
{
	cub->count = 0;
	cub->error_parse = 0;
	cub->map.width = 0;
	cub->map.height = 0;
	cub->player.mvt = -1;
	cub->player.turn = -1;
	cub->params.f_color = -1;
	cub->params.c_color = -1;
	cub->params.no_text = NULL;
	cub->params.so_text = NULL;
	cub->params.ea_text = NULL;
	cub->params.we_text = NULL;
	cub->map_path = ft_strdup(map_path);
	cub->map_fd = open(cub->map_path, O_RDONLY);
}

static void	check_args(int ac, char **av)
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

t_cub	*parsing(int ac, char **av)
{
	t_cub	*cub;
	int		k;

	check_args(ac, av);
	cub = (t_cub *)malloc(sizeof(t_cub));
	init_params(cub, av[1]);
	k = parse_params(cub);
	while (cub->buff)
	{
		if ((int)ft_strlen(cub->buff) > cub->map.width
			&& cub->buff[(int)ft_strlen(cub->buff) - 1] == '\n')
			cub->map.width = (int)ft_strlen(cub->buff) - 1;
		else if ((int)ft_strlen(cub->buff) > cub->map.width
			&& !cub->buff[(int)ft_strlen(cub->buff) - 1])
			cub->map.width = (int)ft_strlen(cub->buff);
		cub->map.height++;
		free(cub->buff);
		cub->buff = get_next_line(cub->map_fd);
	}
	close(cub->map_fd);
	fill_map(cub, k);
	return (cub);
}
