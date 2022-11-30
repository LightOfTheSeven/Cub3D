#include "../include/cub3D.h"

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

void    print_a_column(t_general *general, float distance, int i)
{
    (void)distance;
    int index;
    float ceil;
    float projection;
    float dst_to_proj;

    printf("distance = %f\n", distance);
    dst_to_proj = ((XPIXEL / 2.0) / tan (conversion_radian(32)));
    printf("dst_to_proj = %f\n", dst_to_proj);
    projection = (1 / distance) * dst_to_proj;
    ceil = (YPIXEL  - projection) / 2;
    printf("ceil = %f\n", ceil);
    index = 0;
   while (index < YPIXEL && index < ceil)
        pixel_draw(general, i, index++, 0x5DADE2);
    while (index < YPIXEL && index < (ceil + projection))
        pixel_draw(general, i, index++, 0x45B39D);
    while (index < YPIXEL)
        pixel_draw(general, i, index++, 0xF7DC6F);
    return ;
}
