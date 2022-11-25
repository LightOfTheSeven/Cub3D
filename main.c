#include <stdio.h>
#include "include/cub3D.h"

int main ()
{
	char **tab;

	tab = ft_split("Bonjour la ville", ' ');
	printf("%s %s %s\n", tab[0],  tab[1],  tab[2]);
	return (0);
}