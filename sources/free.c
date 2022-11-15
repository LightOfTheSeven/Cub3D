/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 09:19:55 by gbertin           #+#    #+#             */
/*   Updated: 2022/11/15 08:10:06 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	free_img(char *err, t_general *general)
{
	int	i;

	i = 0;
	while (i < NB_SPRITE)
	{
		if (general->spts[i].ptr != NULL)
			mlx_destroy_image(general->mlx.ptr, general->spts[i].ptr);
		i++;
	}
	free (general->mlx.img);
	if (general->mlx.win)
		mlx_destroy_window(general->mlx.ptr, general->mlx.win);
	mlx_destroy_display(general->mlx.ptr);
	free(general->mlx.ptr);
	return (ft_putstr_fd(err, 2), 1);
}

int free_general(t_general *general)
{
	int i;

	i = 0;
	if (general->map->matrice)
	{
		if (general->map->matrice[i])
		{
			while (general->map->matrice[i])
			{
				free(general->map->matrice[i]);
				i++;
			}
		}
	}
	free(general->map->matrice);
	free(general->map);
	return 0;
}