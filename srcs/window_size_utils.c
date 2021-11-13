/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_size_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjama <yjama@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 15:16:16 by yjama             #+#    #+#             */
/*   Updated: 2021/04/27 11:50:09 by yjama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_skip_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	return (i);
}

int	ft_skip_number(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isdigit(str[i]))
		i++;
	return (i);
}

int	ft_columns_num(t_list *node)
{
	int		size;
	int		new_size;

	size = 0;
	while (node)
	{
		new_size = (int)ft_strlen(node->content);
		if (new_size > size)
			size = new_size;
		node = node->next;
	}
	return (size);
}

int	ft_nb_line_and_nb_column(t_all *all)
{
	int	h;
	int	w;

	h = ft_lstsize(all->file);
	if (h < 3)
	{
		ft_putstr_fd("Error: too small map (at least 3 lines)\n", STDOUT);
		return (ERROR);
	}
	w = ft_columns_num(all->file);
	if (w < 3)
	{
		ft_putstr_fd("Error: too small map (at least 3 columns)\n", STDOUT);
		return (ERROR);
	}
	all->map_h = h - 1;
	all->map_w = w;
	return (SUCCESS);
}
