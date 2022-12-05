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

double calcul_x(double angle)
{
	double x;

	if (angle > 360)
		angle -= 360;
	if (angle < 0)
		angle += 360;
	x = cos(conversion_radian(angle)) * 0.04;
	return (x);
}

double calcul_y(double angle)
{
	double y;

	if (angle > 360)
		angle -= 360;
	if (angle < 0)
		angle += 360;
	y = sin(conversion_radian(angle * -1)) * 0.04;
	return (y);
}

static void	up(t_general *general)
{
	general->map->pos_x += calcul_x(general->map->angle_cam);
	general->map->pos_y += calcul_y(general->map->angle_cam);
}

static void down(t_general *general)
{
	general->map->pos_x -= calcul_x(general->map->angle_cam);
	general->map->pos_y -= calcul_y(general->map->angle_cam);
}

static void left(t_general *general)
{
	general->map->pos_x += calcul_x(general->map->angle_cam + 90);
	general->map->pos_y += calcul_y(general->map->angle_cam + 90);
}

static void right(t_general *general)
{
	general->map->pos_x += calcul_x(general->map->angle_cam - 90);
	general->map->pos_y += calcul_y(general->map->angle_cam - 90);
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
		//change_direction(general, general->map->angle_cam);
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
