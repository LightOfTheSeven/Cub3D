/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_direction.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 09:53:18 by gbertin           #+#    #+#             */
/*   Updated: 2022/12/08 10:11:13 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	up(t_general *general)
{
	general->map->pos_x += calcul_x(general->map->angle_cam, general, 0);
	general->map->pos_y += calcul_y(general->map->angle_cam, general, 0);
}

void	down(t_general *general)
{
	general->map->pos_x -= calcul_x(general->map->angle_cam, general, 1);
	general->map->pos_y -= calcul_y(general->map->angle_cam, general, 1);
}

void	left(t_general *general)
{
	general->map->pos_y += calcul_y(general->map->angle_cam + 90, general, 0);
	general->map->pos_x += calcul_x(general->map->angle_cam + 90, general, 0);
}

void	right(t_general *general)
{
	general->map->pos_x += calcul_x(general->map->angle_cam - 90, general, 0);
	general->map->pos_y += calcul_y(general->map->angle_cam - 90, general, 0);
}
