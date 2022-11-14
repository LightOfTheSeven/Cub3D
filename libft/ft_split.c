/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 08:59:50 by gbertin           #+#    #+#             */
/*   Updated: 2021/12/27 14:43:47 by gbertin          ###   ########.fr       */
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

static int	ft_nbwords(char const *s, char c)
{
	unsigned int	nb_words;
	unsigned int	i;

	nb_words = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && s[i] == c)
			i++;
		if (s[i] != '\0' && s[i] != c)
		{
			while (s[i] != '\0' && s[i] != c)
				i++;
			nb_words++;
		}
	}
	return (nb_words);
}

static int	ft_strlenc(const char *s, char c)
{
	unsigned int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0' && s[i] != c)
		i++;
	return (i);
}

static char	*ft_mallocstrc(char *dest, char const *src, char c)
{
	unsigned int	size;
	unsigned int	i;

	i = 0;
	size = ft_strlenc(src, c);
	dest = malloc(size + 1);
	if (!dest)
		return (NULL);
	while (src[i] != '\0' && src[i] != c)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	**ft_split(char const *s, char c)
{
	unsigned int	i;
	unsigned int	y;
	char			**new_strs;

	i = 0;
	y = 0;
	new_strs = ft_memalloc(sizeof(char *) * (ft_nbwords(s, c) + 1));
	if (!new_strs)
		return (0);
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && s[i] == c)
			i++;
		if (s[i] != c && s[i] != '\0')
		{
			new_strs[y] = ft_mallocstrc(new_strs[y], &s[i], c);
			if (!new_strs[y])
				return (NULL);
			i += ft_strlenc(&s[i], c);
			y++;
		}
	}
	new_strs[y] = NULL;
	return (new_strs);
}
