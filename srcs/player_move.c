/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjama <yjama@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:55:05 by yjama             #+#    #+#             */
/*   Updated: 2021/04/28 12:10:13 by yjama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	ft_normalize_angle(float *angle)
{
	*angle = remainder(*angle, (2 * M_PI));
	if (*angle < 0)
		*angle = (2 * M_PI) + *angle;
	return (*angle);
}

int	ft_plr_angle(float *angle)
{
	*angle = ft_normalize_angle(angle);
	if ((*angle > M_PI * 0.25) && (*angle < 0.75 * M_PI))
		return (1);
	else if ((*angle > M_PI * 1.25) && (*angle < 1.75 * M_PI))
		return (1);
	return (0);
}

int	has_wall_at(t_all *all, float y, float x)
{
	int		gridx;
	int		gridy;

	if (x < 0 || x > (all->map_w * all->tile_size) || \
	y < 0 || y > (all->map_h * all->tile_size))
		return (1);
	gridx = floor(x / all->tile_size);
	gridy = floor(y / all->tile_size);
	return (all->map[gridy][gridx] == '1');
}

void	ft_position_upd(t_all *all, float y, \
	float x, t_sprite *sprite)
{
	float		old_dirx;
	float		old_planx;
	float		vectangle;

	old_dirx = sprite->dir_x;
	old_planx = sprite->plan_x;
	vectangle = all->plr->turn_direction * all->plr->rotation_speed;
	sprite->dir_x = sprite->dir_x * cos(vectangle) - sprite->dir_y * \
	sin(vectangle);
	sprite->dir_y = old_dirx * sin(vectangle) + sprite->dir_y * cos(vectangle);
	sprite->plan_x = sprite->plan_x * cos(vectangle) - sprite->plan_y * \
	sin(vectangle);
	sprite->plan_y = old_planx * sin(vectangle) + sprite->plan_y * \
		cos(vectangle);
	if (x > all->tile_size && x < all->map_w * all->tile_size - all->tile_size && \
		y > all->tile_size && y < all->map_h * all->tile_size - all->tile_size)
	{
		all->plr->y = y;
		all->plr->x = x;
	}
}

void	ft_plr_move(t_all *all, t_plr *plr)
{
	float		move_step;
	float		new_player_x;
	float		new_player_y;
	int			player_orientation;

	player_orientation = ft_plr_angle(&plr->rotation_angle);
	plr->rotation_angle += plr->turn_direction * plr->rotation_speed;
	move_step = plr->walk_direction * plr->move_speed;
	new_player_y = plr->y + sin(plr->rotation_angle) * move_step;
	new_player_x = plr->x + cos(plr->rotation_angle) * move_step;
	if (plr->translation == -1 || plr->translation == 1)
	{
		plr->angle = (M_PI * 0.5) - plr->rotation_angle;
		if (player_orientation == 1)
		{
			new_player_y = plr->y + sin(plr->angle) * move_step;
			new_player_x = plr->x - cos(plr->angle) * move_step;
		}
		else if (player_orientation == 0)
		{
			new_player_y = plr->y - sin(plr->angle) * -move_step;
			new_player_x = plr->x + cos(plr->angle) * -move_step;
		}
	}
	ft_position_upd(all, new_player_y, new_player_x, all->sprite);
}
