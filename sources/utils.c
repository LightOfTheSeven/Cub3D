/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 18:43:15 by gbertin           #+#    #+#             */
/*   Updated: 2022/11/29 15:02:11 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	print_matrice(t_map *map)
{
	int	i;

	i = 0;
	if (!map->matrice)
	{
		ft_putstr_fd("Matrice not set\n", 2);
		return ;
	}
	while (map->matrice[i])
	{
		printf("%s\n", map->matrice[i]);
		i++;
	}
}

void	end_gnl(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

int	is_direction(char c)
{
	if (c == 'N' || c == 'O' || c == 'S' || c == 'E')
		return (1);
	return (0);
}

int	count_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (0);
	while (tab[i])
		i++;
	return (i);
}

int	is_space(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strndup(const char *s, int n)
{
	char	*dest;
	int		size;
	int		i;

	size = 0;
	i = 0;
	size = ft_strlen((char *)s);
	dest = (char *) malloc ((size + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	while (i < size && i < n)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	only_int(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (1);
	while (line[i])
	{
		if (!ft_isdigit(line[i]))
			return (1);
		i++;
	}
	return (0);
}
