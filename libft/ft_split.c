/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 13:21:08 by sel-mars          #+#    #+#             */
/*   Updated: 2021/11/11 16:37:49 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_zerosplit(void)
{
	char	**zeroptr;

	zeroptr = (char **)malloc(sizeof(char *));
	zeroptr[0] = NULL;
	return (zeroptr);
}

static int	count_occur(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] == c && s[i] != '\0')
		i++;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i + 1] == c)
			i++;
		if (s[i] == c && s[i + 1] != '\0')
			count++;
		i++;
	}
	return (count + 1);
}

static int	count_char(const char *s, char c, int i)
{
	int	count;

	count = 0;
	while (s[i] != c && s[i] != '\0')
	{
		i++;
		count++;
	}
	return (count + 1);
}

static char	**ft_split_ext(char **split_tab, const char *s, char c, int l)
{
	int		i;
	int		j;
	int		k;
	int		count;

	i = 0;
	j = 0;
	while (s[i] != '\0' && j < l)
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != c)
		{
			count = count_char(s, c, i);
			split_tab[j] = (char *)malloc(count * sizeof(char));
			if (!split_tab[j])
				return (NULL);
			k = 0;
			while (s[i] != c && s[i] != '\0')
				split_tab[j][k++] = s[i++];
			split_tab[j][k] = '\0';
			j++;
		}
	}
	return (split_tab);
}

char	**ft_split(const char *s, char c)
{
	int		i;
	int		count;
	char	**split_tab;

	i = 0;
	if (!s)
		return (NULL);
	count = count_occur(s, c);
	while (s[i] == c && s[i] != '\0')
		i++;
	if (i == (int)ft_strlen(s))
		return (ft_zerosplit());
	split_tab = (char **)malloc((count + 1) * sizeof(char *));
	if (!split_tab)
		return (NULL);
	split_tab[count] = NULL;
	split_tab = ft_split_ext(split_tab, s, c, count);
	if (!split_tab)
	{
		while (count > 0)
			free(split_tab[count--]);
		free(split_tab);
		return (NULL);
	}
	return (split_tab);
}
