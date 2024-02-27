/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 10:37:08 by nbardavi          #+#    #+#             */
/*   Updated: 2023/11/20 14:18:21 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

size_t	ft_strlen(const char *theString)
{
	size_t	i;

	i = 0;
	if (theString == NULL)
		return (0);
	while (theString[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*returnvalue;
	int		i;
	int		j;

	j = 0;
	i = 0;
	returnvalue = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (returnvalue == NULL)
	{
		return (NULL);
	}
	if (s1)
		while (s1[j])
			returnvalue[i++] = (char)s1[j++];
	j = 0;
	while (s2[j])
		returnvalue[i++] = (char)s2[j++];
	returnvalue[i] = '\0';
	return (returnvalue);
}

char	*ft_strchr(const char *string, int searchedChar)
{
	char	c;

	c = (char)searchedChar;
	if (c == '\0')
		return ((char *)string + ft_strlen(string));
	while (*string)
	{
		if (*string == c)
			return ((char *)string);
		string++;
	}
	return (NULL);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*returnvalue;

	i = 0;
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	returnvalue = malloc(sizeof(char) * len + 1);
	if (returnvalue == NULL)
		return (NULL);
	while (i < len)
		returnvalue[i++] = s[start++];
	returnvalue[i] = '\0';
	return (returnvalue);
}
