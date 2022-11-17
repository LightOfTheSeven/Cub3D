#include "../include/cub3D.h"

static void handle_mouvement(int keycode, t_general *general)
{
	double	new_y;
	double	new_x;

	new_x = general->map->pos_x;
	new_y = general->map->pos_y;
	if (keycode == A_KEY)
    	new_x -= SPEED / 100;
	else if (keycode == D_KEY)
       new_x += SPEED / 100;
	else if (keycode == W_KEY)
		new_y -= SPEED / 100;
	else if (keycode == S_KEY)
        new_y += SPEED / 100;
	if (general->map->matrice[(int)ceil(new_y)][(int)ceil(general->map->pos_x)] == '1')
		return ;
	general->map->pos_x = new_x;
	general->map->pos_y = new_y;
}

static void	handle_rotate_cam(int keycode, t_general *general)
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

static int	key_hook(int keycode, t_general *general)
{
	int new_win;

	new_win = 0;
	if (keycode == A_KEY || keycode == D_KEY || keycode == W_KEY || keycode == S_KEY)
	{
		handle_mouvement(keycode, general);
		new_win = 1;
	}
    else if (keycode == R_ARW || keycode == L_ARW)
	{
		handle_rotate_cam(keycode, general);
		new_win = 1;
	}
	else if (keycode == ESC)
		exit_mlx(general);
	if (new_win)
	{
		if (!print_map(general))
			return (1);
	}
	return (0);
}

void	hook(t_general *general)
{
    mlx_hook(general->mlx.win, 33, 1L << 17, exit_mlx, general); //si on ferme avec la souris
    mlx_hook(general->mlx.win, 2, 1L << 0, key_hook, general); //tant que la touche est appuyé
    //mlx_key_hook(general->mlx.win, hook_manager, general) --> pas bon parce que la touche doit etre relevé
    mlx_loop(general->mlx.ptr);
}