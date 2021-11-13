/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprites_put_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjama <yjama@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 10:45:15 by yjama             #+#    #+#             */
/*   Updated: 2021/04/28 12:09:13 by yjama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_sprite_distance(t_sprite *sprite, t_plr *plr)
{
	int	id;

	id = 0;
	while (id < sprite->nb_sprite)
	{
		sprite->distance[id] = distance_between_points(plr->x, \
			plr->y, sprite->x[id], sprite->y[id]);
		id++;
	}
}
