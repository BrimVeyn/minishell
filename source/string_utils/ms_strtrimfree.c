/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_strtrimfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:34:52 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/26 09:27:20 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_istr(char const *str, char const c)
{
	while (*str)
	{
		if (c == *str)
			return (1);
		str++;
	}
	return (0);
}

char	*ms_strtrimf(char const *s1, char const *set)
{
	char		*end;
	char		*new;
	const char	*ptr = s1;

	while (*s1 && ft_istr(set, *s1))
		s1++;
	if (!*s1)
		return (ft_strdup(""));
	end = (char *)(s1 + ft_strlen(s1) - 1);
	while (end > s1 && ft_istr(set, *end))
		end--;
	new = ft_substr(s1, 0, end - s1 + 1);
	free((char *)ptr);
	return (new);
}
