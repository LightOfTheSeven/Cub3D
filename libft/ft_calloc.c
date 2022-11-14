/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 09:16:45 by gbertin           #+#    #+#             */
/*   Updated: 2021/12/08 13:21:30 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void			*ptr;

	size = count * size;
	ptr = (void *)malloc(size);
	if (ptr == NULL)
		return (ptr);
	ft_bzero(ptr, size);
	return (ptr);
}
