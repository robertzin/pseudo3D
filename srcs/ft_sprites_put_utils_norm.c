/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprites_put_utils_norm.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjama <yjama@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 10:50:10 by yjama             #+#    #+#             */
/*   Updated: 2021/04/28 12:14:16 by yjama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_sprite_count(char **map)
{
	int	i;
	int	j;
	int	sprites;

	i = -1;
	sprites = 0;
	while (map[++i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '2')
				sprites++;
			j++;
		}
	}
	return (sprites);
}

void	ft_sprite_N(t_sprite *sprite)
{
	sprite->dir_x = 0;
	sprite->dir_y = -1;
	sprite->plan_x = -0.6;
	sprite->plan_y = 0;
}

void	ft_sprite_malloc(t_all *all)
{
	all->sprite->x = malloc(sizeof(float) * all->sprite->nb_sprite);
	if (!(all->sprite->x))
	{
		ft_putstr_fd("Error: Sprite_x malloc failed\n", STDOUT);
		ft_free_all(all, ERROR);
	}
	all->sprite->y = malloc(sizeof(float) * all->sprite->nb_sprite);
	if (!(all->sprite->y))
	{
		ft_putstr_fd("Error: Sprite_y malloc failed\n", STDOUT);
		ft_free_all(all, ERROR);
	}
	all->sprite->distance = (float *)malloc(sizeof(float) * \
		all->sprite->nb_sprite);
	if (!(all->sprite->distance))
	{
		ft_putstr_fd("Error: Sprite_distance malloc failed\n", STDOUT);
		ft_free_all(all, ERROR);
	}
}
