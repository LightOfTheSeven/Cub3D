
#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
#include <math.h>


#include "../libft/libft.h"
#include "../libmlx/mlx.h"

#define DEBUG 0
#define NB_SPRITE 3
#define FOV 90
#define V_X 0
#define V_Y 1
#define ANGLE_MIN 0
#define ANGLE_MAX 1

#define WIDTH_TILE 64
#define HEIGHT_TILE 64
#define WIDTH_MINIMAP 14
#define HEIGHT_MINIMAP 8

# define L_ARW					65361
# define R_ARW					65363
# define UP_ARW					65362
# define DOWN_ARW				65364
# define A_KEY					97
# define W_KEY					119
# define S_KEY					115
# define D_KEY					100
# define ESC					65307

// permet de connaitre l'emplacement de chaque element
enum sprite {WALL, PLAYER, FLOOR}; // Ajouter N S W E

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
}				t_spt;

typedef struct s_map {
	char	**matrice;
	char	**minimap;
	float	pos_x;
	float	pos_y;
	int		ray_length;
	float	angle_cam; // entre 0 et 360, 45 degres de chaque cote
}				t_map;

typedef struct s_general {
	t_mlx	mlx;
	t_map	*map;
	t_spt	spts[3]; // spt = sprite
	
}				t_general;

typedef struct s_dir {
	float x;
	float y;
	float hypo;
}				t_dir;

int		init_struct(t_general *general, char **argv);
int		init_map(t_general *general, char *file_name);
int		free_img(char *err, t_general *general);
int		print_map(t_general *general);
int 	exit_mlx(t_general *general);
int 	free_general(t_general *general);
void 	hook(t_general *general);
int		hook_manager(int keycode, t_general *general);
int 	is_direction(char c);
void	init_raycasting(t_general *general);
int 	is_wall(double pos_x, double pos_y, double angle, t_general *general);

// BONUS
// int		init_minimap(t_map *map);
// void	change_minimap(t_map *map);


// UTILS
void 	print_matrice(t_map *map);

#endif
