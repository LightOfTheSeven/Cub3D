/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 11:04:02 by gbertin           #+#    #+#             */
/*   Updated: 2022/12/05 14:45:58 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	main(int argc, char **argv)
{
	t_general	general;

	if (argc == 2)
	{
		ft_memset(&general, 0, sizeof(t_general));
		if (init_struct(&general, argv))
		{
			free_general(&general);
			return (1);
		}
		ft_memset(&general.hook, 0, sizeof(t_hook));
		general.hook.down = 0;
		general.hook.right = 0;
		general.hook.up = 0;
		general.hook.left = 0;
		print_map(&general);
		hook(&general);
	}
	return (0);
}
