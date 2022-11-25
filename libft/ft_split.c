/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:47:16 by gbertin           #+#    #+#             */
/*   Updated: 2022/11/25 18:47:18 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**free_tab(char **result)
{
	int	i;

	if (!result)
		return (NULL);
	i = 0;
	while (result[i])
	{
		free(result[i]);
		result[i] = NULL;
		i++;
	}
	free (result);
	return (NULL);
}

static int	get_word_end(const char *str, char separator, int i)
{
	while (str[i] && str[i] != separator)
		i++;
	return (i);
}

static int	fill_result(char **result, const char *str, char separator)
{
	int	i;
	int	word_end;

	i = 0;
	while (str[i])
	{
		if (str[i] != separator)
		{
			word_end = get_word_end(str, separator, i);
			*result = ft_calloc(sizeof(**result), word_end - i + 1);
			if (!*result)
				return (1);
			ft_memcpy(*result, str + i, word_end - i);
			result++;
			i = word_end - 1;
		}
		i++;
	}
	return (0);
}

static int	count_words(const char *str, char separator)
{
	int	i;
	int	nb_words;

	i = 0;
	nb_words = 0;
	while (str[i] == separator)
		i++;
	while (str[i])
	{
		if (str[i] != separator)
		{
			nb_words++;
			while (str[i] && str[i] != separator)
				i++;
		}
		if (str[i])
			i++;
	}
	return (nb_words);
}

char	**ft_split(const char *str, char separator)
{
	char	**result;

	result = ft_calloc(sizeof(*result), count_words(str, separator) + 1);
	if (!result)
		return (NULL);
	if (!fill_result(result, str, separator))
		return (free_tab(result));
	return (result);
}