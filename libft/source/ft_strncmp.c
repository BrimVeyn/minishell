/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 15:28:57 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/11/18 11:38:47 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*ss1;
	unsigned char	*ss2;

	i = 0;
	ss1 = (unsigned char *)s1;
	ss2 = (unsigned char *)s2;
	while ((ss1[i] || ss2[i]) && i < n)
	{
		if (ss1[i] > ss2[i])
			return (1);
		if (ss1[i] < ss2[i])
			return (-1);
		i++;
	}
	return (0);
}
//
// int main(void)
// {
//   char s1[] = "pedon";
//   char s2[] = "pedfn";
//
//   __builtin_printf("%d", ft_strncmp(s1, s2, 3));
//   __builtin_printf("%d", ft_strncmp(s1, s2, 4));
// }
