/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing_errors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 08:59:04 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/03/01 11:31:37 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ms_double_cmdtok_error(t_tok *tdata, int *i, int *j)
{
	if (ms_typecmdtok(tdata->type[*i][*j]) == TRUE && tdata->tokens[*i][*j + 1]
		&& ms_typecmdtok(tdata->type[*i][*j + 1]) == TRUE)
	{
		fd_printf(2, "minishell: syntax error near unexpected token `%fs'\n",
			tdata->tokens[*i][*j + 1]);
		return (ERROR);
	}
	return (TRUE);
}

static int	ms_end_of_line_error(t_tok *tdata, int *i, int *j)
{
	if (ms_typecmdtok(tdata->type[*i][*j]) == TRUE && !tdata->tokens[*i][*j
		+ 1])
	{
		fd_printf(2,
			"minishell: syntax error near unexpected token `newline'\n");
		return (ERROR);
	}
	return (TRUE);
}

int	ms_newline_error(t_tok *tdata)
{
	int	i;
	int	j;

	i = 0;
	while (tdata->tokens[i])
	{
		j = 0;
		while (tdata->tokens[i][j])
		{
			if (ms_double_cmdtok_error(tdata, &i, &j) == ERROR)
				return (ERROR);
			if (ms_end_of_line_error(tdata, &i, &j) == ERROR)
				return (ERROR);
			j++;
		}
		i++;
	}
	return (TRUE);
}

int	ms_ambiguous_error(t_tok *tdata)
{
	int	i;
	int	j;

	i = 0;
	while (tdata->tokens[i])
	{
		j = 0;
		while (tdata->tokens[i][j])
		{
			if (ms_typecmdtok(tdata->type[i][j]) == TRUE
				&& tdata->type[i][j] != D_AL)
			{
				if (ms_count_words(tdata->tokens[i][j + 1]) > 1
					&& (ft_strchr(tdata->tok_copy[i][j + 1], '*') || ft_strchr(tdata->tok_copy[i][j + 1], '$')))
				{
					fd_printf(2, "minishell: %fs: ambiguous redirect\n",
						tdata->tok_copy[i][j + 1]);
					return (ERROR);
				}
			}
			j++;
		}
		i++;
	}
	return (TRUE);
}
