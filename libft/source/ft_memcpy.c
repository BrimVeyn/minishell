/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 07:15:07 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/11/18 11:38:47 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;
	size_t		i;

	d = dest;
	s = src;
	if (dest == NULL && src == NULL)
		return (dest);
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}
//
// int	main(void)
// {
// 	int	source[] = {1, 3, 4};
// 	int	dest[5];
//
// 	ft_memcpy(dest, source, sizeof(source));
// 	__builtin_printf("|%zu|", sizeof(source));
// 	for (int i = 0; i < 5; i++) {
//         __builtin_printf("%d \n", dest[i]);
//     }
//
// 	char	s2[] = "proutf";
// 	char	d2[6];
//
// 	ft_memcpy(d2, s2, sizeof(s2));
//     __builtin_printf("%s \n", d2);
// 	__builtin_printf("|%zu|", sizeof(s2));
// }
