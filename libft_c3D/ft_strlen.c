/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjama <yjama@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 11:48:58 by yjama             #+#    #+#             */
/*   Updated: 2021/04/24 18:59:34 by yjama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *input)
{
	size_t	counter;

	counter = 0;
	while (*input != '\0')
	{
		counter++;
		input++;
	}
	return (counter);
}
