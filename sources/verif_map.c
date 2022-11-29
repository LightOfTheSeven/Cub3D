/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 09:31:50 by gbertin           #+#    #+#             */
/*   Updated: 2022/11/29 15:03:59 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static void	free_list(t_pos *begin)
{
	t_pos	*tmp;

	tmp = begin;
	while (begin->next)
	{
		tmp = begin;
		begin = begin->next;
		free(tmp);
	}
	free(begin);
}

static t_pos	*create_pos(t_pos *begin, int x, int y)
{
	t_pos	*new;

	new = malloc(sizeof(t_pos));
	if (!new)
		return (NULL);
	new->x = x;
	new->y = y;
	new->next = NULL;
	while (begin->next)
		begin = begin->next;
	begin->next = new;
	return (new);
}

static int	almost_check(t_pos *begin, int x, int y)
{
	t_pos	*node;

	node = begin;
	while (node)
	{
		if ((node->x == x && node->y == y) || begin->x == -1)
			return (1);
		node = node->next;
	}
	return (0);
}

static void	recursive_checker(t_general *general, t_pos *begin, t_pos *new)
{
	t_map	*map;

	map = general->map;
	if (!new)
		begin->x = -1;
	if (map->matrice[new->y][new->x] == '1')
		return ;
	if (map->matrice[new->y][new->x] == ' ')
		begin->x = -1;
	if (begin->x == -1 || (map->matrice[new->y][new->x] == '0'
		&& ((new->x == 0 || new->x == general->map_column - 1)
			|| (new->y == 0 || new->y == general->map_line - 1))))
		begin->x = -1;
	if (!almost_check(begin, new->x - 1, new->y))
		recursive_checker(general, begin, \
		create_pos(begin, new->x - 1, new->y));
	if (!almost_check(begin, new->x, new->y - 1))
		recursive_checker(general, begin, \
		create_pos(begin, new->x, new->y - 1));
	if (!almost_check(begin, new->x + 1, new->y))
		recursive_checker(general, begin, \
		create_pos(begin, new->x + 1, new->y));
	if (!almost_check(begin, new->x, new->y + 1))
		recursive_checker(general, begin, \
		create_pos(begin, new->x, new->y + 1));
}

int	verif_map(t_general *general)
{
	t_pos	*begin;

	begin = NULL;
	begin = malloc(sizeof(t_pos));
	begin->x = general->map->pos_x;
	begin->y = general->map->pos_y;
	begin->next = NULL;
	recursive_checker(general, begin, begin);
	if (begin->x == -1)
	{
		ft_putstr_fd("Error\nCub3D : Map not close\n", 2);
		free_list(begin);
		return (1);
	}
	free_list(begin);
	return (0);
}
