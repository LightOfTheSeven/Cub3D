#include "../include/cub3D.h"

float conversion_radian(float f)
{
    f = f * (3.1415 / 180);
    return f;
}

void pixel_draw(t_mlx *temp, int x, int y, int color)
{
    char	*dst;

	dst = temp->addr + (y * temp->len + x * (temp->bpp / 8));
	*(unsigned int *)dst = color;
}

void print_rayon_face_joueur(t_general *general)
{
    float dir_x;
    float dir_y;

    if (general->map->angle_cam < 0)
        general->map->angle_cam = general->map->angle_cam + 360;
    if (general->map->angle_cam > 360)
        general->map->angle_cam = general->map->angle_cam - 360;
    //printf("angle = %f\n", general->map->angle_cam);
    dir_x = cos(conversion_radian(360 - general->map->angle_cam));
    dir_y = cos(conversion_radian(general->map->angle_cam - 270));
    //printf("dir_x = %f dir_y = %f\n", dir_x, dir_y);
    int i = 0;
    struct s_mlx temp;
    int color = 88888;

    float x = (general->map->pos_x) * HEIGHT_TILE;
    float y = (general->map->pos_y) * WIDTH_TILE;

    temp.img = mlx_new_image(general->mlx.ptr, general->mlx.win_width, general->mlx.win_height);
    temp.addr = mlx_get_data_addr(temp.img, &temp.bpp, &temp.len, &temp.endian);
    while (i < 70)
    {
        x = x + dir_x;
        y = y + dir_y;
        pixel_draw(&temp, x, y, color);
        i++;
    }
    general->mlx.img = temp.img;
    mlx_put_image_to_window(general->mlx.ptr, general->mlx.win, general->mlx.img, 0, 0); 
}