/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:43:24 by sel-mars          #+#    #+#             */
/*   Updated: 2021/11/09 12:03:18 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (*str)
	{
		str++;
		i++;
	}
	while (i != 0 && *str != (char)c)
	{
		str--;
		i--;
	}
	if (*str == (char)c)
		return ((char *)str);
	return (0);
}
