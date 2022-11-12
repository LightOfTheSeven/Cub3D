/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 11:04:02 by gbertin           #+#    #+#             */
/*   Updated: 2022/11/12 17:17:05 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	init_struct_mlx(t_mlx *mlx)
{
	mlx->ptr = mlx_init();
	if (!mlx->ptr)
		return (1);
	mlx->win_height = 1080;
	mlx->win_width = 1920;
	mlx->win = mlx_new_window(mlx->ptr, mlx->win_width, mlx->win_height, "Cub3D");
	mlx->img = mlx_new_image(mlx->ptr, mlx->win_width, mlx->win_height);
	return (0);
}

int	init_struct(t_general *general)
{
	t_mlx	  mlx;

	ft_memset(&mlx, 0, sizeof(t_mlx));
	general->mlx = &mlx;
	init_struct_mlx(general->mlx);
	return (0);
}

int	fill_map(t_general *general, char *file_name)
{
	int		fd;
	char	*line;
	int		nb_line;
	t_map	  *map;
	int i;

	i = 0;
	map = (t_map *) malloc (sizeof(t_map));
	ft_memset(map, 0, sizeof(t_map));
	nb_line = 0;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		nb_line++;
	}
	free(line);
	map->matrice = (char **) malloc(sizeof(char *) * (nb_line + 1));
	if (!map->matrice)
		return (1);
	close(fd);
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (1);
	while (i < nb_line )
	{
		map->matrice[i] = get_next_line(fd);
		if (!map->matrice[i])
			return (1);
		i++;
	}
	map->matrice[nb_line] = NULL;
	i = 0;
	general->map = map;
	return (0);
}

void 	print_map(t_map *map)
{
	int i;

	i = 0;
	while (map->matrice[i])
	{
		printf("%s", map->matrice[i]);
		i++;
	}
}

int main(int argc, char **argv)
{
	t_general general;
	
	if (argc == 2)
	{
		ft_memset(&general, 0, sizeof(t_general));
		if (init_struct(&general))
			return (1);
		fill_map(&general, argv[1]);
		print_map(general.map);
	}
	return (0);
}
