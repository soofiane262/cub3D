/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 21:38:05 by kid-bouh          #+#    #+#             */
/*   Updated: 2022/08/25 16:15:37 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

void	ft_map_param_error(t_cub *cub, char *str)
{
	int	i;

	free(cub->map_path);
	if (cub->params.no_text)
		free(cub->params.no_text);
	if (cub->params.so_text)
		free(cub->params.so_text);
	if (cub->params.ea_text)
		free(cub->params.ea_text);
	if (cub->params.we_text)
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
	exit(ft_put_error(str));
}

static void	parse_params_2(t_cub *cub)
{
	if (!ft_strncmp(cub->buff, "NO ", 3) && !cub->params.no_text)
		cub->params.no_text = ft_check_path_texture(cub);
	else if (!ft_strncmp(cub->buff, "SO ", 3) && !cub->params.so_text)
		cub->params.so_text = ft_check_path_texture(cub);
	else if (!ft_strncmp(cub->buff, "WE ", 3) && !cub->params.we_text)
		cub->params.we_text = ft_check_path_texture(cub);
	else if (!ft_strncmp(cub->buff, "EA ", 3) && !cub->params.ea_text)
		cub->params.ea_text = ft_check_path_texture(cub);
	else if (!ft_strncmp(cub->buff, "F ", 2) && cub->params.f_color == -1)
		cub->params.f_color = ft_check_color(cub, cub->params.f_color);
	else if (!ft_strncmp(cub->buff, "C ", 2) && cub->params.c_color == -1)
		cub->params.c_color = ft_check_color(cub, cub->params.c_color);
	else if ((!ft_strncmp(cub->buff, "NO ", 3) && cub->params.no_text)
		|| (!ft_strncmp(cub->buff, "SO ", 3) && cub->params.so_text)
		|| (!ft_strncmp(cub->buff, "EA ", 3) && cub->params.ea_text)
		|| (!ft_strncmp(cub->buff, "WE ", 3) && cub->params.we_text)
		|| (!ft_strncmp(cub->buff, "F ", 3) && cub->params.f_color != -1)
		|| (!ft_strncmp(cub->buff, "C ", 3) && cub->params.c_color != -1))
		cub->error_parse = 1;
	else if (ft_strchr("01NSWE ", cub->buff[0]))
		cub->error_parse = -1;
	else
		cub->error_parse = 2;
}

static int	parse_params(t_cub *cub)
{
	int		k;

	k = 0;
	cub->buff = get_next_line(cub->map_fd);
	while (cub->buff)
	{
		k++;
		if (!ft_strncmp(cub->buff, "\n", 1))
		{	
			free(cub->buff);
			cub->buff = get_next_line(cub->map_fd);
			continue ;
		}
		parse_params_2(cub);
		if (cub->error_parse != -1)
			free(cub->buff);
		if (cub->error_parse)
			break ;
		cub->buff = get_next_line(cub->map_fd);
	}
	check_map_error(k, cub->count, cub->error_parse, cub);
	return (k);
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
	ft_check_map(cub);
	return (cub);
}
