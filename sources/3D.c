#include "../include/cub3D.h"

static int convert_color(int color[3])
{
    int     ret_v;

    ret_v = 0;
    ret_v += color[2] % 16;
    ret_v += (color[2] / 16) * pow(1,16);
    ret_v += (color[1] % 16) * pow(1,32);
    ret_v += (color[1] / 16) * pow(1,64);
    ret_v += (color[0] % 16) * pow(1,128);
    ret_v += (color[0] / 16) * pow(1,256);
    return (ret_v);
}

void	pixel_draw(t_general *general, int x, int y, int color)
{
	char	*dst;

	dst = general->mlx.addr + (y * general->mlx.len + x * (general->mlx.bpp / 8));
	*(unsigned int *)dst = color;
}

void    init_image(t_general *general)
{
    //mlx_destroy_image(general->mlx->ptr, mlx->img);
    general->mlx.img = mlx_new_image(general->mlx.ptr, general->mlx.win_width, general->mlx.win_height);
    general->mlx.addr = mlx_get_data_addr(general->mlx.img, &general->mlx.bpp, &general->mlx.len, &general->mlx.endian);
}

//    mlx_put_image_to_window(general->mlx.ptr, general->mlx.win, general->mlx.img, 0, 0);
// void print_pixel_from_xpm(t_general *general, t_hitpoint hitpoint, int i, int index, int size_wall)
// {
//     int     color;
//     // int     abs;
//     // int     ord;
//     // float   ratio;
//     (void)size_wall;

//     if (hitpoint.x - floor(hitpoint.x) != 0) //horizontal
//     {
//         // ratio = hitpoint.x - floor(hitpoint.x);
//         // abs = (int)round(WIDTH_TILE * ratio);
//         // abs = abs;

//         // ratio = index / size_wall;
//         // ord = (int)round(HEIGHT_TILE * ratio);
//         // ord = general->spts[1].len * ord;
//         // color = (int)general->spts[nord].data[ord + abs];
//         color = 0x000000;
//     }
//     else // vertical
//     {
//         //ratio = hitpoint.x - floor(hitpoint.x);
//         color = 0xFFFFFF;
       
//     }
//     pixel_draw(general, i, index, color);
// }

void    print_a_column(t_general *general, float distance, int i)
{
    (void)distance;
    int index;
    float ceil;
    float projection;
    float dst_to_proj;

   // printf("distance = %f\n", distance);
    dst_to_proj = ((XPIXEL / 2.0) / tan (conversion_radian(32)));
    //printf("dst_to_proj = %f\n", dst_to_proj);
    projection = (1 / distance) * dst_to_proj;
    ceil = (YPIXEL  - projection) / 2;
    //printf("ceil = %f\n", ceil);
    index = 0;
   while (index < YPIXEL && index < ceil)
        pixel_draw(general, i, index++, convert_color(general->ceil_color));
    while (index < YPIXEL && index < (ceil + projection))
        pixel_draw(general, i, index++, 0x45B39D);
    while (index < YPIXEL)
        pixel_draw(general, i, index++, convert_color(general->floor_color));
    return ;
}
