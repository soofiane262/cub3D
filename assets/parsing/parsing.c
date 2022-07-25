/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 13:04:08 by sel-mars          #+#    #+#             */
/*   Updated: 2022/07/25 19:06:34 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
		#include <stdio.h>

int	ft_put_error(char *error)
{
	ft_putendl_fd(error, 2);
		return (1);
}

int	ft_map_param_error(t_cub *cub, char *str)
{
	int	i;

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
	free(cub);
	cub = NULL;
	return (ft_put_error(str));
}

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
}

int	skip_space(char *str, int i)
{
	while (str[i] && str[i] != '\n' && (str[i] == 32 || (str[i] > 9 && str[i] < 13)))
		i++;
	return (i);
}

int	read_map_file(t_cub *cub)
{
	int		i;
	int		for_rgb;
	int		tmp_int;
	int		tmp_int2;
	char	**tmp_str_arr;

	cub->params.nb_params = 0;
	cub->tmp_int = 1;
	tmp_int = 0;
	cub->buff = get_next_line(cub->map_fd);
	if (!cub->buff)
		return (ft_map_param_error(cub, "Error: Empty map file"));
	init_params(cub);
	while (cub->buff && cub->params.nb_params < 6)
	{
		cub->tmp_int++;
		if (ft_strnstr(cub->buff, "\n", 1))
		{
			cub->buff = get_next_line(cub->map_fd);
			continue ;
		}
		if (!ft_strncmp(cub->buff, "NO ", 3) && cub->params.nb_params++ >= 0)
		{
			cub->params.no_param++;
			if (cub->params.no_param > 1)
			{
				tmp_int = -1;
				break ;
			}
			cub->params.no_text = ft_substr(cub->buff, skip_space(cub->buff, 2),
				ft_strlen(cub->buff) - skip_space(cub->buff, 2) - 1);
			tmp_int = open(cub->params.no_text, O_RDONLY);
			if (!ft_strnstr(cub->params.no_text, ".xpm", ft_strlen(cub->params.no_text))
				|| ft_strncmp(ft_strnstr(cub->params.no_text, ".xpm", ft_strlen(cub->params.no_text)), ".xpm", 5)
				|| !cub->params.no_text || tmp_int == -1)
			{
				tmp_int = -1;
				break ;
			}
			close(tmp_int);
		}
		else if (!ft_strncmp(cub->buff, "SO ", 3) && cub->params.nb_params++ >= 0)
		{
			cub->params.so_param++;
			if (cub->params.so_param > 1)
			{
				tmp_int = -1;
				break ;
			}
			cub->params.so_text = ft_substr(cub->buff, skip_space(cub->buff, 2),
				ft_strlen(cub->buff) - skip_space(cub->buff, 2) - 1);
			tmp_int = open(cub->params.so_text, O_RDONLY);
			if (!ft_strnstr(cub->params.so_text, ".xpm", ft_strlen(cub->params.so_text))
				|| ft_strncmp(ft_strnstr(cub->params.so_text, ".xpm", ft_strlen(cub->params.so_text)), ".xpm", 5)
				|| !cub->params.so_text || tmp_int == -1)
			{
				tmp_int = -1;
				break ;
			}
			close(tmp_int);
		}
		else if (!ft_strncmp(cub->buff, "EA ", 3) && cub->params.nb_params++ >= 0)
		{
			cub->params.ea_param++;
			if (cub->params.ea_param > 1)
			{
				tmp_int = -1;
				break ;
			}
			cub->params.ea_text = ft_substr(cub->buff, skip_space(cub->buff, 2),
				ft_strlen(cub->buff) - skip_space(cub->buff, 2) - 1);
			tmp_int = open(cub->params.ea_text, O_RDONLY);
			if (!ft_strnstr(cub->params.ea_text, ".xpm", ft_strlen(cub->params.ea_text))
				|| ft_strncmp(ft_strnstr(cub->params.ea_text, ".xpm", ft_strlen(cub->params.ea_text)), ".xpm", 5)
				|| !cub->params.ea_text || tmp_int == -1)
			{
				tmp_int = -1;
				break ;
			}
			close(tmp_int);
		}
		else if (!ft_strncmp(cub->buff, "WE ", 3) && cub->params.nb_params++ >= 0)
		{
			cub->params.we_param++;
			if (cub->params.we_param > 1)
			{
				tmp_int = -1;
				break ;
			}
			cub->params.we_text = ft_substr(cub->buff, skip_space(cub->buff, 2),
				ft_strlen(cub->buff) - skip_space(cub->buff, 2) - 1);
			tmp_int = open(cub->params.we_text, O_RDONLY);
			if (!ft_strnstr(cub->params.we_text, ".xpm", ft_strlen(cub->params.we_text))
				|| ft_strncmp(ft_strnstr(cub->params.we_text, ".xpm", ft_strlen(cub->params.we_text)), ".xpm", 5)
				|| !cub->params.we_text || tmp_int == -1)
			{
				tmp_int = -1;
				break ;
			}
			close(tmp_int);
		}
		else if (!ft_strncmp(cub->buff, "F ", 2) && cub->params.nb_params++ >= 0)
		{
			cub->params.f_param++;
			if (cub->params.f_param > 1)
			{
				tmp_int = -1;
				break ;
			}
			for_rgb = 0;
			i = 1;
			while (cub->buff[i])
			{
				if (for_rgb == 3)
				{
					tmp_int = -1;
					break ;
				}
				i = skip_space(cub->buff, i);
				tmp_int = i;
				while (cub->buff[i] != ' ' && ft_isdigit(cub->buff[i]))
					i++;
				tmp_int2 = i - tmp_int;
				i = skip_space(cub->buff, i);
				if (cub->buff[i] && cub->buff[i] != '\n' && cub->buff[i] != ',')
				{
					tmp_int = -1;
					break ;
				}
				if (!for_rgb)
				{
					cub->tmp_str = ft_substr(cub->buff, tmp_int, tmp_int2);
					cub->params.f_red = ft_atoi(cub->tmp_str);
					free(cub->tmp_str);
				}
				else if (for_rgb == 1)
				{
					cub->tmp_str = ft_substr(cub->buff, tmp_int, tmp_int2);
					cub->params.f_green = ft_atoi(cub->tmp_str);
					free(cub->tmp_str);
				}
				else if (for_rgb == 2)
				{
					cub->tmp_str = ft_substr(cub->buff, tmp_int, tmp_int2);
					cub->params.f_blue = ft_atoi(cub->tmp_str);
					free(cub->tmp_str);
				}
				for_rgb++;
				i++;
			}
			cub->tmp_str = NULL;
			if (tmp_int == -1
				|| cub->params.f_red < 0 || cub->params.f_red > 255
				|| cub->params.f_green < 0 || cub->params.f_green > 255
				|| cub->params.f_blue < 0 || cub->params.f_blue > 255)
			{
				tmp_int = -1;
				break ;
			}
			cub->params.f_color = 256 * 256 * cub->params.f_red + 256 * cub->params.f_green + cub->params.f_blue;
		}
		else if (!ft_strncmp(cub->buff, "C ", 2) && cub->params.nb_params++ >= 0)
		{
			cub->params.c_param++;
			if (cub->params.c_param > 1)
			{
				tmp_int = -1;
				break ;
			}
			for_rgb = 0;
			i = 1;
			while (cub->buff[i])
			{
				if (for_rgb == 3)
				{
					tmp_int = -1;
					break ;
				}
				i = skip_space(cub->buff, i);
				tmp_int = i;
				while (cub->buff[i] != ' ' && ft_isdigit(cub->buff[i]))
					i++;
				tmp_int2 = i - tmp_int;
				i = skip_space(cub->buff, i);
				if (cub->buff[i] && cub->buff[i] != '\n' && cub->buff[i] != ',')
				{

					tmp_int = -1;
					break ;
				}
				if (!for_rgb)
				{
					cub->tmp_str = ft_substr(cub->buff, tmp_int, tmp_int2);
					cub->params.c_red = ft_atoi(cub->tmp_str);
					free(cub->tmp_str);
				}
				else if (for_rgb == 1)
				{
					cub->tmp_str = ft_substr(cub->buff, tmp_int, tmp_int2);
					cub->params.c_green = ft_atoi(cub->tmp_str);
					free(cub->tmp_str);
				}
				else if (for_rgb == 2)
				{
					cub->tmp_str = ft_substr(cub->buff, tmp_int, tmp_int2);
					cub->params.c_blue = ft_atoi(cub->tmp_str);
					free(cub->tmp_str);
				}
				for_rgb++;
				i++;
			}
			cub->tmp_str = NULL;
			if (tmp_int == -1
				|| cub->params.f_red < 0 || cub->params.f_red > 255
				|| cub->params.f_green < 0 || cub->params.f_green > 255
				|| cub->params.f_blue < 0 || cub->params.f_blue > 255)
			{
				tmp_int = -1;
				break ;
			}
			cub->params.c_color = 256 * 256 * cub->params.c_red + 256 * cub->params.c_green + cub->params.c_blue;
		}
		else
		{
			tmp_int = -1;
			break ;
		}
		tmp_int = 0;
		free(cub->buff);
		cub->buff = get_next_line(cub->map_fd);
	}
	if (tmp_int == -1)
	{
		free(cub->buff);
		return (ft_map_param_error(cub, "Error: Error in parameters"));
	}
	while (cub->buff && ft_strnstr(cub->buff, "\n", 1))
	{
		cub->tmp_int++;
		free(cub->buff);
		cub->buff = get_next_line(cub->map_fd);
	}
	cub->map.width = 0;
	cub->map.height = 0;
	while (cub->buff)
	{
		if ((int)(ft_strlen(cub->buff) - 1) > cub->map.width)
			cub->map.width = ft_strlen(cub->buff) - 1;
		cub->map.height++;
		free(cub->buff);
		cub->buff = get_next_line(cub->map_fd);
	}
	free(cub->buff);
	close(cub->map_fd);
	cub->map_fd = open(cub->map_path, O_RDONLY);
	i = 0;
	while (++i < cub->tmp_int)
		free(get_next_line(cub->map_fd));
	tmp_str_arr = (char **)malloc(sizeof(char *) * (cub->map.height + 1));
	cub->buff = get_next_line(cub->map_fd);
	i = 0;
	cub->error = false;
	tmp_int = 0;
	while (cub->buff)
	{
		if ((int)(ft_strlen(cub->buff) - 1) == cub->map.width)
		{
			if (tmp_int == 1)
				cub->error = true;
			tmp_int = 0;
			tmp_str_arr[i++] = ft_substr(cub->buff, 0, ft_strlen(cub->buff) - 1);
		}
		else if (cub->buff[0] == '\n')
		{
			tmp_int = 1;
			tmp_str_arr[i] = (char *)malloc(sizeof(char) * 2);
			tmp_str_arr[i][0] = '\n';
			tmp_str_arr[i++][1] = '\0';
		}
		else
		{
			if (tmp_int == 1)
				cub->error = true;
			tmp_int = 0;
			tmp_str_arr[i] = (char *)malloc(sizeof(char) * (cub->map.width + 1));
			cub->tmp_int = 0;
			while (cub->tmp_int < (int)(ft_strlen(cub->buff) - 1))
			{
				
				tmp_str_arr[i][cub->tmp_int] = cub->buff[cub->tmp_int];
				cub->tmp_int++;
			}
			while (cub->tmp_int < cub->map.width)
				tmp_str_arr[i][cub->tmp_int++] = ' ';
			tmp_str_arr[i++][cub->tmp_int] = '\0';
		}
		free(cub->buff);
		cub->buff = get_next_line(cub->map_fd);
	}
	tmp_str_arr[i] = NULL;
		tmp_int2 = 0;
	if (cub->error)
	{
		tmp_int2 = 0;
		while (tmp_int2 < cub->map.height)
			free(tmp_str_arr[tmp_int2++]);
		free(tmp_str_arr);
		cub->map.height -= tmp_int - 1;
		return (ft_map_param_error(cub, "Error: Map error"));
	}
	else
	{
		tmp_int = 1;
		while (cub->map.height
			&& ft_strlen(tmp_str_arr[cub->map.height - tmp_int]) == 1)
			tmp_int++;
		cub->map.map = (char **)malloc(sizeof(char *) * (cub->map.height - tmp_int + 2));
		tmp_int2 = 0;
		while (tmp_int2 < cub->map.height - tmp_int + 1)
		{
			cub->map.map[tmp_int2] = ft_strdup(tmp_str_arr[tmp_int2]);
			tmp_int2++;
		}
		cub->map.map[tmp_int2] = NULL;	
		tmp_int2 = 0;
		while (tmp_int2 < cub->map.height)
			free(tmp_str_arr[tmp_int2++]);
		free(tmp_str_arr);
		cub->map.height -= tmp_int - 1;
	}
	close(cub->map_fd);
	return (0);
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
					|| (i + 1 < cub->map.height && !ft_strchr(" 1", cub->map.map[i + 1][j]))
					|| (j - 1 >= 0 && !ft_strchr(" 1", cub->map.map[i][j - 1]))
					|| (j + 1 < cub->map.width && !ft_strchr(" 1", cub->map.map[i][j + 1]))
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
				cub->player.x_pos = i;
				cub->player.y_pos = j;
				cub->player.orient = cub->map.map[i][j];
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
