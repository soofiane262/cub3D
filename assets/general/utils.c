/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 12:04:42 by sel-mars          #+#    #+#             */
/*   Updated: 2022/08/18 18:42:49 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_extension(char *str, char *ext)
{
	if (!ft_strnstr(str, ext, ft_strlen(str))
		|| ft_strncmp(ft_strnstr(str, ext,
				ft_strlen(str)), ext, ft_strlen(ext)))
		return (1);
	return (0);
}

int	int_in_range(int to_check, int min, int max)
{
	if (to_check >= min && to_check <= max)
		return (1);
	return (0);
}

int	argb_to_int(int alpha, int red, int green, int blue)
{
	if (!int_in_range(alpha, 0, 255) || !int_in_range(red, 0, 255)
		|| !int_in_range(green, 0, 255) || !int_in_range(blue, 0, 255))
		return (-1);
	return ((alpha << 24) + (red << 16) + (green << 8) + blue);
}

int	skip_space(char *str, int i)
{
	while (str[i] && (str[i] == ' '))
		i++;
	return (i);
}

int	skip_space_rv(char *str, int i)
{
	while (i >= 0 && (str[i] == ' '))
		i--;
	return (i);
}
