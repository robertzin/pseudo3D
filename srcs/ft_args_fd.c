/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjama <yjama@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 21:49:08 by yjama             #+#    #+#             */
/*   Updated: 2021/04/24 18:19:32 by yjama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_check_file_extension(char *line, char *extension_name)
{
	int		end;

	end = (int)ft_strlen(line) - 1;
	while (end && ft_isspace(line[end]))
		line[end--] = '\0';
	end -= 3;
	if (end >= 4)
	{
		if (ft_strcmp(line + end, extension_name))
		{
			ft_putstr_fd("Error: incorrect extension\n", STDOUT);
			return (ERROR);
		}
	}
	return (SUCCESS);
}

void	ft_check_arguments(t_all *all, int ac, char **av)
{
	all->screenshoot = 0;
	if (ac == 3)
	{
		if (!ft_strcmp("--save", av[2]))
		{
			all->screenshoot = 1;
			if (ft_check_file_extension(av[1], ".cub") == ERROR)
				exit(ERROR);
		}
		else
		{
			ft_putstr_fd("Error: wrong argument\n", STDOUT);
			exit(ERROR);
		}
	}
	else if (ac != 2)
	{
		ft_putstr_fd("Error: wrong argument\n", STDOUT);
		exit(ERROR);
	}
	if (ac == 2)
	{
		if (ft_check_file_extension(av[1], ".cub") == ERROR)
			exit(ERROR);
	}
}

int	ft_file_descriptor(t_all *all, char *filename)
{
	all->fd = open(filename, O_RDONLY);
	if (all->fd < 0)
	{
		ft_putstr_fd("Error: failure open file\n", STDOUT);
		return (ERROR);
	}
	return (SUCCESS);
}
