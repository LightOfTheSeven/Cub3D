/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 14:45:45 by gbertin           #+#    #+#             */
/*   Updated: 2022/12/08 11:41:43 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

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

int	onkeypress(t_general *g)
{
	if (g->hook.left)
		left(g);
	if (g->hook.right)
		right(g);
	if (g->hook.up)
		up(g);
	if (g->hook.down)
		down(g);
	if (g->hook.rotate_left || g->hook.rotate_right)
	{
		if (g->hook.rotate_right)
			g->map->angle_cam -= 2;
		else
			g->map->angle_cam += 2;
		if (g->map->angle_cam < 0)
			g->map->angle_cam = g->map->angle_cam + 360;
		if (g->map->angle_cam > 360)
			g->map->angle_cam = g->map->angle_cam - 360;
	}
	if (g->hook.left || g->hook.right || g->hook.up || g->hook.down
		|| g->hook.rotate_left || g->hook.rotate_right)
	{
		if (!print_map(g))
			return (1);
	}
	return (0);
}

void	hook(t_general *g)
{
	mlx_loop_hook(g->mlx.ptr, &onkeypress, g);
	mlx_hook(g->mlx.win, KeyPress, KeyPressMask, key_hook, g);
	mlx_hook(g->mlx.win, KeyRelease, KeyReleaseMask, &key_release, g);
	mlx_hook(g->mlx.win, DestroyNotify, 0, exit_mlx, g);
	mlx_loop(g->mlx.ptr);
}
