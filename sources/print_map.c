/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:00:56 by gbertin           #+#    #+#             */
/*   Updated: 2022/11/15 13:48:29 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

/* Matrice de rotation: x' = cos(alpha).x - sin(alpha).y et 
y' = sin(alpha).x + cos(alpha).y */

/*static void	print_ray(t_general *general)
{
	double	vec_dir[2];
	int		n_pixels;
	double	x;
	double	y;
	
	n_pixels = 0;
	printf("%f %f\n", general->map->vector_dir[V_X], general->map->vector_dir[V_Y]);
	vec_dir[V_X] = cos(general->map->angle_cam) * general->map->vector_dir[V_X] - sin(general->map->angle_cam) * general->map->vector_dir[V_Y];
    vec_dir[V_Y] = sin(general->map->angle_cam) * general->map->vector_dir[V_X] + cos(general->map->angle_cam) * general->map->vector_dir[V_Y];
	x = floor(general->map->pos_x) * HEIGHT_TILE;
	y = floor(general->map->pos_y) * WIDTH_TILE;
	x += (general->map->pos_x - floor(general->map->pos_x)) * HEIGHT_TILE + 4;
	y += (general->map->pos_y - floor(general->map->pos_y)) * WIDTH_TILE + 4;
	printf("%f v_x = %f     ||   v_y = %f\n", general->map->angle_cam, vec_dir[V_X], vec_dir[V_Y]);
	while (n_pixels < 300)
	{
		mlx_pixel_put(general->mlx.ptr, general->mlx.win, (int)x, (int)y, 0x00FF00);
		x += vec_dir[V_X];
		y += vec_dir[V_Y];
		n_pixels++;
	}
}*/

static void print_player(t_general *general)
{
	int x;
	int y;

	x = floor(general->map->pos_x) * HEIGHT_TILE;
	y = floor(general->map->pos_y) * WIDTH_TILE;
	x += (general->map->pos_x - floor(general->map->pos_x)) * HEIGHT_TILE; // 4 = moitie du personnage pour centrer sur sa position
	y += (general->map->pos_y - floor(general->map->pos_y)) * HEIGHT_TILE;
	//printf("%d, %d\n", x, y);
	mlx_put_image_to_window(general->mlx.ptr, general->mlx.win, \
			general->spts[PLAYER].ptr, x, y);
}

static void	print_tile(char tile, t_general *general, int x, int y)
{
	if (tile == '1')
		mlx_put_image_to_window(general->mlx.ptr, general->mlx.win, general->spts[WALL].ptr, x, y);
	else if (tile == '0')
		mlx_put_image_to_window(general->mlx.ptr, general->mlx.win, \
			general->spts[FLOOR].ptr, x, y);
	else if (is_direction(tile))
		mlx_put_image_to_window(general->mlx.ptr, general->mlx.win, \
			general->spts[FLOOR].ptr, x, y);
}

int	print_map(t_general *general)
{
	int	row;
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
	print_player(general);
	//print_ray(general);
	print_rayon_face_joueur(general);
	return (0);
}