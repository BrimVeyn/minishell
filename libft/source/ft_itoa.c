/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:17:31 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/11/18 11:38:47 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	calculate_size(int n)
{
	size_t	size;

	if (n <= 0)
		size = 1;
	else
		size = 0;
	while (n != 0)
	{
		size++;
		n /= 10;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char			*str;
	size_t			size;
	unsigned int	unb;

	size = calculate_size(n);
	str = malloc((size + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[size] = '\0';
	unb = (unsigned int)n;
	if (n < 0)
	{
		str[0] = '-';
		unb = -((unsigned int)n);
	}
	else if (n == 0)
		str[0] = '0';
	while (unb != 0)
	{
		str[--size] = (unb % 10) + '0';
		unb = unb / 10;
	}
	return (str);
}
//
// #include <limits.h>
// #include <string.h>
//
// int	main(void)
// {
//
// 	// __builtin_printf("STR : %s\n", ft_itoa(-5857));
// 	__builtin_printf("STR : %s\n", ft_itoa(-623));
// 	__builtin_printf("STR : %s\n", ft_itoa(156));
// 	__builtin_printf("STR : %s\n", ft_itoa(-0));
// 	// __builtin_printf("STR : %s\n", ft_itoa(0));
// 	__builtin_printf("STRCMP R = %d\n", strcmp(ft_itoa(-0), "0"));
// 	__builtin_printf("STRCMP R = %d\n", strcmp(ft_itoa(-623), "-623"));
// 	__builtin_printf("STRCMP R = %d\n", strcmp(ft_itoa(156), "156"));
// }
