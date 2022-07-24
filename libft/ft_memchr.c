/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 10:22:16 by sel-mars          #+#    #+#             */
/*   Updated: 2021/11/09 10:59:38 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	cc;
	unsigned char	*dst;

	i = 0;
	cc = (unsigned char) c;
	dst = (unsigned char *)str;
	while (i < n)
	{
		if (*dst == cc)
			return (dst);
		dst++;
		i++;
	}
	return (0);
}
