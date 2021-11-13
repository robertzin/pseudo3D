/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjama <yjama@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 14:35:04 by yjama             #+#    #+#             */
/*   Updated: 2021/04/24 18:33:47 by yjama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_get_value_color_finish(char *line, int column)
{
	line += ft_skip_number(line);
	line += ft_skip_spaces(line);
	if (column < 2 && *line == ',')
		line += 1;
	else
	{
		line += ft_skip_spaces(line);
		if (*line)
		{
			ft_putstr_fd("Error: something went wrong with color\n", STDOUT);
			return (0);
		}
	}
	return (line);
}

char	*ft_get_value_color_start(int *ptr, char *line, int column)
{
	if (!*line)
	{
		ft_putstr_fd("Error: color format is wrong\n", STDOUT);
		return (0);
	}
	line += ft_skip_spaces(line);
	if (ft_isdigit(*line))
	{
		*ptr = ft_atoi(line);
		if (*ptr > 255)
		{
			ft_putstr_fd("Error: color # must be less than 255\n", STDOUT);
			return (0);
		}
	}
	else
	{
		ft_putstr_fd("Error: color # is not a positive int\n", STDOUT);
		return (0);
	}
	return ((line = ft_get_value_color_finish(line, column)));
}

int	ft_node_error(void)
{
	ft_putstr_fd("Error: no color found of wrong format\n", STDOUT);
	return (ERROR);
}

int	ft_line_error(void)
{
	ft_putstr_fd("Error: 1st char after 'C' / 'F' must be space\n", STDOUT);
	return (ERROR);
}

int	ft_get_color(t_list **begin, char *name, int *num_color)
{
	char		*line;
	t_list		*node;
	int			color[3];
	int			i;

	node = ft_node_find(begin, name, 2);
	if (!node)
		return (ft_node_error());
	line = node->content;
	line += 1;
	if (*line != ' ')
		return (ft_line_error());
	i = -1;
	while (++i < 3)
	{
		line = ft_get_value_color_start(&color[i], line, i);
		if (!line)
			return (ERROR);
	}
	*num_color = (((color[0]) << 16) + ((color[1]) << 8) + (color[2]));
	ft_list_remove_one_if(begin, node->content, &ft_strcmp, \
	&ft_free_content_node);
	return (SUCCESS);
}
