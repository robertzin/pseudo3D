/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjama <yjama@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 15:34:20 by yjama             #+#    #+#             */
/*   Updated: 2021/04/27 16:53:11 by yjama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_map_char_check(t_all *all)
{
	int			i;
	int			j;
	int			save;

	i = 0;
	save = 0;
	while (all->map[i + 1])
	{
		j = ft_check_first_char(all->map[i]);
		if (j == ERROR)
			return (ERROR);
		while (all->map[i][++j])
		{
			if ((ft_is_good_char(&all->NEWS, all->map[i][j])) == ERROR)
				return (ERROR);
			if (ft_check_char_around(all->map, i, j) == ERROR)
				return (ERROR);
			if (all->map[i][j] != ' ')
				save = j;
		}
		if (ft_check_last_char(all->map[i][save]) == ERROR)
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

char	**ft_make_map(t_list **file, int num)
{
	t_list	*tmp;
	char	**map;
	int		i;

	i = 0;
	tmp = *file;
	map = ft_calloc(num + 1, sizeof(char *));
	while (tmp)
	{
		map[i] = ft_strdup(tmp->content);
		tmp = tmp->next;
		i++;
	}
	ft_lstclear(file, &free);
	if (i > 0)
		return (map);
	return (0);
}

int	ft_check_map(t_all *all)
{
	if ((ft_delete_spaces(all) == ERROR))
		return (ft_free_all(all, ERROR));
	if ((ft_nb_line_and_nb_column(all)) == ERROR)
		return (ft_free_all(all, ERROR));
	all->map = (ft_make_map(&all->file, ft_lstsize(all->file)));
	if (all->map == 0)
		return (ft_free_all(all, ERROR));
	ft_lstclear(&all->file, &ft_free_content_node);
	if (ft_check_that_line_is_wall(all->map[0]) == ERROR)
		return (ft_free_all(all, ERROR));
	if (ft_check_that_line_is_wall(all->map[all->map_h - 1]) == ERROR)
		return (ft_free_all(all, ERROR));
	if (ft_map_char_check(all) == ERROR)
	{
		printf("error\n");
		return (ft_free_all(all, ERROR));
	}
	if (!all->NEWS)
	{
		ft_putstr_fd("Error: no player detected\n", STDOUT);
		return (ERROR);
	}
	ft_no_spaces_in_map(all);
	all->file = 0;
	return (SUCCESS);
}
