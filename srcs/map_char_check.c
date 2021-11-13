/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_char_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjama <yjama@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 18:31:53 by yjama             #+#    #+#             */
/*   Updated: 2021/04/27 16:50:59 by yjama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_no_spaces_in_map(t_all *all)
{
	int	i;
	int	j;

	i = -1;
	while (all->map[++i])
	{
		j = -1;
		while (all->map[i][++j])
		{
			if (all->map[i][j] == ' ')
				all->map[i][j] = '1';
		}
	}
}

int	ft_check_first_char(char *s)
{
	int	i;

	i = ft_skip_spaces(s);
	if (!s[i] || s[i] != '1')
	{
		ft_putstr_fd("Error: first character in map must be '1'\n", STDOUT);
		return (ERROR);
	}
	return (i);
}

int	ft_check_last_char(char c)
{
	if (c != '1')
	{
		ft_putstr_fd("Error: last character in map must be '1'\n", STDOUT);
		return (ERROR);
	}
	return (SUCCESS);
}

int	ft_is_good_char(char *s, char c)
{
	char		*ptr;

	ptr = ft_strchr("012NEWS ", c);
	if (ptr)
	{
		if (ft_strchr("NEWS", c))
		{
			if (!*s)
				*s = c;
			else
			{
				ft_putstr_fd("Error: more than one player\n", STDOUT);
				return (ERROR);
			}
		}
	}
	else
	{
		ft_putstr_fd("Error: unknown character\n", STDOUT);
		return (ERROR);
	}
	return (SUCCESS);
}

int	ft_check_char_around(char **map, int i, int j)
{
	int	ret;

	ret = 0;
	if (ft_strchr("012NEWS", map[i][j]))
	{
		if (map[i][j] == ' ')
		{
			if (map[i][j + 1] == ' ')
				ret++;
			if (map[i][j - 1] == ' ')
				ret++;
			if (map[i + 1][j] == ' ')
				ret++;
			if (map[i - 1][j] == ' ')
				ret++;
		}
	}
	if (ret == 4)
		return (ERROR);
	return (SUCCESS);
}
