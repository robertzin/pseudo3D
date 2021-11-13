/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_minimap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjama <yjama@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 19:06:32 by yjama             #+#    #+#             */
/*   Updated: 2021/04/26 22:31:54 by yjama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_map_utile(t_all *all, t_point *point, int j, int color)
{
	int	y;
	int	x;

	y = -1;
	while (++y < all->tile_size * MINIMAP_SCALE)
	{
		x = -1;
		while (++x < all->tile_size * MINIMAP_SCALE)
		{
			all->win->img_addr[point->y * all->screen_w + point->x] = color;
			point->x += 1;
		}
		point->y += 1;
		point->x = j * all->tile_size * MINIMAP_SCALE;
	}
}

void	draw_map(t_all *all)
{
	int			y;
	int			x;
	t_point		point;

	y = -1;
	while (++y < all->map_h)
	{
		x = -1;
		while (all->map[y][++x])
		{
			if (all->map[y][x] == '2' || all->map[y][x] == '0' ||
			ft_strchr("NEWS", all->map[y][x]))
			{
				point.x = x * all->tile_size * MINIMAP_SCALE;
				point.y = y * all->tile_size * MINIMAP_SCALE;
				if (all->map[y][x] == '2')
					draw_map_utile(all, &point, x, 0xFF0000);
				else
					draw_map_utile(all, &point, x, 0xFFFFFF);
			}
		}
	}
}

void	player_rect(t_all *all, t_point point, int width, int height)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < height)
	{
		while (j < width)
		{
			all->win->img_addr[(i + point.y - width / 2)*all->screen_w + \
			(j + point.x - height / 2)] = 0x0078FF;
			j++;
		}
		j = 0;
		i++;
	}
}

void	orientation_line(t_all *all, t_point point, float distance,
		float angle)
{
	float		i;
	int			x;
	int			y;
	int			length;

	i = 0;
	x = 0;
	y = 0;
	length = 0;
	while (i < distance)
	{
		if (&all->win->img_addr[(point.y + y)*all->screen_w + \
		(point.x + x)] < all->win->img_addr)
			return ;
		all->win->img_addr[(point.y + y)*all->screen_w + (point.x + x)] \
			= 0xff0000;
		x = cos(angle) * length;
		y = sin(angle) * length;
		length++;
		i++;
	}
}

void	mini_map(t_all *all)
{
	t_point	point;

	point.x = all->plr->x * MINIMAP_SCALE;
	point.y = all->plr->y * MINIMAP_SCALE;
	draw_map(all);
	player_rect(all, point, all->plr->radius, all->plr->radius);
	orientation_line(all, point, 9, all->plr->rotation_angle);
}
