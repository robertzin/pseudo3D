/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rays_3D.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjama <yjama@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 21:54:21 by yjama             #+#    #+#             */
/*   Updated: 2021/04/28 11:23:15 by yjama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ceiling(t_all *all)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (y < (all->screen_h / 2))
	{
		while (x < all->screen_w)
		{
			all->win->img_addr[(y * all->screen_w) + x] = all->color_up;
			x++;
		}
		x = 0;
		y++;
	}
}

void	draw_floor(t_all *all)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (y < (all->screen_h / 2))
	{
		while (x < all->screen_w)
		{
			all->win->img_addr[(y + all->screen_h / 2) *\
				all->screen_w + x] = all->color_down;
			x++;
		}
		x = 0;
		y++;
	}
}

int	choice_of_texture(t_ray *ray)
{
	if (ray->is_ray_facing_up && !ray->was_hit_vertical)
		return (0);
	if (ray->is_ray_facing_down && !ray->was_hit_vertical)
		return (1);
	if (ray->is_ray_facing_left && ray->was_hit_vertical)
		return (2);
	if (ray->is_ray_facing_right && ray->was_hit_vertical)
		return (3);
	return (0);
}

void	draw_wall(t_all *all, t_wall *wall, int column_id)
{
	int	texture_offset_x;
	int	texture_offset_y;
	int	texture_color;
	int	distance_from_top;
	int	index;

	index = choice_of_texture(all->ray);
	if (all->ray->was_hit_vertical == 1)
		texture_offset_x = (int)(all->ray->wall_hit_y * all->txtr[index].width \
			/ all->tile_size) % all->txtr[index].width;
	else
		texture_offset_x = (int)(all->ray->wall_hit_x * all->txtr[index].width \
			/ all->tile_size) % all->txtr[index].width;
	while (wall->wall_top < wall->wall_bottom)
	{
		distance_from_top = wall->wall_top + (wall->wall_strip_height / 2) - \
			(all->screen_h / 2);
		texture_offset_y = distance_from_top * ((float)all->txtr[index].height \
			/ wall->wall_strip_height);
		texture_color = all->txtr[index].wall_texture[(all->txtr[index].width * \
			texture_offset_y) + texture_offset_x];
		all->win->img_addr[(wall->wall_top * all->screen_w) + column_id] = \
			texture_color;
		wall->wall_top++;
	}
}

void	render3d_projection(t_all *all, int column_id)
{
	t_wall	wall;
	float	projected_wall_h;

	wall.correct_wall_distance = all->ray->distance * cos(all->ray->ray_angle - \
		all->plr->rotation_angle);
	wall.distance_projection_plane = (all->screen_w / 2) \
		/ tan(all->plr->FOV / 2);
	projected_wall_h = (all->tile_size / wall.correct_wall_distance) * \
		wall.distance_projection_plane;
	wall.wall_strip_height = (int)projected_wall_h;
	wall.wall_top = (all->screen_h / 2) - (wall.wall_strip_height / 2);
	if (wall.wall_top < 0)
		wall.wall_top = 0;
	wall.wall_bottom = (all->screen_h / 2) + (wall.wall_strip_height / 2);
	if (wall.wall_bottom > all->screen_h)
		wall.wall_bottom = all->screen_h;
	draw_wall(all, &wall, column_id);
}
