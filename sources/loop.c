/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 08:53:36 by gbertin           #+#    #+#             */
/*   Updated: 2022/11/17 08:54:23 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static void	up(t_general *general)
{
	double	old_y;
	//check wall
	old_y = general->map->pos_y;
	general->map->pos_y -= 0.04;
	if (floor(old_y) != floor(general->map->pos_y))
		change_minimap(general->map);
}

static void down(t_general *general)
{
	double	old_y;
	//check wall
	old_y = general->map->pos_y;
	general->map->pos_y += 0.04;
	if (floor(old_y) != floor(general->map->pos_y))
		change_minimap(general->map);
}

static void left(t_general *general)
{
	double	old_x;
	//check wall
	old_x = general->map->pos_x;
	general->map->pos_x -= 0.04;
	if (floor(old_x) != floor(general->map->pos_x))
		change_minimap(general->map);
}

static void right(t_general *general)
{
	double	old_x;
	//check wall
	old_x = general->map->pos_x;
	general->map->pos_x += 0.04;
	if (floor(old_x) != floor(general->map->pos_x))
		change_minimap(general->map);
}

static int	key_hook(int keycode, t_general *general)
{
    if (keycode == A_KEY)
       left(general);
	else if (keycode == D_KEY)
       right(general);
	else if (keycode == W_KEY)
		up(general);
	else if (keycode == S_KEY)
        down(general);
    else if (keycode == R_ARW || keycode == L_ARW)
    {
		if (keycode == R_ARW)
			general->map->angle_cam -= 1;
		else
			 general->map->angle_cam += 1;
        if (general->map->angle_cam < 0)
            general->map->angle_cam = general->map->angle_cam + 360;
        if (general->map->angle_cam > 360)
            general->map->angle_cam = general->map->angle_cam - 360;
    }
	else if (keycode == ESC)
		exit_mlx(general); 
	if (!print_map(general))
		return (1);
	return (0);
}

void	hook(t_general *general)
{
    mlx_hook(general->mlx.win, 33, 1L << 17, exit_mlx, general); //si on ferme avec la souris
    mlx_hook(general->mlx.win, 2, 1L << 0, key_hook, general); //tant que la touche est appuyé
    //mlx_key_hook(general->mlx.win, hook_manager, general) --> pas bon parce que la touche doit etre relevé
    mlx_loop(general->mlx.ptr);
}