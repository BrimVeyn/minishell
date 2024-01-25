/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   missing_delimiter_check.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:25:59 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/25 13:28:19 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
char **ms_joinstarstr(char **p1, char *p2)
{
	char **new;
	int i;

	i = -1;
	new = ft_calloc(ms_tablen(p1) + 2, sizeof(char *));
	if (!new)
		return (NULL);
	while(p1[++i])
		new[i] = ft_strdup(p1[i]);
	new[i] = ft_strdup(p2);
	return(new);
}

int	ms_is_empty(char ***tokens)
{
	int	i;
	int	j;

	i = 0;
	while (tokens[i])
	{
		j = 0;
		while (tokens[i][j])
		{
			if (!ft_strncmp(tokens[i][j], "\0", 1))
				return (ERROR);
			j++;
		}
		i++;
	}
	return (TRUE);
}

char **get_delimiters(char ***tokens, int *type)
{
	char **delimiters;
	int i;
	int	j;

	i = 0;
	delimiters = ft_calloc(2, sizeof(char *));
	while (tokens[i])
	{
		j = 0;
		while (tokens[i][j] && (type[i] == CMD || type[i] == D_AL))
		{
			if (type[i] == D_AL && !ft_strncmp(tokens[i + 1][0], "\0", 1))
				(void) type;
			if (ft_strlen(tokens[i][j]) >= 2 && !ft_strncmp(tokens[i][j], "<<", 2) && ft_strncmp(tokens[i][j + 1], "\0", 1))
            {
				delimiters = ms_joinstarstr(delimiters, tokens[i][j + 1]);
            }
			j++;
		}
		i++;
	}
	return (delimiters);
}

int	missing_delimiter_check(t_tok *tdata)
{
	char **delimiters;
	int	i;

	if (ms_is_empty(tdata->tokens) == TRUE)
		return (TRUE);

	delimiters = get_delimiters(tdata->tokens, tdata->type);
	i = 0;
	while (delimiters[i])
	{
		t_heredoc(tdata, 0, delimiters[i]);
		i++;
	}
	return (ERROR);	
}
