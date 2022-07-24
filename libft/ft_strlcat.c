/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:09:18 by sel-mars          #+#    #+#             */
/*   Updated: 2021/11/06 21:07:06 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	srclen;
	size_t	dstlen;

	i = 0;
	srclen = ft_strlen(src);
	dstlen = ft_strlen(dst);
	if (dstsize == 0 || dstlen > dstsize)
		return (srclen + dstsize);
	j = dstlen;
	dstsize -= dstlen;
	if (dstsize != 0)
	{
		while (src[i] && dstsize - 1 > 0)
		{
			dst[j] = src[i];
			i++;
			j++;
			dstsize--;
		}
		dst[j] = '\0';
	}
	return (srclen + dstlen);
}
