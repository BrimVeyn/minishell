/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 15:29:05 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/11/18 11:38:51 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
#include <stdio.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	char	*bg;

	i = 0;
	bg = (char *)big;
	if (!big && len == 0)
		return (NULL);
	if (little[0] == 0)
		return (bg);
	while (bg[i] && i < len)
	{
		j = 0;
		while (bg[i] == little[j] && i < len)
		{
			i++;
			j++;
			if (little[j] == 0)
				return (&bg[i - j]);
		}
		i += 1 - j;
	}
	return (0);
}
//
// #include <string.h>
//
// int main(void)
// {
// 	char haystack[30] = "aaabcabcd";
// 	char needle[10] = "aabc";
// 	size_t max = -1;
// 	char *i1 = strnstr(haystack, needle, max);
// 	char *i2 = ft_strnstr(haystack, needle, max);
//
// 	__builtin_printf("V : %s \nC : %s", i1, i2);
// }
