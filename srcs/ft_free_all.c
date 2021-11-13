/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjama <yjama@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 11:47:01 by yjama             #+#    #+#             */
/*   Updated: 2021/04/28 12:28:42 by yjama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_map(t_all *all)
{
	int	i;

	i = -1;
	if (all->map)
	{
		while (all->map[++i])
		{
			free(all->map[i]);
			all->map[i] = 0;
		}
		free(all->map);
		all->map = 0;
	}
}

void	ft_free_content_node(void *line)
{
	if ((char *)line)
	{
		free((char *)line);
		line = 0;
	}
}

void	ft_free_sprite(t_all *all)
{
	if (all->sprite->path)
	{
		free(all->sprite->path);
		all->sprite->path = 0;
	}
	if (all->win->mlx_ptr && all->sprite->sprite_ptr)
	{
		mlx_destroy_image(all->win->mlx_ptr, all->sprite->sprite_ptr);
		all->sprite->sprite_ptr = 0;
		free(all->sprite->x);
		free(all->sprite->y);
		free(all->sprite->distance);
	}
}

void	ft_free_texture(t_all *all)
{
	int	i;

	i = -1;
	if (all->txtr[0].path)
		free(all->txtr[0].path);
	if (all->txtr[1].path)
		free(all->txtr[1].path);
	if (all->txtr[2].path)
		free(all->txtr[2].path);
	if (all->txtr[3].path)
		free(all->txtr[3].path);
	if (all->txtr[0].texture_ptr)
	{
		while (++i < NUM_TEXTURE)
		{
			if (all->txtr[i].texture_ptr)
				mlx_destroy_image(all->win->mlx_ptr, all->txtr[i].texture_ptr);
		}
	}
}

int	ft_free_all(t_all *all, int error_code)
{
	if (all->file)
		ft_lstclear(&all->file, &ft_free_content_node);
	ft_free_map(all);
	ft_free_texture(all);
	ft_free_sprite(all);
	if (all->win->mlx_ptr && all->win->win_ptr)
	{
		mlx_clear_window(all->win->mlx_ptr, all->win->win_ptr);
		mlx_destroy_window(all->win->mlx_ptr, all->win->win_ptr);
		if (all->win->img_ptr)
			mlx_destroy_image(all->win->mlx_ptr, all->win->img_ptr);
	}
	all->win->mlx_ptr = 0;
	all->win->win_ptr = 0;
	all->win->img_ptr = 0;
	all->file = 0;
	return (error_code);
}
