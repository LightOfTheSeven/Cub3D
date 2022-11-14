/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 08:39:52 by gbertin           #+#    #+#             */
/*   Updated: 2021/11/25 09:33:38 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned int	i;
	unsigned char	*p;

	p = (unsigned char *)b;
	i = 0;
	while (i < len)
		p[i++] = (unsigned char)c;
	b = (void *)p;
	return (b);
}
