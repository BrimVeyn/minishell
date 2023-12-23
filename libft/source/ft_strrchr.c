/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 15:29:11 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/11/18 11:38:47 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*tmp;
	char	*str;
	int		i;

	i = 0;
	tmp = 0;
	str = (char *)s;
	if (c == 0)
		return (str + ft_strlen(str));
	while (s[i])
	{
		if (s[i] == (char)c)
			tmp = &str[i];
		i++;
	}
	return (tmp);
}
//
// int main(void)
// {
//   char s[] = "Pedaloleximatisation";
//   char c = 'W';
//
//   __builtin_printf("%s",ft_strrchr(s, c));
// }
