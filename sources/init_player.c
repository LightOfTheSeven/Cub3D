/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 12:03:00 by gbertin           #+#    #+#             */
/*   Updated: 2022/12/09 10:33:24 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static void	init_player_position(t_general *g, int *have_player, int x, int y)
{
	g->map->pos_x = (double) x + 0.5;
	g->map->pos_y = (double) y + 0.5;
	g->map->angle_cam = init_cam(g->map->matrice[y][x]);
	*have_player = 0;
}

static int	loop_init_player(t_general *general, int *have_player, int x, int y)
{
	if (is_direction(general->map->matrice[y][x]))
	{
		if (have_player)
			init_player_position(general, have_player, x, y);
		else
		{
			ft_putstr_fd("Error\nCub3D : Too many players\n", 2);
			return (1);
		}
	}
	else if (!is_direction(general->map->matrice[y][x]) &&
		general->map->matrice[y][x] != '0' && general->map->matrice[y][x]
		!= '1' && general->map->matrice[y][x] != ' ')
	{
		ft_putstr_fd("Error\nCub3D : Invalid caracters\n", 2);
		return (1);
	}
	return (0);
}

int	init_pos_player(t_general *general)
{
	int	x;
	int	y;
	int	have_player;

	y = 0;
	have_player = 1;
	while (general->map->matrice[y])
	{
		x = 0;
		while (general->map->matrice[y][x])
		{
			if (loop_init_player(general, &have_player, x, y))
				return (1);
			x++;
		}
		y++;
	}
	if (have_player)
	{
		ft_putstr_fd("Error\nCub3D : missing a player\n", 2);
		return (1);
	}
	return (0);
}
