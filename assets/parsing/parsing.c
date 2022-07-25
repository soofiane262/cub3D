/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 13:04:08 by sel-mars          #+#    #+#             */
/*   Updated: 2022/07/24 23:51:58 by kid-bouh         ###   ########.fr       */
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
	close(cub->map_fd);
	if (cub->params.no_param)
		free(cub->params.no_text);
	if (cub->params.so_param)
		free(cub->params.so_text);
	if (cub->params.ea_param)
		free(cub->params.ea_text);
	if (cub->params.we_param)
		free(cub->params.we_text);
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

void	gnl(t_cub *cub)
{
	cub->tmp_str = get_next_line(cub->map_fd);
	// if (cub->buff)
	// 	free(cub->buff);
	cub->buff = ft_strtrim(cub->tmp_str, " ");
	free(cub->tmp_str);
	cub->tmp_str = NULL;
}

// int	rgb_to_int(t_cub *cub)
// {}

// int	f_and_c_colors(t_cub *cub)
// {}



void	init_params(t_cub *cub)
{
	cub->params.no_param = false;
	cub->params.so_param = false;
	cub->params.ea_param = false;
	cub->params.we_param = false;
}

int	skip_space(char *str, int i)
{
	while (str[i] && (str[i] == 32 || (str[i] > 9 && str[i] < 13)))
		i++;
	return (i);
}

int	read_map_file(t_cub *cub)
{
	int	i;
	int	for_rgb;
	int	tmp_int;
	int	tmp_int2;

	cub->params.nb_params = 0;
	tmp_int = 0;
	gnl(cub);
	if (!cub->buff)
		return (ft_map_param_error(cub, "Error: Empty map file"));
	while (cub->buff && cub->params.nb_params < 6)
	{
		if (ft_strnstr(cub->buff, "\n", 1))
		{
			gnl(cub);
			continue ;
		}
		if (!ft_strncmp(cub->buff, "NO ", 3) && cub->params.nb_params++ >= 0)
		{
			cub->params.no_text = ft_substr(cub->buff, skip_space(cub->buff, 2),
				ft_strlen(cub->buff) - skip_space(cub->buff, 2) - 1);
			// tmp_int = open(cub->params.no_text, O_RDONLY);
			if (!cub->params.no_text || tmp_int == -1)
				break ;
			close(tmp_int);
			cub->params.no_param = true;
		}
		else if (!ft_strncmp(cub->buff, "SO ", 3) && cub->params.nb_params++ >= 0)
		{
			cub->params.so_text = ft_substr(cub->buff, skip_space(cub->buff, 2),
				ft_strlen(cub->buff) - skip_space(cub->buff, 2) - 1);
			// tmp_int = open(cub->params.no_text, O_RDONLY);
			if (!cub->params.so_text || tmp_int == -1)
				break ;
			close(tmp_int);
			cub->params.so_param = true;
		}
		else if (!ft_strncmp(cub->buff, "EA ", 3) && cub->params.nb_params++ >= 0)
		{
			cub->params.ea_text = ft_substr(cub->buff, skip_space(cub->buff, 2),
				ft_strlen(cub->buff) - skip_space(cub->buff, 2) - 1);
			// tmp_int = open(cub->params.no_text, O_RDONLY);
			if (!cub->params.ea_text || tmp_int == -1)
				break ;
			close(tmp_int);
			cub->params.ea_param = true;
		}
		else if (!ft_strncmp(cub->buff, "WE ", 3) && cub->params.nb_params++ >= 0)
		{
			cub->params.we_text = ft_substr(cub->buff, skip_space(cub->buff, 2),
				ft_strlen(cub->buff) - skip_space(cub->buff, 2) - 1);
			// tmp_int = open(cub->params.no_text, O_RDONLY);
			if (!cub->params.we_text || tmp_int == -1)
				break ;
			close(tmp_int);
			cub->params.we_param = true;
		}
		else if (!ft_strncmp(cub->buff, "F ", 2) && cub->params.nb_params++ >= 0)
		{
		// ft_putstr_fd(cub->tmp_str, 1);
			for_rgb = 0;
			i = 1;
			while (cub->buff[i] != '\n' && for_rgb != 3)
			{
				i = skip_space(cub->buff, i);
				tmp_int = i;
				while (cub->buff[i] != '\n' && ft_isdigit(cub->buff[i]))
					i++;
				tmp_int2 = i - tmp_int;
				i = skip_space(cub->buff, i);
				if (cub->buff[i] && (cub->buff[i] != '\n' && cub->buff[i] != ','))
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
				break ;
			cub->params.f_color = 256 * 256 * cub->params.f_red + 256 * cub->params.f_green + cub->params.f_blue;
		}
		else if (!ft_strncmp(cub->buff, "C ", 2) && cub->params.nb_params++ >= 0)
		{
			for_rgb = 0;
			i = 1;
			while (cub->buff[i] != '\n' && for_rgb != 3)
			{
				i = skip_space(cub->buff, i);
				tmp_int = i;
				while (cub->buff[i] != '\n' && ft_isdigit(cub->buff[i]))
					i++;
				tmp_int2 = i - tmp_int;
				i = skip_space(cub->buff, i);
				if (cub->buff[i] && (cub->buff[i] != '\n' && cub->buff[i] != ','))
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
				break ;
			cub->params.c_color = 256 * 256 * cub->params.c_red + 256 * cub->params.c_green + cub->params.c_blue;
		}
		else
		{
			tmp_int = -1;
			break ;
		}
		
		// ft_putnbr_fd(cub->params.nb_params, 1);
			// ft_putstr_fd(cub->params.no_text, 1);
		// ft_putendl_fd("", 1);
		// ft_putstr_fd(cub->buff, 1);
		tmp_int = 0;
		free(cub->buff);
		gnl(cub);
	}
	if (tmp_int == -1)
	{
		free(cub->buff);
		return (ft_map_param_error(cub, "Error: Error in parameters"));
	}
	free(cub->buff);

	

	while (cub->buff)
	{
		gnl(cub);
		printf("%s",cub->buff);
	}


//////////////////////	map  ////////////////////////



















//////////////////////	end map  ////////////////////////
	
	close(cub->map_fd);
	return (0);
}

t_cub	*parsing(int ac, char **av)
{
	t_cub	*cub;

	if (check_args(ac, av))
		return (NULL);
	cub = (t_cub *)malloc(sizeof(t_cub));
	cub->map_fd = open(av[1], O_RDONLY);
	if (read_map_file(cub))
		return (NULL);
	return (cub);
}
