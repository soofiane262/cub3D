/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 21:26:34 by sel-mars          #+#    #+#             */
/*   Updated: 2022/07/24 12:59:21 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_nlsearch(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		return (1);
	return (0);
}

unsigned int	ft_nlidx(char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

char	*first_line(int fd, int *rread, char *str)
{
	char	*buff;
	char	*temp;

	*rread = BUFFER_SIZE;
	if (!str)
	{
		buff = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!buff)
			return (NULL);
		*rread = read(fd, buff, BUFFER_SIZE);
		if (*rread)
		{
			buff[*rread] = '\0';
			temp = str;
			str = ft_strdup_gnl(buff);
			ft_free_gnl(&temp);
		}
		ft_free_gnl(&buff);
	}
	return (str);
}

char	*next_line(int fd, int *rread, char *str)
{
	char	*buff;
	char	*temp;

	buff = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	while (str && !ft_nlsearch(str) && *rread == BUFFER_SIZE)
	{
		*rread = read(fd, buff, BUFFER_SIZE);
		buff[*rread] = '\0';
		temp = str;
		str = ft_strjoin_gnl(str, buff);
		free(temp);
	}
	free(buff);
	return (str);
}

char	*get_next_line(int fd)
{
	static char		*str;
	char			*temp;
	char			*rslt;
	int				rread;
	unsigned int	nlidx;

	rslt = NULL;
	if (BUFFER_SIZE <= 0 || read(fd, NULL, 0) != 0)
		return (NULL);
	str = first_line(fd, &rread, str);
	str = next_line(fd, &rread, str);
	if (str && !ft_nlsearch(str))
	{
		rslt = ft_strdup_gnl(str);
		ft_free_gnl(&str);
	}
	else if (str && ft_nlsearch(str))
	{
		nlidx = ft_nlidx(str);
		rslt = ft_substr_gnl(str, 0, nlidx + 1);
		temp = str;
		str = ft_substr_gnl(str, nlidx + 1, ft_strlen_gnl(str));
		free(temp);
	}
	return (rslt);
}
