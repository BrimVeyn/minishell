/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:20:18 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/11/18 11:38:47 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
#include <string.h>

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	unsigned int	taille_src;
	unsigned int	taille_dest;

	taille_src = 0;
	taille_dest = 0;
	if (!size && !dest)
		return (0);
	while (dest[taille_dest] && taille_dest < size)
		taille_dest++;
	while (src[taille_src] && size && taille_dest + taille_src < size - 1)
	{
		dest[taille_dest + taille_src] = src[taille_src];
		taille_src++;
	}
	if (taille_dest < size)
		dest[taille_dest + taille_src] = '\0';
	while (src[taille_src])
		taille_src++;
	return (taille_dest + taille_src);
}

// #include <stdio.h>
// #include <string.h>
//
// int	main(void)
// {
//
// 	char *dest;
// 	dest = (char *)malloc(sizeof(*dest) * 15);
// 	memset(dest, 0, 15);
// 	memset(dest, 'r', 6);
// 	dest[10] = 'a';
// 	printf("%zu", ft_strlcat(dest, "lorem ipsum dolor sit amet", 0));
// 	char *dest2;
// 	dest2 = (char *)malloc(sizeof(*dest) * 15);
// 	memset(dest2, 0, 15);
// 	memset(dest2, 'r', 6);
// 	dest2[10] = 'a';
// 	printf("%ld", strlcat(dest2, "lorem ipsum dolor sit amet", 0));
// }
