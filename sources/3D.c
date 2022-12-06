/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3D.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 08:36:08 by gbertin           #+#    #+#             */
/*   Updated: 2022/12/06 14:27:59 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int     convert_color(int color[3])
{
    int ret_v;

    ret_v = 0;
    ret_v += (color[2] % 16) * pow(16, 1);
    ret_v += (color[2] / 16) * pow(16, 2);
    ret_v += (color[1] % 16) * pow(16, 3);
    ret_v += (color[1] / 16) * pow(16, 4);
    ret_v += (color[0] % 16) * pow(16, 5);
    ret_v += (color[0] / 16) * pow(16, 6);
    return (ret_v); 
}

void	pixel_draw(t_general *general, int x, int y, int color)
{
	char	*dst;

    // if (x == 1)
    // {
        
    //     printf("pos y %d pos x %d\n", y, x);
    // }
	dst = general->mlx.addr + (y * general->mlx.len + x * (general->mlx.bpp / 8));
	*(unsigned int *)dst = color;
}

void    init_image(t_general *general)
{
    general->mlx.img = mlx_new_image(general->mlx.ptr, general->mlx.win_width, general->mlx.win_height);
    general->mlx.addr = mlx_get_data_addr(general->mlx.img, &general->mlx.bpp, &general->mlx.len, &general->mlx.endian);
}

 void draw_pixel_from_xpm(t_general *general, t_hitpoint hitpoint, int num_ray, int lign, int projection)
{
    int     color;
    double  ratio;
    int     x;
    int     y;
    int     index;
    (void)projection;
    
    x = 0;
    y = 0;
    ratio = 0;
    index = lign;
    lign = lign - ((YPIXEL - projection) / 2);
    ratio = lign / (double)projection;
    y = (64 * ratio);
    //hitpoint.x = cos(conversion_radian(hitpoint.angle));
    //hitpoint.y = sin(conversion_radian(hitpoint.angle));
    if (hitpoint.x - floor(hitpoint.x) == 0) // vertical
    {
        ratio = hitpoint.y - floor(hitpoint.y);
        x = round(64 * ratio);
    }
    else // horizontal
    {
        ratio = hitpoint.x - floor(hitpoint.x);
        x = round(64 * ratio);
    }
    color = general->spts[hitpoint.dir].data[(y * general->spts[hitpoint.dir].len + x)];
    pixel_draw(general, num_ray, index, color);
}

void    print_a_column(t_general *general, t_hitpoint hitpoint, int num_ray)
{
    int lign;
    double ceil;
    double projection;
    double dst_to_proj;
    int     color[2];
    
    color[0] = convert_color(general->ceil_color);
    color[1] = convert_color(general->floor_color);
    dst_to_proj = ((XPIXEL / 2.0) / tan (conversion_radian(32)));
    projection = (1 / hitpoint.dist) * dst_to_proj;
    ceil = (YPIXEL  - projection) / 2;
    lign = 0;
    while (lign < YPIXEL && lign < ceil)
    {
        pixel_draw(general, num_ray, lign++, color[0]);
    }
	// if ((hitpoint.x <= 0 || hitpoint.x > general->map_column) || (hitpoint.y <= 0 || hitpoint.y > general->map_line - 1))
    // {
    //     while (lign - ceil < projection / 2)
    //         pixel_draw(general, num_ray, lign++, color[0]);
    //     while(lign - ceil < projection)
    //         pixel_draw(general, num_ray, lign++, color[1]);
    // }
    while (lign < YPIXEL && lign < (ceil + projection))
        draw_pixel_from_xpm(general, hitpoint, num_ray, lign++, projection);
    while (lign < YPIXEL)
        pixel_draw(general, num_ray, lign++, color[1]);
    return ;
}
