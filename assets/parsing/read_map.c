/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 12:23:03 by sel-mars          #+#    #+#             */
/*   Updated: 2022/08/01 19:20:40 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
	init_params(cub);
	if (!cub->buff)
		return (ft_map_param_error(cub, "Error: Empty map file"));
	while (cub->buff && cub->params.nb_params < 6)
	{
		cub->tmp_int++;
		if (ft_strnstr(cub->buff, "\n", 1))
		{
			free(cub->buff);
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
			cub->params.f_color = rgb_to_int(cub->params.f_red, cub->params.f_green, cub->params.f_blue);
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
			cub->params.c_color = rgb_to_int(cub->params.c_red, cub->params.c_green, cub->params.c_blue);
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
	tmp_int2 = 0;
	while (cub->buff)
	{
		if ((int)(ft_strlen(cub->buff) - 1) == cub->map.width && cub->buff[cub->map.width] == '\n')
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
			while ((tmp_int2 < cub->map.height - 1 && cub->tmp_int < (int)(ft_strlen(cub->buff) - 1))
				|| (tmp_int2 == cub->map.height - 1 && cub->tmp_int < (int)(ft_strlen(cub->buff))))
			{
				
				tmp_str_arr[i][cub->tmp_int] = cub->buff[cub->tmp_int];
				cub->tmp_int++;
			}
			while (cub->tmp_int < cub->map.width)
				tmp_str_arr[i][cub->tmp_int++] = ' ';
			tmp_str_arr[i++][cub->tmp_int] = '\0';
		}
		tmp_int2++;
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