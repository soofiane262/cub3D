/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 18:35:30 by sel-mars          #+#    #+#             */
/*   Updated: 2021/11/06 18:48:15 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str1, const char *str2, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!*str2)
		return ((char *)str1);
	while (str1[i] != '\0' && i < n)
	{
		j = 0;
		while (str1[i + j] == str2[j] && str2[j] != '\0' && i + j < n)
			j++;
		if (str2[j] == '\0')
			return ((char *)&str1[i]);
		i++;
	}
	return (0);
}
