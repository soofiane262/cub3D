/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 09:25:51 by sel-mars          #+#    #+#             */
/*   Updated: 2021/11/06 19:55:14 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strtrimstartidx(char const *s1, char const *set)
{
	int	i;
	int	j;

	i = 0;
	while (s1[i] != '\0')
	{
		j = 0;
		while (s1[i] != set[j] && set[j] != '\0')
			j++;
		if (s1[i] == set[j])
			i++;
		else
			break ;
	}
	return (i);
}

static int	ft_strtrimendidx(char const *s1, char const *set)
{
	int		i;
	int		j;
	size_t	s1len;

	s1len = ft_strlen(s1);
	i = s1len;
	while (i != 0)
	{
		j = 0;
		while (s1[i] != set[j] && set[j] != '\0')
			j++;
		if (s1[i] == set[j])
			i--;
		else
			break ;
	}
	return (i);
}

static char	*ft_strtrim_zero(void)
{
	char	*zeroptr;

	zeroptr = (char *)malloc(sizeof(char));
	if (!zeroptr)
		return (NULL);
	zeroptr[0] = '\0';
	return (zeroptr);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		startidx;
	int		endidx;
	char	*newstr;

	i = 0;
	if (!set)
		return ((char *)s1);
	else if (!s1)
		return (0);
	startidx = ft_strtrimstartidx(s1, set);
	endidx = ft_strtrimendidx(s1, set);
	if (endidx < startidx)
		return (ft_strtrim_zero());
	newstr = (char *)malloc((endidx - startidx + 2) * sizeof(char));
	if (!newstr)
		return (NULL);
	while (startidx <= endidx)
	{
		newstr[i] = s1[startidx];
		i++;
		startidx++;
	}
	newstr[i] = '\0';
	return (newstr);
}
