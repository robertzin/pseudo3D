/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjama <yjama@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 18:52:33 by yjama             #+#    #+#             */
/*   Updated: 2021/04/28 11:41:37 by yjama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_ptr_textures_in_array(t_all *all)
{
	int	bpp;
	int	size_line;
	int	endian;
	int	i;
	int	x;

	i = -1;
	while (++i < NUM_TEXTURE)
	{
		x = 0;
		all->txtr[i].texture_ptr = mlx_xpm_file_to_image(all->win->mlx_ptr, \
			all->txtr[i].path, &all->txtr[i].width, &all->txtr[i].height);
		if (!all->txtr[i].texture_ptr)
		{
			ft_putstr_fd("Error: texture pointer failed\n", STDOUT);
			exit(ft_free_all(all, ERROR));
		}
		all->txtr[i].wall_texture = (int *)mlx_get_data_addr(all->txtr[i].texture_ptr, \
			&bpp, &size_line, &endian);
		if (!all->txtr[i].wall_texture)
		{
			ft_putstr_fd("Error: wall texture error\n", STDOUT);
			exit(ft_free_all(all, ERROR));
		}
	}
}

void	create_image(t_all *all)
{
	int			bpp;
	int			size_line;
	int			endian;

	all->win->img_ptr = 0;
	endian = 0;
	all->win->img_ptr = mlx_new_image(all->win->mlx_ptr, \
		all->screen_w, all->screen_h);
	if (!all->win->img_ptr)
	{
		ft_putstr_fd("Error: can not get img_ptr", STDOUT);
		ft_free_all(all, ERROR);
	}
	all->win->img_addr = (int *)mlx_get_data_addr(all->win->img_ptr, \
		&bpp, &size_line, &endian);
	if (!all->win->img_addr)
	{
		ft_putstr_fd("Error: can not get img_addr", STDOUT);
		ft_free_all(all, ERROR);
		exit(ERROR);
	}
}

void	ft_init_vars(t_all *all)
{
	t_ray		ray;
	t_plr		plr;
	t_win		win;
	t_sprite	sprite;

	all->ray = &ray;
	all->plr = &plr;
	all->win = &win;
	all->sprite = &sprite;
	all->map = 0;
	all->txtr[0].texture_ptr = 0;
	all->sprite->path = 0;
	all->sprite->sprite_ptr = 0;
}

int	main(int argc, char **argv)
{
	t_all		all;

	ft_init_vars(&all);
	ft_check_arguments(&all, argc, argv);
	if (ft_file_descriptor(&all, argv[1]) == ERROR)
		return (ERROR);
	if (parsing(&all) == ERROR)
		return (-1);
	ft_mlx_init(&all);
	load_ptr_textures_in_array(&all);
	ft_init_plr(&all);
	ft_init_sprite(&all);
	ft_new_window(&all);
	if (!all.screenshoot)
		ft_events(&all);
	else
		game_loop(&all);
	return (ft_free_all(&all, SUCCESS));
}
