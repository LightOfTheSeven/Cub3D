/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 09:34:08 by gbertin           #+#    #+#             */
/*   Updated: 2021/12/01 10:23:25 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strcpy(char *dst, const char *src)
{
	unsigned int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strdup(const char *s1)
{
	int		length;
	char	*tmp;

	length = ft_strlen(s1);
	tmp = (char *) malloc(sizeof(char) * length + 1);
	if (tmp == NULL)
		return (NULL);
	ft_strcpy(tmp, s1);
	return (tmp);
}
