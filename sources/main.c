/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 11:04:02 by gbertin           #+#    #+#             */
/*   Updated: 2022/11/14 14:47:27 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void 	print_matrice(t_map *map)
{
	int i;

	i = 0;
	while (map->matrice[i])
	{
		printf("%s", map->matrice[i]);
		i++;
	}
}

int	hook_manager(int keycode, t_general *general)
{
	if (keycode == L_ARW || keycode == A_KEY)
		ft_putstr_fd("left\n", 1);
	else if (keycode == R_ARW || keycode == D_KEY)
		ft_putstr_fd("right\n", 1);
	else if (keycode == UP_ARW || keycode == W_KEY)
		ft_putstr_fd("up\n", 1);
	else if (keycode == DOWN_ARW || keycode == S_KEY)
		ft_putstr_fd("down\n", 1);
	else if (keycode == ESC)
		ft_putstr_fd("exit\n", 1);
	if (!print_map(general))
		return (0);
	return (0);
}

int main(int argc, char **argv)
{
	t_general general;
	
	if (argc == 2)
	{
		ft_memset(&general, 0, sizeof(t_general));
		if (init_struct(&general, argv))
			return (1);
		print_map(&general);
		print_matrice(general.map);
		mlx_key_hook(general.mlx.win, hook_manager, &general);
		//mlx_hook(general.mlx.win, 17, 0, &ft_close, &general);
		mlx_loop(general.mlx.ptr);
	}
	return (0);
}
