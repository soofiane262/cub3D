/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 12:04:42 by sel-mars          #+#    #+#             */
/*   Updated: 2022/08/17 18:09:18 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	int_in_range(int to_check, int min, int max)
{
	if (to_check < min || to_check > max)
		return (1);
	return (0);
}

int	argb_to_int(int alpha, int red, int green, int blue)
{
	if (int_in_range(alpha, 0, 255) || int_in_range(red, 0, 255)
		|| int_in_range(green, 0, 255) || int_in_range(blue, 0, 255))
		return (-1);
	return ((alpha << 24) + (red << 16) + (green << 8) + blue);
}

int	ft_put_error(char *error)
{
	ft_putendl_fd(error, 2);
	return (1);
}

int	skip_space(char *str, int i)
{
	while (str[i] && str[i] != '\n'
		&& (str[i] == 32 || (str[i] > 9 && str[i] < 13)))
		i++;
	return (i);
}
