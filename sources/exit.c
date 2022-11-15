#include "../include/cub3D.h"

int exit_mlx(t_general *general)
{
    //mlx_clear_window(general->mlx.ptr, general->mlx.win);
    //mlx_destroy_window(general->mlx.ptr, general->mlx.win);
    free_general(general);
    free_img("EXIT\n", general);
    exit(EXIT_SUCCESS);
    return 0;
}