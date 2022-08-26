/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 21:37:54 by kid-bouh          #+#    #+#             */
/*   Updated: 2022/08/26 15:58:56 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	check_map_error(int line_idx, int count, int error, t_cub *cub)
{
	if (line_idx == 0 || (!cub->buff && count == 0))
		ft_map_param_error(cub, error, "Error: Empty map file");
	else if (error == 1)
		ft_map_param_error(cub, error, "Error: Found duplicate parameter");
	else if (error == 2)
		ft_map_param_error(cub, error, "Error: Found unidentified parameter");
	else if (error == 3)
		ft_map_param_error(cub, error,
			"Error: Texture extension has to be `.xpm`");
	else if (error == 4)
		ft_map_param_error(cub, error,
			"Error: Unable to open texture file");
	else if (error == 5)
		ft_map_param_error(cub, error, "Error: Wrong color syntax");
	else if (count != 6)
		ft_map_param_error(cub, error,
			"Error: Missing one or multiple parameter·s");
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

int	parse_params(t_cub *cub)
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
