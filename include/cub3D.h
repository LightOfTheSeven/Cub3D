/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 15:04:26 by gbertin           #+#    #+#             */
/*   Updated: 2022/12/01 16:55:59 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <math.h>

# include "../libft/libft.h"
# include "../libmlx/mlx.h"

# define DEBUG 0
# define ROTATE 1
# define NB_SPRITE 5
# define FOV 90
# define V_X 0
# define V_Y 1
# define ANGLE_MIN 0
# define ANGLE_MAX 1

#define WIDTH_TILE 64
#define HEIGHT_TILE 64
#define WIDTH_MINIMAP 8
#define HEIGHT_MINIMAP 8
#define XPIXEL 700
#define YPIXEL 500

# define L_ARW					65361
# define R_ARW					65363
# define UP_ARW					65362
# define DOWN_ARW				65364
# define A_KEY					97
# define W_KEY					119
# define S_KEY					115
# define D_KEY					100
# define ESC					65307

# define NO 0
# define SO 1
# define WE 2
# define EA 3

// permet de connaitre l'emplacement de chaque element
enum e_sprite {player, nord, south, west,east}; // Ajouter N S W E

typedef struct s_mlx {
	void			*ptr;
	void			*win;
	int				win_height;
	int				win_width;
	struct s_img 	*img;
	int				len;
	int				bpp;
	int				endian;
	char			*addr;
}				t_mlx;

typedef struct s_spt {
	char	*path;
	void	*ptr;
	struct s_img 	*img;
	int				len;
	int				bpp;
	int				endian;
	char			*data;
}				t_spt;

typedef struct s_map {
	char	**matrice;
	float	pos_x;
	float	pos_y;
	int		ray_length;
	float	angle_cam; // entre 0 et 360, 45 degres de chaque cote
}				t_map;

typedef struct s_dir {
	float	x;
	float	y;
	float	hypo;
}				t_dir;

typedef struct s_hitpoint {
	float	x;
	float	y;
	float	distance;
}				t_hitpoint;

typedef struct s_general {
	char	*filename;
	t_mlx	mlx;
	t_map	*map;
	t_spt	spts[NB_SPRITE]; // spt = sprite
	int		ceil_color[3];
	int		floor_color[3];
	int		map_column;
	int		map_line;
	int		direction;
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
void	init_raycasting(t_general *general);
int 	is_wall(double pos_x, double pos_y, double angle, t_general *general);
void	pixel_draw(t_general *general, int x, int y, int color);
void	init_image(t_general *general);
void    print_a_column(t_general *general, float distance, int i);

// BONUS
// int		init_minimap(t_map *map);
// void	change_minimap(t_map *map);


// UTILS
int		fill_infos(t_general *general, char **line);
int		detect_map(t_general *general, int nb_line);
int		verif_map(t_general *general);
void	print_matrice(t_map *map);
t_dir	first_horizon_wall(float pos_x, float pos_y, double angle);
t_dir	first_vertical_wall(float pos_x, float pos_y, double angle);
t_dir	next_horizon_wall(float pos_x, float pos_y, double angle);
t_dir	next_vertical_wall(float pos_x, float pos_y, double angle);
double	get_ray_min(double angle);
double	get_ray_max(double angle);
float	horiz_bigger(int *remember, float *pos_x, float *pos_y, t_dir horiz);
float	verti_bigger(int *remember, float *pos_x, float *pos_y, t_dir verti);

// UTILS
void	print_matrice(t_map *map);
int		count_tab(char **tab);
void	free_tab(char **tab);
int		is_space(char *line);
int		only_int(char *line);
char	*ft_strndup(const char *s, int n);
void	end_gnl(int fd);
void 	change_direction(t_general *general, double angle);
float	conversion_radian(float f);

#endif
