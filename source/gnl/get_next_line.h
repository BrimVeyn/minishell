/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 10:34:59 by nbardavi          #+#    #+#             */
/*   Updated: 2023/12/01 15:17:50 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char	*newline(char *stash);
char	*ft_strchr(const char *string, int searchedChar);
size_t	ft_strlen(const char *theString);
char	*ft_strdup(const char *source);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*get_next_line(int fd);
char	*fill_line(int fd, char *stash, char *buffer);

#endif
