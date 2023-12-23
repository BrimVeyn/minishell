/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:43:58 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/11/18 11:38:47 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*cat;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	cat = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (cat == NULL)
		return (NULL);
	while (s1[i])
	{
		cat[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		cat[i + j] = s2[j];
		j++;
	}
	cat[i + j] = 0;
	return (cat);
}
//
// int	main(void)
// {
// 	char	s1[] = "il";
// 	char	s2[] = "fait";
// 	__builtin_printf("%s", ft_strjoin(s1, s2));
// }
//
