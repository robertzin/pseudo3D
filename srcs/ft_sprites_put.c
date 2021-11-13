/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprites_put.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjama <yjama@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 10:42:27 by yjama             #+#    #+#             */
/*   Updated: 2021/04/28 12:17:41 by yjama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	ft_get_transform_y(t_all *all, t_sprite *sprite, int id)
{
	float		sprite_x;
	float		sprite_y;
	float		inv_det;
	float		transform_x;
	float		transform_y;

	sprite_x = sprite->x[id] - all->plr->x;
	sprite_y = sprite->y[id] - all->plr->y;
	inv_det = 1.0 / (sprite->plan_x * sprite->dir_y - \
		sprite->dir_x * sprite->plan_y);
	transform_x = inv_det * (sprite->dir_y * sprite_x - \
		sprite->dir_x * sprite_y);
	transform_y = inv_det * (-sprite->plan_y * sprite_x + \
		sprite->plan_x * sprite_y);
	sprite->sprite_screen_x = (int)((all->screen_w / 2) * \
		(1 + -transform_x / transform_y));
	return (transform_y);
}

void	ft_sprite_switch(t_sprite *sprite, int i, int j)
{
	float		temp_dist;
	float		temp_y;
	float		temp_x;

	temp_dist = sprite->distance[j];
	temp_x = sprite->x[j];
	temp_y = sprite->y[j];
	sprite->distance[j] = sprite->distance[i];
	sprite->x[j] = sprite->x[i];
	sprite->y[j] = sprite->y[i];
	sprite->distance[i] = temp_dist;
	sprite->x[i] = temp_x;
	sprite->y[i] = temp_y;
}

void	ft_sprite_sort(t_sprite *sprite)
{
	int			j;
	int			i;

	i = -1;
	while (i++ < sprite->nb_sprite)
	{
		j = i + 1;
		while (j < sprite->nb_sprite)
		{
			if (sprite->distance[j] > sprite->distance[i])
				ft_sprite_switch(sprite, i, j);
			j++;
		}
	}
}

void	ft_sprite_zero(t_sprite *sprite)
{
	sprite->draw_start_x = 0;
	sprite->draw_end_x = 0;
	sprite->draw_start_y = 0;
	sprite->draw_end_y = 0;
	sprite->sprite_screen_x = 0;
}

void	sprite_put(t_all *all, t_sprite *sprite, t_plr *plr)
{
	float		distance_projection;
	float		sprite_size;
	int			id;
	float		transform_y;

	id = 0;
	ft_sprite_sort(sprite);
	while (id < sprite->nb_sprite)
	{
		ft_sprite_distance(sprite, plr);
		distance_projection = (all->screen_w / 2) / tan(all->plr->FOV / 2);
		sprite_size = all->tile_size / sprite->distance[id] * \
		distance_projection;
		ft_sprite_zero(sprite);
		if (ft_sprite_visible(sprite, plr, id, sprite_size) == 1)
		{
			transform_y = ft_get_transform_y(all, sprite, id);
			ft_get_start(all, sprite, sprite_size);
			ft_sprite_draw(all, transform_y, sprite_size, id);
		}
		id++;
	}
}
