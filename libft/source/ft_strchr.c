/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 15:28:46 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/11/18 11:38:49 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*str;

	i = 0;
	str = (char *)s;
	if (c == 0)
		return (str + ft_strlen(str));
	while (s[i])
	{
		if (str[i] == (char)c)
			return (&str[i]);
		i++;
	}
	return (0);
}
//
// #include "string.h"
//
// int main(void)
// {
// 	char s[] = "tripouille";
//
// 	__builtin_printf("C : %s\n",ft_strchr(s, 0));
// 	__builtin_printf("R : %s\n",strchr(s, 0));
// }
