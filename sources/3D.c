/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3D.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 08:36:08 by gbertin           #+#    #+#             */
/*   Updated: 2022/12/02 15:58:18 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

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
    color = general->spts[1].data[(y * general->spts[1].len + x)];
    if (num_ray == 350)
        printf("x = %d y = %d index = %d color %d len =%d\n", x, y, index, color, general->spts[1].len);
    pixel_draw(general, num_ray, index, color);
}

void    print_a_column(t_general *general, t_hitpoint hitpoint, int num_ray)
{
    int lign;
    double ceil;
    double projection;
    double dst_to_proj;

    dst_to_proj = ((XPIXEL / 2.0) / tan (conversion_radian(32)));
    projection = (1 / hitpoint.dist) * dst_to_proj;
    ceil = (YPIXEL  - projection) / 2;
    lign = 0;
   while (lign < YPIXEL && lign < ceil)
        pixel_draw(general, num_ray, lign++, 0x5DADE2);
    while (lign < YPIXEL && lign < (ceil + projection))
        draw_pixel_from_xpm(general, hitpoint, num_ray, lign++, projection);
        //pixel_draw(general, num_ray, lign++, 0x5DADE2);
    while (lign < YPIXEL)
        pixel_draw(general, num_ray, lign++, 0xF7DC6F);
    return ;
}
