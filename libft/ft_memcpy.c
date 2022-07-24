/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 13:46:36 by sel-mars          #+#    #+#             */
/*   Updated: 2021/11/10 17:05:44 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*newdst;
	const char	*newsrc;

	i = 0;
	newdst = (char *)dst;
	newsrc = (const char *)src;
	if (!newdst && !newsrc)
		return ("\0");
	while (i < n)
	{
		newdst[i] = newsrc[i];
		i++;
	}
	return ((char *)newdst);
}
