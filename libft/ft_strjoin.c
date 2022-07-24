/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 09:09:14 by sel-mars          #+#    #+#             */
/*   Updated: 2021/11/10 17:02:17 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strjoin_ext(char *newstr, const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;
	size_t	s1len;
	size_t	s2len;

	i = 0;
	j = 0;
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	while (i < s1len)
	{
		newstr[i] = s1[i];
		i++;
	}
	while (j < s2len)
	{
		newstr[i] = s2[j];
		i++;
		j++;
	}
	newstr[i] = '\0';
	return (newstr);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	s1len;
	size_t	s2len;
	char	*newstr;

	if (!s1 || !s2)
		return (0);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	newstr = (char *)malloc((s1len + s2len + 1) * sizeof(char));
	if (!newstr)
		return (0);
	newstr = ft_strjoin_ext(newstr, s1, s2);
	return (newstr);
}
