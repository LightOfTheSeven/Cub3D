/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 08:56:31 by gbertin           #+#    #+#             */
/*   Updated: 2022/11/23 12:00:27 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int	init_struct_mlx(t_mlx *mlx)
{
	mlx->ptr = mlx_init();
	if (!mlx->ptr)
		return (1);
	mlx->win_height = HEIGHT_MINIMAP * HEIGHT_TILE;
	mlx->win_width = WIDTH_MINIMAP * WIDTH_TILE;
	mlx->win = mlx_new_window(mlx->ptr, mlx->win_width, mlx->win_height, "Cub3D");
	return (0);
}

static int	init_struct_img(t_general *general)
{
	int		width;
	int		height;
	int		i;

	i = 0;
	// Take path in map file
	while (i < NB_SPRITE)
	{
		general->spts[i].ptr = mlx_xpm_file_to_image(general->mlx.ptr, \
		general->spts[i].path, &width, &height);
		if (!general->spts[i].ptr)
		{
			free_general(general);
			return (free_img("Error mlx image failed\n", general));
		}
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
	int	have_player;

	y = 0;
	have_player = 1;
	while (general->map->matrice[y])
	{
		x = 0;
		while (general->map->matrice[y][x])
		{
			if (is_direction(general->map->matrice[y][x]))
			{
				if (have_player)
				{
					general->map->pos_x = (float) x + 0.5;
					general->map->pos_y = (float) y + 0.5;
					general->map->angle_cam = init_cam(general->map->matrice[y][x]);
					have_player = 0;
				}
				else
				{
					write(2, "Error : Too many players\n", 26);
					return (1);
				}
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	init_struct(t_general *general, char **argv)
{
	ft_memset(general->spts, 0, sizeof(t_spt) * NB_SPRITE);
	if (init_map(general, argv[1]))
	{
		printf("N %sS %sW %sE %s\n", general->spts[NORD].path, general->spts[SUD].path, general->spts[WEST].path, general->spts[EAST].path);
		printf("F %d %d %d C %d %d %d\n", general->floor_color[0], general->floor_color[1], general->floor_color[2], general->ceil_color[0], general->ceil_color[1], general->ceil_color[2]);
		return (1);
	}
	if (init_struct_mlx(&(general->mlx)))
		return (1);
	if (init_struct_img(general))
		return (1);
	if (init_pos_player(general))
		return (1);
	return (0);
}