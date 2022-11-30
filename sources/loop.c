/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 14:45:45 by gbertin           #+#    #+#             */
/*   Updated: 2022/11/30 10:24:53 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void update_pos_x(t_general *general, double val)
{
	double	x;

	x = general->map->pos_x + val;
	if (x <= 1)
		return ;
	if (x >= general->map_column - 1)
		return ;
	general->map->pos_x = x;
}

void update_pos_y(t_general *general, double val)
{
	double	y;

	y = general->map->pos_y + val;
	if (y <= 1)
		return ;
	if (y >= general->map_line - 1)
		return ;
	general->map->pos_y = y;

}

static void	up(t_general *general)
{
	if (general->direction == NO)
		update_pos_y(general, -0.04);
	else if (general->direction == SO)
		update_pos_y(general, 0.04);
	else if (general->direction == WE)
		update_pos_x(general, -0.04);
	else if (general->direction == EA)
		update_pos_x(general, 0.04);
}

static void down(t_general *general)
{
	if (general->direction == NO)
		update_pos_y(general, 0.04);
	else if (general->direction == SO)
		update_pos_y(general, -0.04);
	else if (general->direction == WE)
		update_pos_x(general, 0.04);
	else if (general->direction == EA)
		update_pos_x(general, -0.04);
}

static void left(t_general *general)
{
	if (general->direction == NO)
		update_pos_x(general, -0.04);
	else if (general->direction == SO)
		update_pos_x(general, 0.04);
	else if (general->direction == WE)
		update_pos_y(general, -0.04);
	else if (general->direction == EA)
		update_pos_y(general, 0.04);
}

static void right(t_general *general)
{
	if (general->direction == NO)
		update_pos_y(general, -0.04);
	else if (general->direction == SO)
		update_pos_y(general, 0.04);
	else if (general->direction == WE)
		update_pos_x(general, -0.04);
	else if (general->direction == EA)
		update_pos_x(general, 0.04);
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
			general->map->angle_cam += 1;
		else
			 general->map->angle_cam -= 1;
        if (general->map->angle_cam < 0)
            general->map->angle_cam = general->map->angle_cam + 360;
        if (general->map->angle_cam > 360)
            general->map->angle_cam = general->map->angle_cam - 360;
		change_direction(general, general->map->angle_cam);
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
