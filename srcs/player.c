/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjama <yjama@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 20:10:32 by yjama             #+#    #+#             */
/*   Updated: 2021/04/28 12:10:38 by yjama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_coordinate_plr(t_all *all)
{
	int		x;
	int		y;
	t_point	pos;

	y = -1;
	ft_bzero(&pos, sizeof(t_point));
	while (all->map[++y])
	{
		x = -1;
		while (all->map[y][++x])
		{
			if (ft_strchr("NEWS", all->map[y][x]))
			{
				all->plr->x = all->tile_size * x + all->tile_size / 2;
				all->plr->y = all->tile_size * y + all->tile_size / 2;
				all->plr->position = all->map[y][x];
			}
		}
	}
}

void	ft_plr_position(t_all *all)
{
	ft_coordinate_plr(all);
	if (all->plr->position == 'N')
		all->plr->rotation_angle = 1.5 * M_PI;
	else if (all->plr->position == 'W')
		all->plr->rotation_angle = M_PI;
	else if (all->plr->position == 'E')
		all->plr->rotation_angle = 0;
	else if (all->plr->position == 'S')
		all->plr->rotation_angle = 0.5 * M_PI;
}

void	ft_init_plr(t_all *all)
{
	all->tile_size = 10;
	all->plr->radius = 4;
	all->plr->turn_direction = 0;
	all->plr->walk_direction = 0;
	all->plr->translation = 0;
	all->plr->move_speed = 0.5;
	all->plr->angle = 0;
	all->plr->rotation_speed = 3 * (M_PI / 180);
	all->plr->FOV = (60 * (M_PI / 180));
	all->wall_width = 1;
	all->rays_num = (all->screen_w / all->wall_width);
	all->distances = (float *)malloc(sizeof(float) * all->rays_num);
	if (!(all->distances))
	{
		ft_putstr_fd("Error: all->distances malloc failed\n", STDOUT);
		ft_free_all(all, ERROR);
	}
	ft_plr_position(all);
}
