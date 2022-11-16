/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 11:04:02 by gbertin           #+#    #+#             */
/*   Updated: 2022/11/16 20:41:20 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void 	print_matrice(t_map *map)
{
	(void)map;
	// int i;

	// i = 0;
	// while (map->minimap[i])
	// {
		
	// 	printf("%sC\n", map->minimap[i]);
	// 	i++;
	// }
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
		hook(&general);
	}
	return (0);
}
