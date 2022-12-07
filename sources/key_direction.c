
#include "../include/cub3D.h"

void	up(t_general *general)
{
	general->map->pos_x += calcul_x(general->map->angle_cam, general);
	general->map->pos_y += calcul_y(general->map->angle_cam, general);
}

void	down(t_general *general)
{
	general->map->pos_x -= calcul_x(general->map->angle_cam, general);
	general->map->pos_y -= calcul_y(general->map->angle_cam, general);
}

void	left(t_general *general)
{
	general->map->pos_y += calcul_y(general->map->angle_cam + 90, general);
	general->map->pos_x += calcul_x(general->map->angle_cam + 90, general);
}

void	right(t_general *general)
{
	general->map->pos_x += calcul_x(general->map->angle_cam - 90, general);
	general->map->pos_y += calcul_y(general->map->angle_cam - 90, general);
}
