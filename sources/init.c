/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 08:56:31 by gbertin           #+#    #+#             */
/*   Updated: 2022/11/14 14:47:11 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int	init_struct_mlx(t_mlx *mlx)
{
	mlx->ptr = mlx_init();
	if (!mlx->ptr)
		return (1);
	mlx->win_height = 500;
	mlx->win_width = 1000;
	mlx->win = mlx_new_window(mlx->ptr, mlx->win_width, mlx->win_height, "Cub3D");
	mlx->img = mlx_new_image(mlx->ptr, mlx->win_width, mlx->win_height);
	return (0);
}

static int	init_struct_img(t_general *general)
{
	int		width;
	int		height;
	int		i;

	i = 0;
	// Take path in map file
	general->spts[PLAYER].path = "spt/player.xpm";
	general->spts[WALL].path = "spt/wall.xpm";
	general->spts[FLOOR].path = "spt/floor.xpm";
	while (i < NB_SPRITE)
	{
		general->spts[i].ptr = mlx_xpm_file_to_image(general->mlx.ptr, \
		general->spts[i].path, &width, &height);
		if (!general->spts[i].ptr)
			return (free_img("Error mlx image failed\n", general));
		i++;
	}
	return (0);
}

static float	init_cam(char direction)
{
	if (direction == 'N')
		return 90;
	else if (direction == 'O')
		return 180;
	else if (direction == 'E')
		return 0;
	else if (direction == 'S')
		return 270;
	return 90;
}

static int	init_pos_player(t_general *general)
{
	int	x;
	int	y;

	y = 0;
	while (general->map->matrice[y])
	{
		x = 0;
		while (general->map->matrice[y][x])
		{
			if (is_direction(general->map->matrice[y][x]))
			{
				general->map->pos_x = (float) x + 0.5;
				printf("x = %f\n", general->map->pos_x);
				general->map->pos_y = (float) y + 0.5;
				printf("y = %f\n", general->map->pos_y);
				general->map->angle_cam = init_cam(general->map->matrice[y][x]);
				printf("angle = %f\n", general->map->angle_cam);
				return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	init_struct(t_general *general, char **argv)
{
	ft_memset(general->spts, 0, sizeof(t_spt) * 4);
	if (init_struct_mlx(&(general->mlx)))
		return (1);
	if (init_struct_img(general))
		return (1);
	if (init_map(general, argv[1]))
		return (1);
	if (init_pos_player(general))
		return (1);
	return (0);
}