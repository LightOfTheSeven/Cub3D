/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_direction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 10:03:48 by gbertin           #+#    #+#             */
/*   Updated: 2022/11/30 10:25:11 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int is_direction(char c)
{
    if (c == 'N' || c == 'O' || c == 'S' || c == 'E')
        return 1;
    return 0;
}

void change_direction(t_general *general, double angle)
{
	if (angle <= 135 && angle >= 45)
		general->direction = NO;
	else if (angle <= 315 && angle >= 225)
		general->direction = SO;
	else if (angle <= 225 && angle >= 135)
		general->direction = WE;
	else if ((angle >= 315 && angle <= 360) || (angle >= 0 && angle <= 45))
		general->direction = EA;
}