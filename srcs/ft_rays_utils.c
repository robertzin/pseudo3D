/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rays_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjama <yjama@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 21:53:38 by yjama             #+#    #+#             */
/*   Updated: 2021/04/28 12:06:42 by yjama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	next_vert_intercept(t_all *all, float next_vert_touch_y, \
	float next_vert_touch_x)
{
	 float	xToCheck;
	 float	yToCheck;

	while (next_vert_touch_x >= 0 && next_vert_touch_x <= all->screen_w \
		&& next_vert_touch_y >= 0 && next_vert_touch_y <= all->screen_h)
	{
		xToCheck = next_vert_touch_x;
		yToCheck = next_vert_touch_y;
		if (all->ray->is_ray_facing_left)
			xToCheck -= 1;
		if (has_wall_at(all, yToCheck, xToCheck))
		{
			all->ray->vert_wall_hit_x = next_vert_touch_x;
			all->ray->vert_wall_hit_y = next_vert_touch_y;
			all->ray->found_vert_wall_hit = 1;
			return ;
		}
		next_vert_touch_x += all->ray->xstep;
		next_vert_touch_y += all->ray->ystep;
	}
}

void	ray_vertical(t_all *all)
{
	float	x_intercept;
	float	y_intercept;
	float	next_vert_touch_x;
	float	next_vert_touch_y;

	x_intercept = floor(all->plr->x / all->tile_size) * all->tile_size;
	if (all->ray->is_ray_facing_right)
		x_intercept += all->tile_size;
	y_intercept = all->plr->y + (x_intercept - all->plr->x) * \
		tan(all->ray->ray_angle);
	all->ray->xstep = all->tile_size;
	if (all->ray->is_ray_facing_left)
		all->ray->xstep *= -1;
	all->ray->ystep = all->tile_size * tan(all->ray->ray_angle);
	if (all->ray->is_ray_facing_up && all->ray->ystep > 0)
		all->ray->ystep *= -1;
	if (all->ray->is_ray_facing_down && all->ray->ystep < 0)
		all->ray->ystep *= -1;
	next_vert_touch_x = x_intercept;
	next_vert_touch_y = y_intercept;
	next_vert_intercept(all, next_vert_touch_y, next_vert_touch_x);
}

void	next_horz_intercept(t_all *all, float next_horz_touch_y, \
	float next_horz_touch_x)
{
	float	xToCheck;
	float	yToCheck;

	while (next_horz_touch_x >= 0 && next_horz_touch_x <= (all->map_w * \
		all->tile_size) && next_horz_touch_y >= 0 && next_horz_touch_y <= \
			(all->map_h * all->tile_size))
	{
		xToCheck = next_horz_touch_x;
		yToCheck = next_horz_touch_y;
		if (all->ray->is_ray_facing_up)
			yToCheck -= 1;
		if (has_wall_at(all, yToCheck, xToCheck))
		{
			all->ray->horz_wall_hit_x = next_horz_touch_x;
			all->ray->horz_wall_hit_y = next_horz_touch_y;
			all->ray->found_horz_wall_hit = 1;
			return ;
		}
		else
		{
			next_horz_touch_x += all->ray->xstep;
			next_horz_touch_y += all->ray->ystep;
		}
	}
}

void	ray_horizontal(t_all *all)
{
	float	x_intercept;
	float	y_intercept;
	float	next_horz_touch_y;
	float	next_horz_touch_x;

	y_intercept = floor(all->plr->y / all->tile_size) * all->tile_size;
	if (all->ray->is_ray_facing_down)
		y_intercept += all->tile_size;
	x_intercept = all->plr->x + ((y_intercept - all->plr->y) \
		/ tan(all->ray->ray_angle));
	all->ray->ystep = all->tile_size;
	if (all->ray->is_ray_facing_up)
		all->ray->ystep *= -1;
	all->ray->xstep = all->tile_size / tan(all->ray->ray_angle);
	if (all->ray->is_ray_facing_left && all->ray->xstep > 0)
		all->ray->xstep *= -1;
	if (all->ray->is_ray_facing_right && all->ray->xstep < 0)
		all->ray->xstep *= -1;
	next_horz_touch_x = x_intercept;
	next_horz_touch_y = y_intercept;
	next_horz_intercept(all, next_horz_touch_y, next_horz_touch_x);
}

float	the_smallest_of_the_distances_utile(t_ray *ray, float vert_hit_distance, \
	float horz_hit_distance)
{
	if (horz_hit_distance < vert_hit_distance)
	{
		ray->wall_hit_x = ray->horz_wall_hit_x;
		ray->wall_hit_y = ray->horz_wall_hit_y;
		ray->distance = horz_hit_distance;
	}
	else
	{
		ray->wall_hit_x = ray->vert_wall_hit_x;
		ray->wall_hit_y = ray->vert_wall_hit_y;
		ray->distance = vert_hit_distance;
		ray->was_hit_vertical = 1;
	}
	return (ray->distance);
}
