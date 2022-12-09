/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3D.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 08:36:08 by gbertin           #+#    #+#             */
/*   Updated: 2022/12/09 15:38:07 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int	convert_color(int color[3])
{
	int	ret_v;

	ret_v = 0;
	ret_v += (color[2] % 16) * pow(16, 0);
	ret_v += (color[2] / 16) * pow(16, 1);
	ret_v += (color[1] % 16) * pow(16, 2);
	ret_v += (color[1] / 16) * pow(16, 3);
	ret_v += (color[0] % 16) * pow(16, 4);
	ret_v += (color[0] / 16) * pow(16, 5);
	return (ret_v);
}

void	pixel_draw(t_general *g, int x, int y, int color)
{
	char	*dst;

	dst = g->mlx.addr + (y * g->mlx.len + x * (g->mlx.bpp / 8));
	*(unsigned int *)dst = color;
}

void	init_image(t_general *g)
{
	g->mlx.img = mlx_new_image(g->mlx.ptr, g->mlx.win_width, g->mlx.win_height);
	g->mlx.addr = mlx_get_data_addr(g->mlx.img, &g->mlx.bpp,
			&g->mlx.len, &g->mlx.endian);
}

void	draw_pixel_from_xpm(t_general *g, t_hitpoint hit, int lign, int proj)
{
	int		color;
	int		x;
	int		y;
	int		index;

	x = 0;
	y = 0;
	index = lign;
	lign = lign - ((YPIXEL - proj) / 2);
	y = (g->spts[hit.dir].height * (lign / (double)proj));
	if (hit.x - floor(hit.x) == 0)
		x = round(g->spts[hit.dir].height * (hit.y - floor(hit.y)));
	else
		x = round(g->spts[hit.dir].width * (hit.x - floor(hit.x)));
	color = g->spts[hit.dir].data[(y * g->spts[hit.dir].len + x)];
	pixel_draw(g, hit.num_ray, index, color);
}

void	print_a_column(t_general *general, t_hitpoint hitpoint, int num_ray)
{
	int		lign;
	double	ceil;
	double	projection;
	double	dst_to_proj;
	int		color[2];

	color[0] = convert_color(general->ceil_color);
	color[1] = convert_color(general->floor_color);
	dst_to_proj = ((XPIXEL / 2.0) / tan (conversion_radian(32)));
	projection = (1 / hitpoint.dist) * dst_to_proj;
	ceil = (YPIXEL - projection) / 2;
	lign = 0;
	hitpoint.num_ray = num_ray;
	while (lign < YPIXEL && lign < ceil)
		pixel_draw(general, num_ray, lign++, color[0]);
	while (lign < YPIXEL && lign < (ceil + projection))
		draw_pixel_from_xpm(general, hitpoint, lign++, projection);
	while (lign < YPIXEL)
		pixel_draw(general, num_ray, lign++, color[1]);
	return ;
}
