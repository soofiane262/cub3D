/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:18:50 by sel-mars          #+#    #+#             */
/*   Updated: 2021/11/06 21:11:36 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	num_len(unsigned int n)
{
	size_t			len;

	len = 0;
	while (n > 9)
	{
		n /= 10;
		len++;
	}
	len++;
	return (len);
}

static int	num_sign(int n)
{
	int		sign;

	sign = 1;
	if (n < 0)
		sign = -1;
	return (sign);
}

static char	*ft_itoa_neg(int n)
{
	int				i;
	unsigned int	nb;
	size_t			len;
	char			*newnum;

	nb = n * -1;
	len = num_len(nb);
	newnum = (char *)malloc((len + 2) * sizeof(char));
	if (!newnum)
		return (0);
	i = len;
	while (nb > 9)
	{
		newnum[i] = (nb % 10) + 48;
		nb = nb / 10;
		i--;
	}
	newnum[i] = nb + 48;
	newnum[0] = '-';
	newnum[len + 1] = '\0';
	return (newnum);
}

static char	*ft_itoa_pos(int n)
{
	int		i;
	size_t	len;
	char	*newnum;

	len = num_len(n);
	newnum = (char *)malloc((len + 1) * sizeof(char));
	if (!newnum)
		return (0);
	i = len - 1;
	while (n > 9)
	{
		newnum[i] = (n % 10) + 48;
		n = n / 10;
		i--;
	}
	newnum[i] = n + 48;
	newnum[len] = '\0';
	return (newnum);
}

char	*ft_itoa(int n)
{
	int		sign;
	char	*newnum;

	sign = num_sign(n);
	if (sign == -1)
		newnum = ft_itoa_neg(n);
	else
		newnum = ft_itoa_pos(n);
	return (newnum);
}
