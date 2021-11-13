/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprites_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjama <yjama@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 10:07:33 by yjama             #+#    #+#             */
/*   Updated: 2021/04/28 12:17:54 by yjama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_sprite_texture_put(t_all *all, t_sprite *sprite, t_point point, \
		float sprite_size)
{
	int	texture_offset_x;
	int	distance_from_top;
	int	texture_offset_y;
	int	color;
	int	a;

	a = sizeof(sprite->sprite_texture);
	texture_offset_x = (int)(256 * (point.x - (-sprite_size / 2 + \
		sprite->sprite_screen_x)) * sprite->width / sprite_size) / 256;
	distance_from_top = (point.y) * 256 - all->screen_h * 128 + \
		sprite_size * 128;
	texture_offset_y = ((distance_from_top * sprite->height) / \
		sprite_size) / 256;
	if (((texture_offset_y * sprite->width) + texture_offset_x) < a)
		return ;
	color = sprite->sprite_texture[(texture_offset_y * sprite->width) + \
		texture_offset_x];
	if (color != 0x000000)
		all->win->img_addr[(point.y * all->screen_w) + point.x] = color;
}

void	ft_sprite_draw(t_all *all, float transform_y, \
		float sprite_size, int id)
{
	t_point	point;

	point.x = all->sprite->draw_start_x;
	while (point.x < all->sprite->draw_end_x)
	{
		if (transform_y > 0 && point.x > 0 && point.x < all->screen_w)
		{
			if (all->sprite->distance[id] < all->distances[point.x])
			{
				point.y = all->sprite->draw_start_y;
				while (point.y < all->sprite->draw_end_y)
				{
					ft_sprite_texture_put(all, all->sprite, point, sprite_size);
					point.y++;
				}
			}
		}
		point.x++;
	}
}

void	ft_get_start(t_all *all, t_sprite *sprite, float sprite_size)
{
	int	sprite_h;
	int	sprite_w;

	sprite_w = sprite_size;
	sprite->draw_start_x = -sprite_w / 2 + sprite->sprite_screen_x;
	if (sprite->draw_start_x < 0)
		sprite->draw_start_x = 0;
	sprite->draw_end_x = sprite_w / 2 + sprite->sprite_screen_x;
	if (sprite->draw_end_x >= all->screen_w)
		sprite->draw_end_x = all->screen_w - 1;
	sprite_h = sprite_size;
	sprite->draw_start_y = -sprite_h / 2 + all->screen_h / 2;
	if (sprite->draw_start_y < 0)
		sprite->draw_start_y = 0;
	sprite->draw_end_y = sprite_h / 2 + all->screen_h / 2;
	if (sprite->draw_end_y >= all->screen_h)
		sprite->draw_end_y = all->screen_h - 1;
}

float	ft_sprite_angle(t_plr *plr, float x, float y)
{
	float	vect_x;
	float	vect_y;
	float	player_to_sprite_angle;
	float	sprite_angle;
	float	player_angle;

	vect_x = x - plr->x;
	vect_y = y - plr->y;
	player_to_sprite_angle = atan2(vect_y, vect_x);
	player_angle = ft_normalize_angle(&plr->rotation_angle);
	sprite_angle = player_angle - player_to_sprite_angle;
	if (sprite_angle > M_PI)
		sprite_angle -= 2 * M_PI;
	if (sprite_angle < -M_PI)
		sprite_angle += 2 * M_PI;
	sprite_angle = fabs(sprite_angle);
	return (sprite_angle);
}

int	ft_sprite_visible(t_sprite *sprite, t_plr *plr, \
		int id, float sprite_size)
{
	float	sprite_angle;
	float	sprite_angle_end;
	float	wall_sprite_angle;
	float	FOV_sprite;

	sprite_angle = fabs(ft_sprite_angle(plr, sprite->x[id], \
		sprite->y[id]));
	sprite_angle_end = fabs(ft_sprite_angle(plr, (sprite->x[id] \
		+ sprite_size), (sprite->y[id] + sprite_size)));
	wall_sprite_angle = fabs(sprite_angle_end - sprite_angle);
	FOV_sprite = plr->FOV / 2 + wall_sprite_angle;
	if (sprite_angle < FOV_sprite)
		return (1);
	return (0);
}
