/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 18:41:07 by sel-mars          #+#    #+#             */
/*   Updated: 2021/11/10 18:00:13 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned int	j;
	size_t			nlen;
	char			*newstr;

	if (!s)
		return (0);
	i = 0;
	j = start;
	nlen = len;
	while (nlen-- != 0 && s[i++] != '\0')
		j++;
	newstr = (char *)malloc((i + 1) * sizeof(char));
	if (!newstr)
		return (0);
	i = 0;
	while (i < len && start < ft_strlen(s) && s[start] != '\0')
	{
		newstr[i] = s[start];
		i++;
		start++;
	}
	newstr[i] = '\0';
	return (newstr);
}
