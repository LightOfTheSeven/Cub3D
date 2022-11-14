#include "../include/cub3D.h"

int is_direction(char c)
{
    if (c == 'N' || c == 'O' || c == 'S' || c == 'E')
        return 1;
    return 0;
}