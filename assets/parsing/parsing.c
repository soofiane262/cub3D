/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 13:04:08 by sel-mars          #+#    #+#             */
/*   Updated: 2022/08/18 18:30:53 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_params(t_cub *cub, char *map_path)
{
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

int	get_color(char *str)
{
	int		i;
	int		j;
	int		nb;
	int		color[3];
	char	*tmp_char;

	i = 0;
	nb = 0;
	color[0] = -1;
	color[1] = -1;
	color[2] = -1;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != ' ' && str[i] != ',')
			return (-1);
		j = i;
		while (str[j] && str[j] != ',')
			j++;
		tmp_char = ft_substr(str, i, j - i);
		i = j;
		j = -1;
		while (tmp_char[++j])
		{
			if (ft_isdigit(tmp_char[j]))
			{
				while (tmp_char[j] && tmp_char[j] != ' ')
					j++;
				while (tmp_char[j] && tmp_char[j] == ' ')
					j++;
				if (tmp_char[j])
					return (-1);
				else
					break ;
			}
		}
		j = 0;
		while (color[j] != -1)
			j++;
		color[j] = ft_atoi(tmp_char);
		free(tmp_char);
		tmp_char = NULL;
		if (str[i] && str[i++] == ',')
			nb++;
		if (nb > 2)
			return (-1);
	}
	return (argb_to_int(0, color[0], color[1], color[2]));
}

int	parse_params(t_cub *cub)
{
	int 	fd;
	int 	i;
	int 	j;
	int		k;
	int		error;
	int		count;
	char	*tmp;

	k = 0;
	count = 0;
	error = 0;
	tmp = NULL;
	cub->buff = get_next_line(cub->map_fd);
	while (cub->buff)
	{
		k++;
		if (!ft_strncmp(cub->buff, "\n", 1))
		{	
			free(cub->buff);
			cub->buff = get_next_line(cub->map_fd);
			continue;
		}
		else if (!ft_strncmp(cub->buff, "NO ", 3) && !cub->params.no_text)
		{
			count++;
			i = skip_space(cub->buff, 2);
			j = skip_space_rv(cub->buff, ft_strlen(cub->buff) - 2);			
			cub->params.no_text = ft_substr(cub->buff, i, j - i + 1);
			if (ft_check_extension(cub->params.no_text, ".xpm"))
				error = 3;
			else
			{
				fd = open(cub->params.no_text, O_RDONLY);
				if (fd == -1)
					error = 4;
				else
					close(fd);
			}
		}
		else if (!ft_strncmp(cub->buff, "SO ", 3) && !cub->params.so_text)
		{
			count++;
			i = skip_space(cub->buff, 2);
			j = skip_space_rv(cub->buff, ft_strlen(cub->buff) - 2);
			cub->params.so_text = ft_substr(cub->buff, i, j - i + 1);
			if (ft_check_extension(cub->params.so_text, ".xpm"))
				error = 3;
			else
			{
				fd = open(cub->params.so_text, O_RDONLY);
				if (fd == -1)
					error = 4;
				else
					close(fd);
			}
		}
		else if (!ft_strncmp(cub->buff, "WE ", 3) && !cub->params.we_text)
		{
			count++;
			i = skip_space(cub->buff, 2);
			j = skip_space_rv(cub->buff, ft_strlen(cub->buff) - 2);
			cub->params.we_text = ft_substr(cub->buff, i, j - i + 1);
			if (ft_check_extension(cub->params.we_text, ".xpm"))
				error = 3;
			else
			{
				fd = open(cub->params.we_text, O_RDONLY);
				if (fd == -1)
					error = 4;
				else
					close(fd);
			}
		}
		else if (!ft_strncmp(cub->buff, "EA ", 3) && !cub->params.ea_text)
		{
			count++;
			i = skip_space(cub->buff, 2);
			j = skip_space_rv(cub->buff, ft_strlen(cub->buff) - 2);
			cub->params.ea_text = ft_substr(cub->buff, i, j - i + 1);
			if (ft_check_extension(cub->params.ea_text, ".xpm"))
				error = 3;
			else
			{
				fd = open(cub->params.ea_text, O_RDONLY);
				if (fd == -1)
					error = 4;
				else
					close(fd);
			}
		}
		else if (!ft_strncmp(cub->buff, "F ", 2) && cub->params.f_color == -1)
		{
			count++;
			i = skip_space(cub->buff, 2);
			j = skip_space_rv(cub->buff, ft_strlen(cub->buff) - 2);
			tmp = ft_substr(cub->buff, i, j - i + 1);
			cub->params.f_color = get_color(tmp);
			if (cub->params.f_color == -1)
				error = 5;
		}
		else if (!ft_strncmp(cub->buff, "C ", 2) && cub->params.c_color == -1)
		{
			count++;
			i = skip_space(cub->buff, 2);
			j = skip_space_rv(cub->buff, ft_strlen(cub->buff) - 2);
			tmp = ft_substr(cub->buff, i, j - i + 1);
			cub->params.c_color = get_color(tmp);
			if (cub->params.c_color == -1)
				error = 5;
		}
		else if ((!ft_strncmp(cub->buff, "NO ", 3) && cub->params.no_text)
				|| (!ft_strncmp(cub->buff, "SO ", 3) && cub->params.no_text)
				|| (!ft_strncmp(cub->buff, "EA ", 3) && cub->params.no_text)
				|| (!ft_strncmp(cub->buff, "WE ", 3) && cub->params.no_text)
				|| (!ft_strncmp(cub->buff, "F ", 3) && cub->params.f_color != -1)
				|| (!ft_strncmp(cub->buff, "C ", 3) && cub->params.c_color != -1))
			error = 1;
		else if (ft_strchr("01NSWE ", cub->buff[0]))
			error = -1;
		else
			error = 2;
		if (tmp)
		{
			free(tmp);
			tmp = NULL;
		}
		if (error != -1)
			free(cub->buff);
		if (error)
			break ;
		cub->buff = get_next_line(cub->map_fd);
	}
	check_map_error(k, count, error, cub);
	return (k);
}

t_cub	*parsing(int ac, char **av)
{
	t_cub	*cub;
	int 	i;
	int 	j;
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

	cub->map_fd = open(cub->map_path, O_RDONLY);
	cub->buff = get_next_line(cub->map_fd);
	while (cub->buff && k > 1)
	{
		k--;
		free(cub->buff);
		cub->buff = get_next_line(cub->map_fd);
	}

	cub->map.map = (char **)malloc(sizeof(char *) * (cub->map.height + 1));
	if(!cub->map.map)
		ft_map_param_error(cub, "Error: Unable to allocate memory");
	i = 0;
	while (cub->buff)
	{
		cub->map.map[i] = malloc(sizeof(char) * (cub->map.width + 1));
		if(!cub->map.map[i])
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

	i = 0;
	k = 0;
	while (i < cub->map.height)
	{
		j = 0;
		while (j < cub->map.width)
		{
			if (!ft_strchr("01NSWE ", cub->map.map[i][j]))
				ft_map_param_error(cub, "Error: Encountered unexpected charachter in map");
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
				k++;
			}
			if (cub->map.map[i][j] == '0'
				&& ((cub->map.map[i + 1][j] && cub->map.map[i + 1][j] == ' ')
				|| (cub->map.map[i - 1][j] && cub->map.map[i - 1][j] == ' ' )
				|| (cub->map.map[i][j + 1] && cub->map.map[i][j + 1] == ' ')
				|| (cub->map.map[i][j - 1] && cub->map.map[i][j - 1] == ' ')))
				ft_map_param_error(cub, "Error: Map must be surrounded by walls");
			j++;
		}
		i++;
	}

	if (k == 0)
		ft_map_param_error(cub, "Error: Missing player's starting pos·dir");
	else if (k > 1)
		ft_map_param_error(cub, "Error: Player's starting pos·dir must be unique");
	return (cub);
}
