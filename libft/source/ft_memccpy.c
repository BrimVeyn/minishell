/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 07:24:59 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/11/18 11:38:47 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t		i;
	char		*d;
	const char	*s;

	i = 0;
	d = dest;
	s = src;
	while (i < n)
	{
		d[i] = s[i];
		if (s[i] == c)
			return (&d[i + 1]);
		i++;
	}
	return (0);
}
//
// int main(void)
// {
// 	char src[] = "Superbe";
// 	char dst[100] = "C'est une supberbe apres-midi";
// 	char c = 'u';
// 	size_t n = 5;
// 	__builtin_printf("Before copy %s\n", dst);
// 	ft_memccpy(dst, src, c, n);
// 	__builtin_printf("A : %s\n", (char *) ft_memccpy(dst, src, c, n));
// 	__builtin_printf("After copy %s\n", dst);
// }
