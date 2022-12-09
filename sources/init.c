/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 08:56:31 by gbertin           #+#    #+#             */
/*   Updated: 2022/12/09 16:00:00 by gbertin          ###   ########.fr       */
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

static int	init_struct_img(t_general *g)
{
	int		i;

	i = 0;
	while (i < NB_SPRITE)
	{
		g->spts[i].ptr = mlx_xpm_file_to_image(g->mlx.ptr, \
		g->spts[i].path, &g->spts[i].width, &g->spts[i].height);
		if (!g->spts[i].ptr)
			return (free_img("Error\nCub3D : mlx image failed\n", g));
		g->spts[i].data = (int *)mlx_get_data_addr(g->spts[i].ptr,
				&g->spts[i].bpp, &g->spts[i].len, &g->spts[i].endian);
		g->spts[i].len /= 4;
		if (g->spts[i].width != g->spts[i].height)
			return (free_img("Error\nCub3D : Sprite is not Square\n", g));
		i++;
	}
	return (0);
}

double	init_cam(char direction)
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

static void	init_general(t_general *general, char **argv)
{
	int		i;

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
