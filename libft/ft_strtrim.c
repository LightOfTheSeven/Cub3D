/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 09:08:48 by gbertin           #+#    #+#             */
/*   Updated: 2021/12/01 09:52:22 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	s_in_set(char s, char const *set)
{	
	unsigned int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (s == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t			start;
	size_t			end;
	char			*cpy;
	size_t			i;

	start = 0;
	i = 0;
	end = ft_strlen(s1);
	if (!s1)
		return (NULL);
	while (s1[start] != '\0' && s_in_set(s1[start], set))
		start++;
	while (end > start && s_in_set(s1[end - 1], set))
		end--;
	cpy = (char *)malloc(sizeof(*s1) * (end - start + 1));
	if (!cpy)
		return (NULL);
	while (start < end)
		cpy[i++] = s1[start++];
	cpy[i] = '\0';
	return (cpy);
}
