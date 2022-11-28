/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 09:19:55 by gbertin           #+#    #+#             */
/*   Updated: 2022/11/28 12:52:05 by gbertin          ###   ########.fr       */
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
	if (general->mlx.win)
		mlx_destroy_window(general->mlx.ptr, general->mlx.win);
	mlx_destroy_display(general->mlx.ptr);
	free(general->mlx.ptr);
	return (ft_putstr_fd(err, 2), 1);
}

void free_spts(t_general *general)
{
	int i;

	i = 1;
	while(i < NB_SPRITE)
	{	
		if (general->spts[i].path)
			free(general->spts[i].path);
		//if (general->spts[i].ptr != NULL)
		//	mlx_destroy_image(general->mlx.ptr, general->spts[i].ptr);
		i++;
	}
}

void free_tab(char **tab) //free les tableaux contenant un \0 ou un NULL a la fin
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int free_general(t_general *general)
{
	if (general->map->matrice)
		free_tab(general->map->matrice);
	free_spts(general);
	free(general->map);
	return 0;
}