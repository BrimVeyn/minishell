/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:34:52 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/11/18 11:38:47 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	ft_instr(char const *str, char const c)
{
	while (*str)
	{
		if (c == *str)
			return (1);
		str++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*end;

	while (*s1 && ft_instr(set, *s1))
		s1++;
	if (!*s1)
		return (ft_strdup(""));
	end = (char *)(s1 + ft_strlen(s1) - 1);
	while (end > s1 && ft_instr(set, *end))
		end--;
	return (ft_substr(s1, 0, end - s1 + 1));
}
//
// #include <string.h>
// #include <stdio.h>
//
// int	main(void)
// {
//     char *s2 = "          ";
//     char *trimmed = ft_strtrim(s2, " ");
//
//     if (trimmed[0] == '\0') {
//         printf("Result is an empty string or NULL\n");
//     } else {
//         printf("Trimmed string: %s\n", trimmed);
//     }
// }
