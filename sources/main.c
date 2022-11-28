/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 11:04:02 by gbertin           #+#    #+#             */
/*   Updated: 2022/11/28 12:32:06 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"



int main(int argc, char **argv)
{
	t_general general;
	
	if (argc == 2)
	{
		ft_memset(&general, 0, sizeof(t_general));
		if (init_struct(&general, argv))
		{
			free_general(&general);
			return (1);
		}
		print_map(&general);
		hook(&general);
	}
	return (0);
}
