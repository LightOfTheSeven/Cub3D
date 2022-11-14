/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 08:59:08 by gbertin           #+#    #+#             */
/*   Updated: 2021/11/29 08:59:29 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	unsigned int	i;
	unsigned int	y;

	i = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		y = 0;
		while (haystack[y + i] == needle[y] && i + y < len
			&& haystack[y + i] && needle[y])
		{
			y++;
			if (!needle[y])
				return ((char *)(haystack + i));
		}
		i++;
	}
	return (NULL);
}

// int main() {

//    char *s;

//    s = "Bonjour les admins :)";

//     // Recherche de la présence de la chaîne "admin" dans la saisie.
//     char *result = ft_strnstr(s, "admin",20);

//     // Affichage d'une réponse à l'utilisateur.
//     if ( result == NULL ) {
//         puts( "Vous n'avez pas saisi le mot admin" );
//     } else {
//         puts( "La chaîne contient le mot admin" );
//     }

//     return EXIT_SUCCESS;
// }
