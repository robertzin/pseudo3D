/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjama <yjama@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 22:10:06 by yjama             #+#    #+#             */
/*   Updated: 2021/04/26 22:30:13 by yjama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_get_width(char *line, int *screen_width)
{
	int	size_width;

	line += ft_skip_spaces(line);
	if (*line == 'R')
		line++;
	if (!ft_isspace(*line))
	{
		ft_putstr_fd("Error: first char after 'R' must be space\n", STDOUT);
		return (0);
	}
	line += ft_skip_spaces(line);
	if (ft_isdigit(*line))
	{
		size_width = ft_atoi(line);
		line += ft_skip_number(line);
	}
	else
	{
		ft_putstr_fd("Error: size window bad format\n", STDOUT);
		return (0);
	}
	*screen_width = size_width;
	return (line);
}

char	*ft_get_height(char *line, int *screen_height)
{
	int	size_height;

	line += ft_skip_spaces(line);
	if (ft_isdigit(*line))
	{
		size_height = ft_atoi(line);
		line += ft_skip_number(line);
	}
	else
	{
		ft_putstr_fd("Error\nwrong format for size window\n", STDOUT);
		return (0);
	}
	line += ft_skip_spaces(line);
	if (*line)
	{
		ft_putstr_fd("Error\nwrong character for size window\n", STDOUT);
		return (0);
	}
	*screen_height = size_height;
	return (line);
}

void	ft_check_max_resolution(t_all *all)
{
	int		w;
	int		h;

	w = 1920;
	h = 1080;
	if (all->screen_w > w)
		all->screen_w = w;
	if (all->screen_h > h)
		all->screen_h = h;
}

int	ft_get_window_size(t_all *all)
{
	char	*line;
	t_list	*node;

	node = ft_node_find(&all->file, "R ", 2);
	if (!node)
	{
		ft_putstr_fd("Error: no resolution found\n", STDOUT);
		return (ERROR);
	}
	line = node->content;
	line = ft_get_width(line, &all->screen_w);
	if (!line)
		return (ERROR);
	line = ft_get_height(line, &all->screen_h);
	if (!line)
		return (ERROR);
	if (all->screen_w < 100 || all->screen_h < 100)
	{
		ft_putstr_fd("Error: incorrect window size\n", STDOUT);
		return (ERROR);
	}
	ft_check_max_resolution(all);
	ft_list_remove_one_if(&all->file, node->content, &ft_strcmp, \
		&ft_free_content_node);
	return (SUCCESS);
}
