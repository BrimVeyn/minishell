/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 07:42:28 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/11/18 11:38:47 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned const char	*tmp;
	unsigned char		*d;

	tmp = src;
	d = dest;
	if (!dest && !src)
		return (dest);
	if (dest < src)
	{
		while (n--)
			*d++ = *tmp++;
	}
	else
	{
		d += n;
		tmp += n;
		while (n--)
			*(--d) = *(--tmp);
	}
	return (dest);
}
//
// #include <string.h>
//
// int	main(void)
// {
// 	char	*src;
// 	char	dst1[0xF0];
// 	char	dst2[0xF0];
// 	int		size;
//
// 	src = "this is a good nyancat !\r\n";
// 	size = strlen(src);
// 	__builtin_printf("%s", (char *)memmove(dst1, src, size));
// 	__builtin_printf("%s", (char *)ft_memmove(dst1, src, size));
// }
