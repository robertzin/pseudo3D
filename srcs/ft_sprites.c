/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprites.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjama <yjama@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 10:06:07 by yjama             #+#    #+#             */
/*   Updated: 2021/04/28 12:07:53 by yjama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_sprite_data_ptr_load(t_all *all)
{
	int			bpp;
	int			size_line;
	int			endian;

	all->sprite[0].sprite_ptr = mlx_xpm_file_to_image(all->win->mlx_ptr, \
	all->sprite->path, &all->sprite->width, &all->sprite->height);
	if (!all->sprite->sprite_ptr)
	{
		ft_putstr_fd("Error: sprite pointer failed\n", STDOUT);
		exit(ft_free_all(all, ERROR));
	}
	all->sprite->sprite_texture = (int *)mlx_get_data_addr(\
	all->sprite->sprite_ptr, &bpp, &size_line, &endian);
	if (!all->sprite->sprite_texture)
	{
		ft_putstr_fd("Error: sprite pointer failed\n", STDOUT);
		exit(ft_free_all(all, ERROR));
	}
}

void	ft_sprite_zero_init(t_sprite *sprite)
{
	sprite->angle = 0;
	sprite->sprite_ptr = 0;
	sprite->sprite_texture = 0;
	sprite->width = 0;
	sprite->height = 0;
}

void	ft_sprite_position(t_all *all)
{
	int			i;
	int			j;
	int			id;

	id = 0;
	i = -1;
	while (all->map[++i])
	{
		j = 0;
		while (all->map[i][j])
		{
			if (all->map[i][j] == '2')
			{
				all->sprite->x[id] = j * all->tile_size + all->tile_size / 2;
				all->sprite->y[id] = i * all->tile_size + all->tile_size / 2;
				all->sprite->distance[id] = 0;
				id++;
			}
			j++;
		}
	}
}

void	ft_sprite_NEWS(t_all *all)
{
	if (all->NEWS == 'E')
	{
		all->sprite->dir_x = 1;
		all->sprite->dir_y = 0;
		all->sprite->plan_x = 0;
		all->sprite->plan_y = -0.6;
	}
	else if (all->NEWS == 'S')
	{
		all->sprite->dir_x = 0;
		all->sprite->dir_y = 1;
		all->sprite->plan_x = 0.6;
		all->sprite->plan_y = 0;
	}
	else if (all->NEWS == 'W')
	{
		all->sprite->dir_x = -1;
		all->sprite->dir_y = 0;
		all->sprite->plan_x = 0;
		all->sprite->plan_y = 0.6;
	}
	else if (all->NEWS == 'N')
		ft_sprite_N(all->sprite);
}

void	ft_init_sprite(t_all *all)
{
	all->sprite->nb_sprite = ft_sprite_count(all->map);
	ft_sprite_malloc(all);
	ft_sprite_zero(all->sprite);
	ft_sprite_data_ptr_load(all);
	ft_sprite_position(all);
	ft_sprite_NEWS(all);
}
