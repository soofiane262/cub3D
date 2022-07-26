/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 12:04:42 by sel-mars          #+#    #+#             */
/*   Updated: 2022/07/26 13:05:12 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	rgb_to_int(int red, int green, int blue)
{
	int	converted;

	converted = 256 * 256 * red + 256 * green + blue;
	return (converted);
}

int	ft_put_error(char *error)
{
	ft_putendl_fd(error, 2);
		return (1);
}

int	skip_space(char *str, int i)
{
	while (str[i] && str[i] != '\n' && (str[i] == 32 || (str[i] > 9 && str[i] < 13)))
		i++;
	return (i);
}
