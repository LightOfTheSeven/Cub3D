/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 21:49:46 by gbertin           #+#    #+#             */
/*   Updated: 2022/11/14 20:12:35 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_gnl_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_gnl_strcat(char *s1, char *s2)
{
	size_t	size;
	size_t	i;
	size_t	j;
	char	*new;

	i = 0;
	j = 0;
	size = ft_gnl_strlen(s1) + ft_gnl_strlen(s2) + 1;
	new = (char *)malloc(sizeof(char) * size);
	if (!new)
		return (0);
	while (s1[i] != '\0')
	{
		new[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
		new[i++] = s2[j++];
	new[i] = '\0';
	free(s1);
	return (new);
}

char	*ft_gnl_strjoin(char *s1, char *s2)
{
	if (!s1)
	{
		s1 = (char *)malloc(sizeof(char) * 1);
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	return (ft_gnl_strcat(s1, s2));
}
