/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 09:19:55 by gbertin           #+#    #+#             */
/*   Updated: 2022/11/14 09:58:10 by gbertin          ###   ########.fr       */
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
			mlx_destroy_image(general->mlx->ptr, general->spts[i].ptr);
		i++;
	}
	mlx_destroy_display(general->mlx->ptr);
	free(general->mlx->ptr);
	return (ft_putstr_fd(err, 2), 1);
}