/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:00:56 by gbertin           #+#    #+#             */
/*   Updated: 2022/11/30 10:02:17 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

/*static void print_player(t_general *general)
{
	int	x;
	int	y;

	x = floor(general->map->pos_x) * HEIGHT_TILE;
	y = floor(general->map->pos_y) * WIDTH_TILE;
	x += (general->map->pos_x - floor(general->map->pos_x)) * HEIGHT_TILE;
	y += (general->map->pos_y - floor(general->map->pos_y)) * HEIGHT_TILE;
	mlx_put_image_to_window(general->mlx.ptr, general->mlx.win, \
			general->spts[PLAYER].ptr, x, y);
}*/

/*static void	print_tile(char tile, t_general *general, int x, int y)
{
	if (tile == '1')
		mlx_put_image_to_window(general->mlx.ptr, \
			general->mlx.win, general->spts[east].ptr, x, y);
	else if (tile == '0')
		mlx_put_image_to_window(general->mlx.ptr, general->mlx.win, \
			general->spts[nord].ptr, x, y);
	else if (is_direction(tile))
		mlx_put_image_to_window(general->mlx.ptr, general->mlx.win, \
			general->spts[FLOOR].ptr, x, y);
}*/

int	print_map(t_general *general)
{
	/*int	row;
	int	col;
	int	x;
	int	y;

	y = 0;
	row = 0;
	while (general->map->matrice[row])
	{
		col = 0;
		x = 0;
		while (general->map->matrice[row][col])
		{
			print_tile(general->map->matrice[row][col], general, x, y);
			col++;
			x += WIDTH_TILE;
		}
		y += HEIGHT_TILE;
		row++;
	}
	print_player(general);*/
	mlx_destroy_image(general->mlx.ptr, general->mlx.img);
	init_raycasting(general);
	return (0);
}
