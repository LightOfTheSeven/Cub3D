/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 09:24:17 by gbertin           #+#    #+#             */
/*   Updated: 2022/12/08 11:47:50 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int	check_end_of_file(int fd)
{
	char	*line;
	int		err;

	err = 0;
	line = get_next_line(fd);
	if (line && !is_space(line))
		err = 1;
	while (line)
	{
		if (!is_space(line))
			err = 1;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (err)
	{
		ft_putstr_fd("Error\nBad format of map\n", 2);
		return (1);
	}
	return (0);
}

static int	goto_map(t_general *general, int *fd, int nb_line, char **line)
{
	int		i;

	i = 0;
	*fd = open(general->filename, O_RDONLY);
	if (*fd < 0)
	{
		ft_putstr_fd("Error\n", 2);
		strerror(errno);
		close(*fd);
		return (0);
	}
	*line = NULL;
	*line = get_next_line(*fd);
	while (line && (i < nb_line || is_space(*line)))
	{
		free(*line);
		*line = get_next_line(*fd);
		i++;
	}
	if (!(*line))
		return (0);
	return (i);
}

static void	set_size_of_matrice(t_general *gnrl, int fd, int begin, char *line)
{
	int		i;

	i = begin;
	while (line)
	{
		if (is_space(line))
		{
			free(line);
			break ;
		}
		if ((int)ft_strlen(line) > gnrl->map_column)
			gnrl->map_column = ft_strlen(line);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	gnrl->map_line = i - begin;
}

static int	malloc_matrice(t_general *general, int fd, int begin, char *line)
{
	int		i;
	int		index;
	size_t	x;
	char	**matrice;

	i = begin;
	index = 0;
	printf("len matrice %d\n", general->map_line);
	matrice = (char **)malloc(sizeof(char *) * (general->map_line + 1));
	if (!matrice)
		return (1);
	ft_memset(matrice, 0, sizeof(char **));
	while (line)
	{
		x = 0;
		matrice[index] = malloc(sizeof(char) * (general->map_column + 1));
		if (!matrice[index])
		{
			free_tab(matrice);
			return (0);
		}
		if (is_space(line))
		{
			free(line);
			break ;
		}
		while ((int)x < general->map_column)
		{
			if (x < ft_strlen(line))
				matrice[index][x] = line[x];
			else
				matrice[index][x] = ' ';
			x++;
		}
		free(line);
		line = get_next_line(fd);
		matrice[index][general->map_column] = '\0';
		i++;
		index++;
	}
	matrice[general->map_line] = NULL;
	general->map->matrice = matrice;
	return (0);
}

int	detect_map(t_general *general, int begin_line)
{
	int		fd;
	char	*line;

	line = NULL;
	begin_line = goto_map(general, &fd, begin_line, &line);
	if (begin_line == 0)
		return (1);
	set_size_of_matrice(general, fd, begin_line, line);
	if (check_end_of_file(fd))
		return (1);
	begin_line = goto_map(general, &fd, begin_line, &line);
	if (begin_line == 0)
		return (1);
	if (malloc_matrice(general, fd, begin_line, line))
		return (1);
	end_gnl(fd);
	print_matrice(general->map);
	return (0);
}
