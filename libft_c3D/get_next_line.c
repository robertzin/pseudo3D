/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjama <yjama@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 20:22:05 by yjama             #+#    #+#             */
/*   Updated: 2021/04/24 19:12:04 by yjama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 32
#endif

void	ft_strclr(char **s)
{
	if (s)
	{
		free(*s);
		*s = NULL;
	}
}

int	ft_return(int bytes, char **line, char *ptr, char **rest)
{
	if (bytes < 0 || !(*line))
	{
		ft_strclr(rest);
		ft_strclr(line);
		return (-1);
	}
	else if (bytes || ptr)
		return (1);
	else
	{
		ft_strclr(rest);
		return (0);
	}
}

char	*ft_check_rest(char *rest, char **line)
{
	char	*ptr;

	ptr = NULL;
	if (rest)
	{
		ptr = ft_strchr(rest, '\n');
		if (ptr)
		{
			*ptr = '\0';
			*line = ft_strdup(rest);
			rest = ft_strcpy(rest, ++ptr);
		}
		else
		{
			*line = ft_strdup(rest);
			rest[0] = '\0';
		}
	}
	else
	{
		*line = (char *)malloc(sizeof(char));
		if (*line)
			*line[0] = '\0';
	}
	return (ptr);
}

char	*ft_new_line(char *buf, char **rest)
{
	char	*ptr;

	ptr = NULL;
	ptr = ft_strchr(buf, '\n');
	if (ptr)
	{
		*ptr = '\0';
		ft_strclr(rest);
		*rest = ft_strdup(++ptr);
	}
	return (ptr);
}

int	get_next_line(int fd, char **line)
{
	char		buf[BUFFER_SIZE + 1];
	char		*ptr;
	char		*tmp;
	int			bytes;
	static char	*rest;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	ptr = ft_check_rest(rest, line);
	if (!(*line))
	{
		ft_strclr(&rest);
		return (-1);
	}
	while (!ptr && (bytes = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[bytes] = '\0';
		ptr = ft_new_line(buf, &rest);
		tmp = *line;
		*line = ft_strjoin(*line, buf);
		free(tmp);
	}
	return (ft_return(bytes, line, ptr, &rest));
}
