/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 14:45:45 by gbertin           #+#    #+#             */
/*   Updated: 2022/12/05 14:57:50 by gbertin          ###   ########.fr       */
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
		update_pos_x(general, 0.04);
	else if (general->direction == SO)
		update_pos_x(general, -0.04);
	else if (general->direction == WE)
		update_pos_y(general, -0.04);
	else if (general->direction == EA)
		update_pos_y(general, 0.04);
}

static void right(t_general *general)
{
	if (general->direction == NO)
		update_pos_x(general, -0.04);
	else if (general->direction == SO)
		update_pos_x(general, 0.04);
	else if (general->direction == WE)
		update_pos_y(general, 0.04);
	else if (general->direction == EA)
		update_pos_y(general, -0.04);
}

static int	key_hook(int keycode, t_general *general)
{
    if (keycode == A_KEY)
	{
    	general->hook.left = 1;
	}
	if (keycode == D_KEY)
    	general->hook.right = 1;
	if (keycode == W_KEY)
		general->hook.up = 1;
	if (keycode == S_KEY)
        general->hook.down = 1;
    if (keycode == R_ARW)
		general->hook.rotate_right = 1;
	if (keycode == L_ARW)
		general->hook.rotate_left = 1;
	if (keycode == ESC)
		exit_mlx(general); 
	return (0);
}

int	key_release(int keycode, t_general *general)
{
	 if (keycode == A_KEY)
    	general->hook.left = 0;
	if (keycode == D_KEY)
    	general->hook.right = 0;
	if (keycode == W_KEY)
		general->hook.up = 0;
	if (keycode == S_KEY)
        general->hook.down = 0;
    if (keycode == R_ARW)
		general->hook.rotate_right = 0;
	if (keycode == L_ARW)
		general->hook.rotate_left = 0;
	return (0);
}

int	onkeypress(t_general *general)
{
	if (general->hook.left)
       left(general);
	if (general->hook.right)
       right(general);
	if (general->hook.up)
		up(general);
	if (general->hook.down)
        down(general);
	if (general->hook.rotate_left || general->hook.rotate_right)
	{
		if (general->hook.rotate_right)
			general->map->angle_cam += 2.5;
		else
			 general->map->angle_cam -= 2.5;
        if (general->map->angle_cam < 0)
            general->map->angle_cam = general->map->angle_cam + 360;
        if (general->map->angle_cam > 360)
            general->map->angle_cam = general->map->angle_cam - 360;
		change_direction(general, general->map->angle_cam);
	}
	//printf ("HOOK %d %d %d %d %d %d\n", general->hook.left, general->hook.right, general->hook.up, general->hook.down,general->hook.rotate_left, general->hook.rotate_right);
	if (general->hook.left || general->hook.right || general->hook.up || general->hook.down || general->hook.rotate_left || general->hook.rotate_right)
	{
		if (!print_map(general))
			return (1);
	}
	return (0);
}

void	hook(t_general *general)
{
	// printf ("HOOK %d %d %d %d\n", general->hook.down, general->hook.up, general->hook.left, general->hook.right);
	mlx_loop_hook(general->mlx.ptr, &onkeypress, general); // make direction
	
	mlx_hook(general->mlx.win, KeyPress, KeyPressMask, key_hook, general); // set direction
    mlx_hook(general->mlx.win, KeyRelease, KeyReleaseMask, &key_release, general); // unset direction
	mlx_hook(general->mlx.win, DestroyNotify, 0, exit_mlx, general); // exit
	mlx_loop(general->mlx.ptr);
}
