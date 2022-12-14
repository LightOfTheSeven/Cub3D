/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 15:04:26 by gbertin           #+#    #+#             */
/*   Updated: 2022/12/10 15:08:49 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <math.h>
# include <X11/X.h>

# include "../libft/libft.h"
# include "../libmlx/mlx.h"

# define DEBUG 0
# define NB_SPRITE 4
# define FOV 60
# define V_X 0
# define V_Y 1
# define ANGLE_MIN 0
# define ANGLE_MAX 1

# define WIDTH_TILE 128
# define HEIGHT_TILE 128
# define WIDTH_MINIMAP 15
# define HEIGHT_MINIMAP 15
# define XPIXEL 1050.0
# define YPIXEL 750.0

# define L_ARW					65361
# define R_ARW					65363
# define UP_ARW					65362
# define DOWN_ARW				65364
# define A_KEY					97
# define W_KEY					119
# define S_KEY					115
# define D_KEY					100
# define ESC					65307

enum e_sprite {nord, south, west, east};

typedef struct s_mlx {
	void			*ptr;
	void			*win;
	int				win_height;
	int				win_width;
	struct s_img	*img;
	int				len;
	int				bpp;
	int				endian;
	char			*addr;
}				t_mlx;

typedef struct s_dir {
	double	x;
	double	y;
	double	hypo;
}				t_dir;

typedef struct s_hitpoint {
	double	x;
	double	y;
	double	dist;
	int		dir;
	double	angle;
	int		num_ray;
	int		remember;
	t_dir	horiz;
	t_dir	verti;
}				t_hitpoint;

typedef struct s_hook {
	int		up;
	int		down;
	int		left;
	int		right;
	int		rotate_left;
	int		rotate_right;
}				t_hook;

typedef struct s_spt {
	char			*path;
	void			*ptr;
	struct s_img	*img;
	int				len;
	int				bpp;
	int				endian;
	char			*addr;
	int				*data;
	int				width;
	int				height;
}				t_spt;

typedef struct s_map {
	char	**matrice;
	double	pos_x;
	double	pos_y;
	int		ray_length;
	double	angle_cam;
}				t_map;

typedef struct s_general {
	char	*filename;
	t_mlx	mlx;
	t_map	*map;
	t_hook	hook;
	t_spt	spts[NB_SPRITE];
	int		ceil_color[3];
	int		floor_color[3];
	int		map_column;
	int		map_line;
	double	temp_x;
	double	temp_y;
}				t_general;

int		init_struct(t_general *general, char **argv);
int		init_map(t_general *general);
int		free_img(char *err, t_general *general);
int		print_map(t_general *general);
int		exit_mlx(t_general *general);
int		free_general(t_general *general);
void	hook(t_general *general);
int		hook_manager(int keycode, t_general *general);
int		is_direction(char c);
int		malloc_matrice(t_general *general, int fd, int begin, char *line);
void	init_raycasting(t_general *general);
int		is_wall(double pos_x, double pos_y, double angle, t_general *general);
int		fill_infos(t_general *general, char **line);
int		detect_map(t_general *general, int nb_line);
int		verif_map(t_general *general);
void	print_matrice(t_map *map);
t_dir	first_horizon_wall(double pos_x, double pos_y, double angle);
t_dir	first_vertical_wall(double pos_x, double pos_y, double angle);
t_dir	next_horizon_wall(double pos_x, double pos_y, double angle);
t_dir	next_vertical_wall(double pos_x, double pos_y, double angle);
double	conversion_radian(double f);
double	get_ray_min(double angle);
double	get_ray_max(double angle);
double	horiz_bigger(int *remember, double *pos_x, double *pos_y, t_dir horiz);
double	verti_bigger(int *remember, double *pos_x, double *pos_y, t_dir verti);
void	init_image(t_general *general);
void	print_a_column(t_general *general, t_hitpoint hitpoint, int i);
int		init_pos_player(t_general *general);
double	init_cam(char direction);
void	up(t_general *general);
void	down(t_general *general);
void	left(t_general *general);
void	right(t_general *general);
double	calcul_x(double angle, t_general *general, int neg);
double	calcul_y(double angle, t_general *general, int neg);
double	fisheye(double distance, double angle, double angle_cam);

// UTILS
void	print_matrice(t_map *map);
int		count_tab(char **tab);
void	free_tab(char **tab);
int		is_space(char *line);
int		only_int(char *line);
char	*ft_strndup(const char *s, int n);
int		end_gnl(int fd);
double	conversion_radian(double f);

#endif
