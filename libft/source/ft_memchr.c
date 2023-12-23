/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 07:48:47 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/11/18 11:38:47 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	ch;
	unsigned char	*src;

	i = 0;
	src = (unsigned char *)s;
	ch = (unsigned char)c;
	while (i < n)
	{
		if (src[i] == ch)
			return (&src[i]);
		i++;
	}
	return (0);
}
//
// int main(void)
// {
// 	char	src[] = "ilfaitbeau";
// 	char	c = 't';
//
// 	__builtin_printf("%s", (char *) ft_memchr(src, c, sizeof(src)));
// }
