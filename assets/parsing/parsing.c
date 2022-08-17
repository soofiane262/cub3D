/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 13:04:08 by sel-mars          #+#    #+#             */
/*   Updated: 2022/08/17 18:10:25 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_params(t_cub *cub)
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

void ft_perror(char *str)
{
	ft_putendl_fd(str, 2);
	exit(1);
}

int check_args(int ac, char **av)
{
	int	fd;

	if (ac == 1)
		return (ft_put_error("Error: Missing path to map file"));
	else if (ac > 2)
		return (ft_put_error("Error: Too many arguments"));
	else if (!ft_strnstr(av[1], ".cub", ft_strlen(av[1]))
			|| ft_strncmp(ft_strnstr(av[1], ".cub", ft_strlen(av[1])), ".cub", 5))
		return (ft_put_error("Error: Wrong map extension"));
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (ft_put_error("Error: Unable to open map file"));
	close(fd);
	return (0);
}


int ft_check_extension(char *str, char *ext)
{
	if (!ft_strnstr(str, ext, ft_strlen(str)) 
		|| ft_strncmp(ft_strnstr(str, ext, ft_strlen(str)), ext, ft_strlen(ext)))
		return (1);
	return (0);
}

int	ft_skip_space(char *str, int i)
{
	while (str[i] && (str[i] == 32 || str[i] == 9))
		i++;
	return (i);
}

int	ft_skip_space_rv(char *str, int i)
{
	while (i >= 0 && (str[i] == 32 || str[i] == 9))
		i--;
	return (i);
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

t_cub	*parsing(int ac, char **av)
{
	t_cub	*cub;
	char	*tmp;
	int 	fd;
	int 	i;
	int 	j;
	int		error;
	int		count;
	int		line_idx = 0;

	count = 0;
	error = 0;
	if (check_args(ac, av))
		return (NULL);
	cub = (t_cub *)malloc(sizeof(t_cub));
	init_params(cub);
	cub->map_path = ft_strdup(av[1]);
	cub->map_fd = open(cub->map_path, O_RDONLY);
	cub->buff = get_next_line(cub->map_fd);
	tmp = NULL;
	while (cub->buff)
	{
		line_idx++;
		if (!ft_strncmp(cub->buff, "\n", 1))
		{	
			free(cub->buff);
			cub->buff = get_next_line(cub->map_fd);
			continue;
		}
		else if (!ft_strncmp(cub->buff, "NO ", 3) && !cub->params.no_text)
		{
			count++;
			i = ft_skip_space(cub->buff, 2);
			j = ft_skip_space_rv(cub->buff, ft_strlen(cub->buff) - 2);			
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
			i = ft_skip_space(cub->buff, 2);
			j = ft_skip_space_rv(cub->buff, ft_strlen(cub->buff) - 2);
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
			i = ft_skip_space(cub->buff, 2);
			j = ft_skip_space_rv(cub->buff, ft_strlen(cub->buff) - 2);
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
			i = ft_skip_space(cub->buff, 2);
			j = ft_skip_space_rv(cub->buff, ft_strlen(cub->buff) - 2);
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
			i = ft_skip_space(cub->buff, 2);
			j = ft_skip_space_rv(cub->buff, ft_strlen(cub->buff) - 2);
			tmp = ft_substr(cub->buff, i, j - i + 1);
			cub->params.f_color = get_color(tmp);
			if (cub->params.f_color == -1)
				error = 5;
		}
		else if (!ft_strncmp(cub->buff, "C ", 2) && cub->params.c_color == -1)
		{
			count++;
			i = ft_skip_space(cub->buff, 2);
			j = ft_skip_space_rv(cub->buff, ft_strlen(cub->buff) - 2);
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
		if (error > 0)
		{
			free(cub->buff);
			cub->buff = NULL;
		}
		if (error)
			break ;
		cub->buff = get_next_line(cub->map_fd);
	}
	check_map_error(line_idx, count, error, cub);
	while (cub->buff)
	{
		if ((int)ft_strlen(cub->buff) > cub->map.width)
			cub->map.width = ft_strlen(cub->buff);
			cub->map.height++;
		cub->buff = get_next_line(cub->map_fd);
	}
	cub->map.width--;
	close(cub->map_fd);
	cub->map_fd = open(cub->map_path, O_RDONLY);
	cub->buff = get_next_line(cub->map_fd);
	while (cub->buff && line_idx > 1)
	{
		line_idx--;
		cub->buff = get_next_line(cub->map_fd);
	}
	cub->map.map = (char **)malloc(sizeof(char *) * (cub->map.height + 1));
	if(!cub->map.map)
		return (NULL);
	i = 0;
	while (cub->buff && i < cub->map.height)
	{
		cub->map.map[i] = malloc(sizeof(char) * (cub->map.width + 1));
		if(!cub->map.map[i])
			return (NULL);
		tmp = ft_substr(cub->buff, 0, ft_strlen(cub->buff) - 1);
		j = 0;
		while (j < (int)ft_strlen(tmp))
		{
			cub->map.map[i][j] = tmp[j];
			j++;
		}
		while (j < cub->map.width)
		{
			cub->map.map[i][j] = ' ';
			j++;
		}
		cub->map.map[i][j] = '\0';
		i++;
		cub->buff = get_next_line(cub->map_fd);
	}
	cub->map.map[i] = NULL;

	i = 0;
	line_idx = 0;
	while (i < cub->map.height)
	{
		j = 0;
		while (j < cub->map.width)
		{
			if (!ft_strchr("01NSWE ", cub->map.map[i][j]) || line_idx > 1)
				ft_perror("Error in map");
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
				line_idx++;
			}
			if (cub->map.map[i][j] == '0'
				&& ((cub->map.map[i + 1][j] && cub->map.map[i + 1][j] == ' ')
				|| (cub->map.map[i - 1][j] && cub->map.map[i - 1][j] == ' ' )
				|| (cub->map.map[i][j + 1] && cub->map.map[i][j + 1] == ' ')
				|| (cub->map.map[i][j - 1] && cub->map.map[i][j - 1] == ' ')))
				ft_perror("Error in map");
			j++;
		}
		i++;
	}

	if (line_idx == 0)
		ft_perror("Error in map");
	return (cub);
}
