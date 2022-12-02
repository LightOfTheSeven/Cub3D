/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 08:56:31 by gbertin           #+#    #+#             */
/*   Updated: 2022/12/02 15:48:18 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int	init_struct_mlx(t_mlx *mlx)
{
	mlx->ptr = mlx_init();
	if (!mlx->ptr)
		return (1);
	mlx->win_height = YPIXEL;
	mlx->win_width = XPIXEL;
	mlx->win = mlx_new_window(mlx->ptr, \
		mlx->win_width, mlx->win_height, "Cub3D");
	return (0);
}

static int	init_struct_img(t_general *general)
{
	int		width;
	int		height;
	int		i;

	i = 0;
	while (i < NB_SPRITE)
	{
		printf("PATH TO SPRITE = %s %d\n", general->spts[i].path, i);
		general->spts[i].ptr = mlx_xpm_file_to_image(general->mlx.ptr, \
		general->spts[i].path, &width, &height);
		if (!general->spts[i].ptr)
		{
			return (free_img("Error\nCub3D : mlx image failed\n", general));
		}
		general->spts[i].data = (int *)mlx_get_data_addr(general->spts[i].ptr, &general->spts[i].bpp, &general->spts[i].len, &general->spts[i].endian);
		general->spts[i].len /= 4;
		//printf("color = %d\n", general->spts[i].data[1]);
		i++;
	}
	return (0);
}

static double	init_cam(char direction)
{
	if (direction == 'N')
		return (90);
	else if (direction == 'O')
		return (180);
	else if (direction == 'E')
		return (0);
	else if (direction == 'S')
		return (270);
	return (90);
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
					general->map->pos_x = (double) x + 0.5;
					general->map->pos_y = (double) y + 0.5;
					general->map->angle_cam = init_cam(general->map->matrice[y][x]);
					have_player = 0;
				}
				else
				{
					ft_putstr_fd("Error\nCub3D : Too many players\n", 2);
					return (1);
				}
			}
			else if (!is_direction(general->map->matrice[y][x]) && general->map->matrice[y][x] != '0' && general->map->matrice[y][x] != '1' && general->map->matrice[y][x] != ' ')
			{
				ft_putstr_fd("Error\nCub3D : Invalid caracters\n", 2);
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

static void	init_general(t_general *general, char **argv)
{
	int	i;

	i = 0;
	general->filename = argv[1];
	general->floor_color[0] = -1;
	general->ceil_color[0] = -1;
	while (i < NB_SPRITE)
	{
		general->spts[i].path = NULL;
		general->spts[i].ptr = NULL;
		i++;
	}
	general->spts[player].path = "spt/player.xpm";
	general->map_column = 0;
	general->map_line = 0;
}

int	init_struct(t_general *general, char **argv)
{
	ft_memset(general->spts, 0, sizeof(t_spt) * NB_SPRITE);
	init_general(general, argv);
	if (init_map(general))
		return (1);
	if (init_pos_player(general))
		return (1);
	if (verif_map(general))
		return (1);
	if (init_struct_mlx(&(general->mlx)))
		return (1);
	if (init_struct_img(general))
		return (1);
	init_raycasting(general);
	return (0);
}
