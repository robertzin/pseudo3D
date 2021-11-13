/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_spaces_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjama <yjama@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 17:23:54 by yjama             #+#    #+#             */
/*   Updated: 2021/04/28 12:10:55 by yjama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_check_that_line_is_wall(char *line)
{
	int	i;

	i = ft_skip_spaces(line);
	while (line[++i])
	{
		if (line[i] != '1' && line[i] != ' ')
		{
			ft_putstr_fd("Error: no wall at top or bottom!\n", STDOUT);
			return (ERROR);
		}
	}
	return (SUCCESS);
}

int	ft_header_spaces(t_list **begin, t_list *node)
{
	char	*line;
	t_list	*next;

	if (!node)
		return (ERROR);
	line = node->content;
	line += ft_skip_spaces(line);
	if (!*line)
	{
		next = node->next;
		ft_list_remove_one_if(begin, node->content, &ft_strcmp, \
			&ft_free_content_node);
		return (ft_header_spaces(begin, next));
	}
	else if (*line != '1' && *line != '0')
		return (ERROR);
	return (SUCCESS);
}

int	ft_delete_spaces(t_all *all)
{
	if ((ft_header_spaces(&all->file, all->file)) == ERROR)
	{
		ft_putstr_fd("Error in header of the map\n", STDOUT);
		return (ERROR);
	}
	return (SUCCESS);
}
