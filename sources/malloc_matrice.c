/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_matrice.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 10:02:56 by gbertin           #+#    #+#             */
/*   Updated: 2022/12/09 10:12:11 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int	malloc_line(t_general *g, char *line, char **matrice, int index)
{
	size_t	x;

	x = 0;
	if (is_space(line))
	{
		free(line);
		return (1);
	}
	matrice[index] = malloc(sizeof(char) * (g->map_column + 1));
	if (!matrice[index])
	{
		free_tab(matrice);
		return (1);
	}	
	while ((int)x < g->map_column)
	{
		if (x < ft_strlen(line))
			matrice[index][x] = line[x];
		else
			matrice[index][x] = ' ';
		x++;
	}
	free(line);
	return (0);
}

int	malloc_matrice(t_general *general, int fd, int begin, char *line)
{
	int		i;
	int		index;
	char	**matrice;

	i = begin;
	index = 0;
	matrice = (char **)malloc(sizeof(char *) * (general->map_line + 1));
	if (!matrice)
		return (1);
	ft_memset(matrice, 0, sizeof(char **));
	while (line)
	{
		if (malloc_line(general, line, matrice, index))
			return (1);
		line = get_next_line(fd);
		matrice[index][general->map_column] = '\0';
		i++;
		index++;
	}
	matrice[general->map_line] = NULL;
	general->map->matrice = matrice;
	return (0);
}
