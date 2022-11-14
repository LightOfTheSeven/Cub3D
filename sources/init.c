/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 08:56:31 by gbertin           #+#    #+#             */
/*   Updated: 2022/11/14 10:57:10 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int	init_struct_mlx(t_mlx *mlx)
{
	mlx->ptr = mlx_init();
	if (!mlx->ptr)
		return (1);
	mlx->win_height = 1080;
	mlx->win_width = 1920;
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
		printf("%s\n", general->spts[i].path);
		general->spts[i].ptr = mlx_xpm_file_to_image(general->mlx->ptr, \
		general->spts[i].path, &width, &height);
		if (!general->spts[i].ptr)
			return (free_img("Error mlx image failed\n", general));
		i++;
	}
	return (0);
}

int	init_struct(t_general *general, char **argv)
{
	t_mlx	  mlx;

	ft_memset(&mlx, 0, sizeof(t_mlx));
	general->mlx = &mlx;
	ft_memset(general->spts, 0, sizeof(t_mlx));
	if (init_struct_mlx(general->mlx))
		return (1);
	if (init_struct_img(general))
		return (1);
	if (init_map(general, argv[1]))
		return (1);
	return (0);
}