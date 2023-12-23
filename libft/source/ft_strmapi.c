/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:44:13 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/11/18 11:38:47 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*recep;
	size_t	i;

	recep = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (recep == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		recep[i] = f(i, s[i]);
		i++;
	}
	recep[i] = 0;
	return (recep);
}
//
// static char	inc_str(unsigned int i, char c)
// {
// 	c += i;
// 	return (c);
// }
//
// int	main(void)
// {
// 	char	s[] = "Ilfaitsuperbeau";
// 	__builtin_printf("%s", ft_strmapi(s, inc_str));
// }
