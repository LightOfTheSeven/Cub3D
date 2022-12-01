/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:00:56 by gbertin           #+#    #+#             */
/*   Updated: 2022/11/29 15:09:26 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	print_map(t_general *general)
{
	mlx_destroy_image(general->mlx.ptr, general->mlx.img);
	init_raycasting(general);
	return (0);
}
