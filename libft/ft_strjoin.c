/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 08:51:45 by gbertin           #+#    #+#             */
/*   Updated: 2021/12/01 09:50:40 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static void	*ft_memalloc(size_t size)
{
	void	*new_memory;

	new_memory = malloc(size);
	if (new_memory)
	{
		ft_bzero(new_memory, size);
		return (new_memory);
	}
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	len_s;
	char			*new_s;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	len_s = ft_strlen(s1) + ft_strlen(s2) + 1;
	new_s = (char *)ft_memalloc(len_s);
	if (!new_s)
		return (NULL);
	while (s1[i] != '\0')
	{
		new_s[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
		new_s[i++] = s2[j++];
	new_s[i] = '\0';
	return (new_s);
}
