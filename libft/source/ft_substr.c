/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:47:36 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/11/18 11:38:47 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	i;
	size_t	slen;

	i = 0;
	slen = ft_strlen(s);
	if (!s)
		return (NULL);
	if (start >= slen || len == 0)
		return (ft_strdup(""));
	if (len > slen - start)
		len = slen - start;
	new = malloc((len + 1) * sizeof(char));
	if (new == NULL)
		return (NULL);
	while (i < len && s[start + i])
	{
		new[i] = s[start + i];
		i++;
	}
	new[i] = 0;
	return (new);
}
//
// #include <string.h>
//
// int	main(void)
// {
// 	char *ret = ft_substr("tripouille", 0, 42000);
// 	char *s;
// 	char *str = strdup("0123456789");
// 	s = ft_substr(str, 9, 10);
// 	__builtin_printf("%s", s);
// 	// if (!strncmp(ret, "", 1))
// 	// 	__builtin_printf("Yes");
// }
//
//
