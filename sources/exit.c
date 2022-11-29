/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 12:35:08 by gbertin           #+#    #+#             */
/*   Updated: 2022/11/29 12:35:49 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	exit_mlx(t_general *general)
{
	free_general(general);
	free_img("EXIT\n", general);
	exit(EXIT_SUCCESS);
	return (0);
}
