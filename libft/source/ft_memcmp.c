/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 07:53:07 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/11/18 11:38:50 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*src1;
	const unsigned char	*src2;

	i = 0;
	src1 = s1;
	src2 = s2;
	while (i < n)
	{
		if (src1[i] != src2[i])
			return (src1[i] - src2[i]);
		i++;
	}
	return (0);
}
//
// #include <string.h>
//
// int	main(void)
// {
// 	char s[] = {-128, 0, 127, 0};
// 	// char sCpy[] = {-128, 0, 127, 0};
// 	char s2[] = {0, 0, 127, 0};
// 	char s3[] = {0, 0, 42, 0};
//
// 	__builtin_printf("C : %d\n", ft_memcmp(s, s2, 1));
// 	__builtin_printf("R : %d\n", memcmp(s, s2, 1));
// 	__builtin_printf("C : %d\n", ft_memcmp(s2, s, 1));
// 	__builtin_printf("R : %d\n", memcmp(s2, s, 1));
// 	__builtin_printf("C : %d\n", ft_memcmp(s2, s3, 4));
// 	__builtin_printf("R : %d\n", memcmp(s2, s3, 4));
// }
//
