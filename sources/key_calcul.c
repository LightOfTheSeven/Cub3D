
#include "../include/cub3D.h"

double	calcul_x(double angle, t_general *general, int neg)
{
	double	x;
	double	new_x;

	if (angle > 360)
		angle -= 360;
	if (angle < 0)
		angle += 360;
	x = cos(conversion_radian(angle)) * 0.06;
	if (neg)
		new_x = general->map->pos_x - x;
	else
		new_x = general->map->pos_x + x;
	if (general->map->matrice[(int)floor(general->map->pos_y)][(int)floor(new_x)] == '1')
		return (0);
	if (new_x <= 1 || new_x >= general->map_column - 1)
		return (0);
	return (x);
}

double	calcul_y(double angle, t_general *general, int neg)
{
	double	y;
	double	new_y;

	if (angle > 360)
		angle -= 360;
	if (angle < 0)
		angle += 360;
	y = sin(conversion_radian(angle * -1)) * 0.06;
	if (neg)
		new_y = general->map->pos_y - y;
	else
		new_y = general->map->pos_y + y;
	if (general->map->matrice[(int)floor(new_y)][(int)floor(general->map->pos_x)] == '1')
		return (0);
	if (new_y <= 1 || new_y >= general->map_line - 1)
		return (0);
	return (y);
}
