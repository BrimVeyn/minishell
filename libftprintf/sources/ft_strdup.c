/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbardavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:34:13 by nbardavi          #+#    #+#             */
/*   Updated: 2023/11/28 14:38:46 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

char	*ft_strdup(const char *source)
{
	char	*str2;
	int		i;

	i = -1;
	str2 = malloc(sizeof(char) * (ft_strlen(source) + 1));
	if (str2 == NULL)
		return (NULL);
	while (source[++i])
		str2[i] = source[i];
	str2[i] = '\0';
	return (str2);
}
