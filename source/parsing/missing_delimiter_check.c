/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   missing_delimiter_check.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:25:59 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/26 10:35:50 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int exitno;

char	**ms_joinstarstr(char **p1, char *p2)
{
	char	**new;
	int		i;

	i = -1;
	new = ft_calloc(ms_tablen(p1) + 2, sizeof(char *));
	if (!new)
		return (NULL);
	while (p1[++i])
		new[i] = ft_strdup(p1[i]);
	new[i] = ft_strdup(p2);
	return (new);
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
			if ((!ft_strncmp(tokens[i][j], "\0", 1) && j == 0) || (j != 0
					&& !ft_strncmp(tokens[i][j], "\0", 1)
					&& !ft_strncmp(tokens[i][j - 1], "<<", 2)))
				return (ERROR);
			j++;
		}
		i++;
	}
	return (TRUE);
}

char	**get_delimiters(char ***tokens, int *type)
{
	char	**delimiters;
	int		i;
	int		j;

	i = 0;
	delimiters = ft_calloc(2, sizeof(char *));
	while (tokens[i])
	{
		j = 0;
		while (tokens[i][j] && (type[i] == CMD || type[i] == D_AL))
		{
			if (type[i] == D_AL && !ft_strncmp(tokens[i + 1][0], "\0", 1))
				(void)type;
			if (ft_strlen(tokens[i][j]) >= 2 && !ft_strncmp(tokens[i][j], "<<",
					2) && ft_strncmp(tokens[i][j + 1], "\0", 1))
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
	char	**delimiters;
	int		i;

	if (ms_is_empty(tdata->tokens) == TRUE)
		return (TRUE);
	delimiters = get_delimiters(tdata->tokens, tdata->type);
	i = 0;
	while (delimiters[i])
	{
		t_heredoc(tdata, 0, delimiters[i]);
		i++;
	}
	fd_printf(2, "minishell: syntax error near unexpected token `newline'\n");
	exitno = 2;
	tdata->type[0] = WRONG;
	return (ERROR);
}
