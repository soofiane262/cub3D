/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 21:38:00 by kid-bouh          #+#    #+#             */
/*   Updated: 2022/08/22 02:28:00 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_after_digit(char *tmp_char)
{
	int	j;

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
	return (0);
}

int	get_color_2(char *str, int i, int j, char *tmp_char)
{
	if (!ft_isdigit(str[i]) && str[i] != ' ' && str[i] != ',')
		return (-1);
	j = i;
	while (str[j] && str[j] != ',')
		j++;
	tmp_char = ft_substr(str, i, j - i);
	i = j;
	if (check_after_digit(tmp_char) == -1)
		return (-1);
	return (0);
}

int	*get_color_3(int *color, char *tmp_char)
{
	int	j;

	j = 0;
	while (color[j] != -1)
		j++;
	color[j] = ft_atoi(tmp_char);
	free(tmp_char);
	tmp_char = NULL;
	return (color);
}

int	get_color(char *str, int i, int j)
{
	int		*c;
	int		color[4];
	char	*tmp_char;

	while (j < 4)
		color[j++] = -1;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != ' ' && str[i] != ',')
			return (-1);
		j = i;
		while (str[j] && str[j] != ',')
			j++;
		tmp_char = ft_substr(str, i, j - i);
		i = j;
		if (check_after_digit(tmp_char) == -1)
			return (-1);
		c = get_color_3(color, tmp_char);
		if (str[i] && str[i++] == ',')
			color[3]++;
		if (color[3] > 1)
			return (-1);
	}
	return (argb_to_int(0, c[0], c[1], c[2]));
}
