#include "../include/cub3D.h"

t_dir	first_horizon_wall(float pos_x, float pos_y, double angle)
{
	t_dir	horiz;
	float	a;
	float	b;

	if (angle < 180)
		horiz.y = floor(pos_y) - pos_y;
	else
		horiz.y = ceil(pos_y) - pos_y;
	horiz.x = (horiz.y) / tan(conversion_radian(angle));
	a = pos_x - (pos_x - horiz.x);
	b = pos_y - (pos_y + horiz.y);
	horiz.hypo = sqrt(a * a + b * b);
	return (horiz);
}

t_dir	first_vertical_wall(float pos_x, float pos_y, double angle)
{
	t_dir	verti;
	float	a;
	float	b;

	if (angle > 90 && angle < 270)
		verti.x = floor(pos_x) - pos_x;
	else
		verti.x = ceil(pos_x) - pos_x;
	verti.y = (verti.x) * tan(conversion_radian(angle));
	a = pos_x - (pos_x + verti.x);
	b = pos_y - (pos_y - verti.y);
	verti.hypo = sqrt(a * a + b * b);
	return (verti);
}

t_dir	next_horizon_wall(float pos_x, float pos_y, double angle)
{
	t_dir	horiz;
	float	a;
	float	b;

	if (angle < 180)
		horiz.y = -1;
	else
		horiz.y = 1;
	horiz.x = 1 / tan(conversion_radian(angle));
	a = pos_x - (pos_x - horiz.x);
	b = pos_y - (pos_y + horiz.y);
	horiz.hypo = sqrt(a * a + b * b);
	return (horiz);
}

t_dir	next_vertical_wall(float pos_x, float pos_y, double angle)
{
	t_dir	verti;
	float	a;
	float	b;

	if (angle > 90 && angle < 270)
		verti.x = -1;
	else
		verti.x = 1;
	verti.y = tan(conversion_radian(angle));
	a = pos_x - (pos_x + verti.x);
	b = pos_y - (pos_y - verti.y);
	verti.hypo = sqrt(a * a + b * b);
	return (verti);
}