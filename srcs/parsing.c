/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjama <yjama@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 21:47:50 by yjama             #+#    #+#             */
/*   Updated: 2021/04/27 16:52:58 by yjama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_image_path(t_list **file, char *name, int n, char **dest)
{
	t_list	*node;
	char	*line;

	node = ft_node_find(file, name, n);
	if (!node)
	{
		ft_putstr_fd("Error: can not get image\n", STDOUT);
		return (ERROR);
	}
	line = (char *)node->content;
	line += 2;
	line += ft_skip_spaces(line);
	if (ft_check_file_extension(line, ".xpm") == ERROR)
		return (ERROR);
	dest[0] = ft_strdup(line);
	ft_list_remove_one_if(file, node->content, &ft_strcmp, \
		&ft_free_content_node);
	return (SUCCESS);
}

int	ft_read_file_return(int fd)
{
	if (close(fd) != SUCCESS)
	{
		ft_putstr_fd("Error while closing file\n", STDOUT);
		return (ERROR);
	}
	return (SUCCESS);
}

int	ft_read_file(t_list **file, int fd)
{
	char	*line;
	t_list	*node;
	int		return_gnl;

	return_gnl = 1;
	while (return_gnl)
	{
		return_gnl = get_next_line(fd, &line);
		if (return_gnl == ERROR)
		{
			ft_putstr_fd("Error while reading file\n", STDOUT);
			return (ERROR);
		}
		node = ft_lstnew(line);
		if (!node)
		{
			ft_putstr_fd("Error: GNL malloc failed\n", STDOUT);
			return (ERROR);
		}
		ft_lstadd_back(file, node);
	}
	return (ft_read_file_return(fd));
}

int	ft_get_info(t_all *all)
{
	all->color_up = 0;
	all->color_down = 0;
	if (ft_get_window_size(all) == ERROR)
		return (ft_free_all(all, ERROR));
	if (ft_get_color(&all->file, "C ", &all->color_up) == ERROR)
		return (ft_free_all(all, ERROR));
	if (ft_get_color(&all->file, "F ", &all->color_down) == ERROR)
		return (ft_free_all(all, ERROR));
	if (get_image_path(&all->file, "NO ", 3, &all->txtr[0].path) == ERROR)
		return (ft_free_all(all, ERROR));
	if (get_image_path(&all->file, "SO ", 3, &all->txtr[1].path) == ERROR)
		return (ft_free_all(all, ERROR));
	if (get_image_path(&all->file, "WE ", 3, &all->txtr[2].path) == ERROR)
		return (ft_free_all(all, ERROR));
	if (get_image_path(&all->file, "EA ", 3, &all->txtr[3].path) == ERROR)
		return (ft_free_all(all, ERROR));
	if (get_image_path(&all->file, "S ", 2, &all->sprite->path) == ERROR)
		return (ft_free_all(all, ERROR));
	return (SUCCESS);
}

int	parsing(t_all *all)
{
	all->file = NULL;
	all->NEWS = '\0';
	all->txtr[0].path = 0;
	all->txtr[1].path = 0;
	all->txtr[2].path = 0;
	all->txtr[3].path = 0;
	if (ft_read_file(&all->file, all->fd) == ERROR)
		return (ft_free_all(all, ERROR));
	if (ft_get_info(all) == ERROR)
		return (ERROR);
	if ((ft_check_map(all)) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
