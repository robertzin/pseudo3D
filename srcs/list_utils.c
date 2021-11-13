/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjama <yjama@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 15:24:08 by yjama             #+#    #+#             */
/*   Updated: 2021/04/27 11:50:19 by yjama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_list_remove_one_if(t_list **begin_list, void *data_ref, \
		int (*cmp)(), void (*free_fct)(void *))
{
	t_list	*prev;
	t_list	*next;

	if (!begin_list || !*begin_list)
		return ;
	if (!(*cmp)((*begin_list)->content, data_ref))
	{
		ft_remove_front(begin_list, free_fct);
		return ;
	}
	prev = *begin_list;
	next = (*begin_list)->next;
	while (prev)
	{
		if (next && !(*cmp)(next->content, data_ref))
		{
			prev->next = next->next;
			(*free_fct)(next->content);
			free(next);
			next = prev->next;
			return ;
		}
		prev = prev->next;
		ft_next(&next);
	}
}

void	ft_remove_front(t_list **begin_list, void (*free_fct)(void *))
{
	t_list	*prev;

	prev = *begin_list;
	*begin_list = prev->next;
	(*free_fct)(prev->content);
	prev->content = 0;
	free(prev);
	prev = 0;
}

t_list	*ft_list_find(t_list *begin_list, void *data_ref, \
	size_t n, int (*cmp)())
{
	while (begin_list)
	{
		if (!(*cmp)(begin_list->content, data_ref, n))
			return (begin_list);
		begin_list = begin_list->next;
	}
	return (begin_list);
}

t_list	*ft_node_find(t_list **begin, char *search, int n)
{
	t_list	*node;

	node = ft_list_find(*begin, search, n, &ft_memcmp);
	if (!node)
		return (0);
	if (node == ft_lstlast(*begin))
		return (0);
	return (node);
}
