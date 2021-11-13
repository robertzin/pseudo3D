/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjama <yjama@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 21:44:00 by yjama             #+#    #+#             */
/*   Updated: 2021/04/28 00:41:12 by yjama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	game_loop(t_all *all)
{
	create_image(all);
	ft_plr_move(all, all->plr);
	draw_ceiling(all);
	draw_floor(all);
	sprite_put(all, all->sprite, all->plr);
	cast_all_rays(all);
	sprite_put(all, all->sprite, all->plr);
	mini_map(all);
	if (all->screenshoot)
		bmp_exporter(all, "screenshoot.bmp");
	else
	{
		mlx_put_image_to_window(all->win->mlx_ptr, all->win->win_ptr, \
			all->win->img_ptr, 0, 0);
		mlx_destroy_image(all->win->mlx_ptr, all->win->img_ptr);
		all->win->img_ptr = 0;
	}
	return (SUCCESS);
}

void	ft_new_window(t_all *all)
{
	if (!all->screenshoot)
	{
		all->win->win_ptr = mlx_new_window(all->win->mlx_ptr, \
			all->screen_w, all->screen_h, "CUB3D");
		if (!all->win->win_ptr)
		{
			ft_putstr_fd("Error: can not create window\n", STDOUT);
			exit(ft_free_all(all, ERROR));
		}
	}
}

void	ft_mlx_init(t_all *all)
{
	all->win->mlx_ptr = 0;
	all->win->mlx_ptr = mlx_init();
	if (!all->win->mlx_ptr)
	{
		ft_putstr_fd("Error: mlx initialization failed\n", STDOUT);
		exit(ft_free_all(all, ERROR));
	}
}
