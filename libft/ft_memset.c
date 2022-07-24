/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 13:39:19 by sel-mars          #+#    #+#             */
/*   Updated: 2021/11/06 18:47:03 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *x, int i, size_t len)
{
	size_t			j;
	unsigned char	*dst;

	dst = (unsigned char *)x;
	j = 0;
	while (j < len)
	{
		*dst = (unsigned char)i;
		dst++;
		j++;
	}
	return (x);
}
