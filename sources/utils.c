/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 18:43:15 by gbertin           #+#    #+#             */
/*   Updated: 2022/11/24 18:43:16 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int is_direction(char c)
{
    if (c == 'N' || c == 'O' || c == 'S' || c == 'E')
        return 1;
    return 0;
}

int count_tab(char **tab)
{
    int i;

    i = 0;
    if (!tab)
        return (0);
    while (tab[i])
        i++;
    return (i);
}