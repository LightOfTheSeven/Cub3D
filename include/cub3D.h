
#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
#include <fcntl.h>


#include "../libft/libft.h"
#include "../libmlx/mlx.h"

#define DEBUG 0

typedef struct s_mlx {
	void			*ptr;
	void			*win;
	int				win_height;
	int				win_width;
	struct s_img 	*img;
}				t_mlx;

typedef struct s_img {
	char	*floor_path;
	char	*player_path;
	char	*wall_path;
	void	*floor_ptr;
	void	*player_ptr;
	void	*wall_ptr;
}				t_img;

typedef struct s_map {
	char	**matrice;
	float	pos_x;
	float	pos_y;
	float	angle_cam; // entre 0 et 360, 45 degres de chaque cote
}				t_map;

typedef struct s_general {
	t_mlx *mlx;
	t_map *map;
}				t_general;

#endif
