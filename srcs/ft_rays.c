/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rays.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjama <yjama@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 18:36:10 by yjama             #+#    #+#             */
/*   Updated: 2021/04/28 12:08:40 by yjama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	distance_between_points(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void	init_struct_ray(t_ray *ray)
{
	ray->distance = 0;
	ray->yintercept = 0;
	ray->xintercept = 0;
	ray->ystep = 0;
	ray->xstep = 0;
	ray->wall_hit_y = 0;
	ray->wall_hit_x = 0;
	ray->vert_wall_hit_x = 0;
	ray->vert_wall_hit_y = 0;
	ray->horz_wall_hit_y = 0;
	ray->horz_wall_hit_x = 0;
	ray->found_vert_wall_hit = 0;
	ray->found_horz_wall_hit = 0;
	ray->is_ray_facing_up = 0;
	ray->is_ray_facing_down = 0;
	ray->is_ray_facing_right = 0;
	ray->is_ray_facing_left = 0;
	ray->was_hit_vertical = 0;
}

void	ray_facing(t_ray *ray)
{
	if (ray->ray_angle > 0 && ray->ray_angle < M_PI)
		ray->is_ray_facing_down = 1;
	else
		ray->is_ray_facing_up = 1;
	if (ray->ray_angle < (M_PI_2) || ray->ray_angle > (3 * M_PI_2))
		ray->is_ray_facing_right = 1;
	else
		ray->is_ray_facing_left = 1;
}

float	the_smallest_of_the_distances(t_ray *ray, t_plr *plr)
{
	float	horz_hit_distance;
	float	vert_hit_distance;

	horz_hit_distance = 0;
	vert_hit_distance = 0;
	if (ray->found_horz_wall_hit == 1)
		horz_hit_distance = distance_between_points(plr->x, plr->y, \
			ray->horz_wall_hit_x, ray->horz_wall_hit_y);
	else
		horz_hit_distance = MAX_VALUE;
	if (ray->found_vert_wall_hit == 1)
		vert_hit_distance = distance_between_points(plr->x, plr->y, \
			ray->vert_wall_hit_x, ray->vert_wall_hit_y);
	else
		vert_hit_distance = MAX_VALUE;
	return (the_smallest_of_the_distances_utile(ray, \
		vert_hit_distance, horz_hit_distance));
}

void	cast_all_rays(t_all *all)
{
	int	column_id;

	column_id = 0;
	all->ray->ray_angle = all->plr->rotation_angle - (all->plr->FOV / 2);
	while (column_id < all->rays_num)
	{
		all->ray->ray_angle = ft_normalize_angle(&all->ray->ray_angle);
		init_struct_ray(all->ray);
		ray_facing(all->ray);
		ray_horizontal(all);
		ray_vertical(all);
		all->distances[column_id] = the_smallest_of_the_distances(\
			all->ray, all->plr);
		render3d_projection(all, column_id);
		all->ray->ray_angle += (all->plr->FOV / all->rays_num);
		column_id++;
	}
}
