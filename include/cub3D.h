
#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>


#include "../libft/libft.h"
#include "../libmlx/mlx.h"

#define DEBUG 0
#define NB_SPRITE 3

enum sprite {WALL, PLAYER, FLOOR}; // Ajouter N S W E

typedef struct s_mlx {
	void			*ptr;
	void			*win;
	int				win_height;
	int				win_width;
	struct s_img 	*img;
}				t_mlx;

typedef struct s_spt {
	char	*path;
	void	*ptr;
}				t_spt;

typedef struct s_map {
	char	**matrice;
	float	pos_x;
	float	pos_y;
	float	angle_cam; // entre 0 et 360, 45 degres de chaque cote
	
}				t_map;

typedef struct s_general {
	t_mlx	*mlx;
	t_map	*map;
	t_spt	spts[4]; // spt = sprite
}				t_general;

int	init_struct(t_general *general, char **argv);
int	init_map(t_general *general, char *file_name);
int	free_img(char *err, t_general *general);


#endif
