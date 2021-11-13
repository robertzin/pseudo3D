/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_events_keys.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjama <yjama@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 15:04:52 by yjama             #+#    #+#             */
/*   Updated: 2021/04/25 12:56:00 by yjama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int key, t_all *all)
{
	if (key == W)
		all->plr->walk_direction = 1;
	else if (key == S)
		all->plr->walk_direction = -1;
	else if (key == A)
	{
		all->plr->translation = -1;
		all->plr->walk_direction = -1;
	}
	else if (key == D)
	{
		all->plr->translation = 1;
		all->plr->walk_direction = 1;
	}
	else if (key == LEFT_ARROW)
		all->plr->turn_direction = -1;
	else if (key == RIGHT_ARROW)
		all->plr->turn_direction = 1;
	else if (key == ESC)
		exit(ft_free_all(all, SUCCESS));
	return (0);
}

int	key_release(int key, t_all *all)
{
	if (key == W)
		all->plr->walk_direction = 0;
	else if (key == S)
		all->plr->walk_direction = 0;
	else if (key == A || key == D)
	{
		all->plr->translation = 0;
		all->plr->walk_direction = 0;
	}
	else if (key == LEFT_ARROW)
		all->plr->turn_direction = 0;
	else if (key == RIGHT_ARROW)
		all->plr->turn_direction = 0;
	return (0);
}

int	close_window(t_all *all)
{
	exit(ft_free_all(all, SUCCESS));
}

void	ft_events(t_all *all)
{
	mlx_hook(all->win->win_ptr, 17, 1L << 17, &close_window, all);
	mlx_hook(all->win->win_ptr, 2, (1L << 0), &key_press, all);
	mlx_hook(all->win->win_ptr, 3, (1L << 1), &key_release, all);
	mlx_loop_hook(all->win->mlx_ptr, &game_loop, all);
	mlx_loop(all->win->mlx_ptr);
}
