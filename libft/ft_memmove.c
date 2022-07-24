/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memmove.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:21:14 by sel-mars          #+#    #+#             */
/*   Updated: 2021/11/06 18:47:14 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*newdst;
	unsigned char	*newsrc;

	i = n;
	newdst = (unsigned char *)dst;
	newsrc = (unsigned char *)src;
	if (!newdst && !newsrc)
		return ("\0");
	if (src < dst)
	{
		while (i != 0)
		{
			i--;
			newdst[i] = newsrc[i];
		}
	}
	else
		newdst = ft_memcpy(dst, src, n);
	return ((char *)newdst);
}
