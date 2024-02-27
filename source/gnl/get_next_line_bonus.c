/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 09:30:58 by nbardavi          #+#    #+#             */
/*   Updated: 2023/11/20 14:47:48 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdlib.h>

char	*substash(char *stash);

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*stash[1024];
	char		*line;

	line = NULL;
	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(stash[fd]);
		free(buffer);
		return (0);
	}
	stash[fd] = fill_line(fd, stash[fd], buffer);
	free(buffer);
	if (!stash[fd])
		return (NULL);
	line = newline(stash[fd]);
	stash[fd] = substash(stash[fd]);
	return (line);
}

char	*substash(char *stash)
{
	int		i;
	char	*newstash;

	i = 0;
	while (stash[i] != '\0' && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	newstash = ft_substr(stash, i + 1, ft_strlen(stash) - i);
	free(stash);
	return (newstash);
}

char	*newline(char *stash)
{
	int		i;
	char	*returnstash;

	i = 0;
	if (stash[i] == '\0')
		return (NULL);
	while (stash[i] != '\0' && stash[i] != '\n')
		i++;
	returnstash = ft_substr(stash, 0, i + 1);
	if (*returnstash == '\0')
	{
		free(returnstash);
		return (NULL);
	}
	return (returnstash);
}

char	*fill_line(int fd, char *stash, char *buffer)
{
	int		byte_read;
	char	*tmp;

	byte_read = 1;
	while (byte_read > 0)
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read == -1)
		{
			free(stash);
			return (NULL);
		}
		else if (byte_read == 0)
			break ;
		buffer[byte_read] = 0;
		if (!stash)
			stash = ft_strdup("");
		tmp = stash;
		stash = ft_strjoin(tmp, buffer);
		free(tmp);
		tmp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (stash);
}
