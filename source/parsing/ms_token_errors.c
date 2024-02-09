/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_token_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 09:01:01 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/02/09 11:38:06 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ms_first_token_check(t_tok *tdata)
{
	if (ms_typetok(tdata->type[0][0]) == TRUE && tdata->type[0][0] != P_O)
	{
		fd_printf(2, "minishell: syntax error near unexpected token `%fs'\n",
			tdata->tokens[0][0]);
		return (ERROR);
	}
	return (TRUE);
}

static int	ms_after_cparenthesis_check(t_tok *tdata, int *i)
{
	if (tdata->type[*i][0] == P_C && tdata->type[*i + 1] && tdata->type[*i
		+ 1][0] == CMD)
	{
		fd_printf(2, "minishell: syntax error near unexpected token `%fs'\n",
			tdata->tokens[*i + 1][0]);
		return (ERROR);
	}
	return (TRUE);
}

static int	ms_after_cmd_check(t_tok *tdata, int *i)
{
	if (tdata->type[*i][0] == CMD && tdata->type[*i + 1] && tdata->type[*i
		+ 1][0] == P_O)
	{
		fd_printf(2, "minishell: syntax error near unexpected token `%fs'\n",
			tdata->tokens[*i + 1][0]);
		return (ERROR);
	}
	return (TRUE);
}

static int	ms_general_case_check(t_tok *tdata, int *i)
{
	if (tdata->tokens[*i + 1] && ms_typetok(tdata->type[*i + 1][0]) == TRUE
		&& tdata->type[*i][0] != P_C && tdata->type[*i + 1][0] != P_O)
	{
		printf("dkeodk");
		fd_printf(2, "minishell: syntax error near unexpected token `%fs'\n",
			tdata->tokens[*i + 1][0]);
		return (ERROR);
	}
	else if (!tdata->tokens[*i + 1] && tdata->type[*i][0] != P_C)
	{
		fd_printf(2, "minishell: syntax error near unexpected token `%fs'\n",
			tdata->tokens[*i][0]);
		return (ERROR);
	}
	return (TRUE);
}

int	ms_token_error(t_tok *tdata)
{
	int	i;

	i = 0;
	if (ms_first_token_check(tdata) == ERROR)
		return (ERROR);
	while (tdata->tokens[i])
	{
		if (ms_after_cparenthesis_check(tdata, &i) == ERROR)
			return (ERROR);
		if (ms_after_cmd_check(tdata, &i) == ERROR)
			return (ERROR);
		if (ms_typetok(tdata->type[i][0]) == TRUE)
			if (ms_general_case_check(tdata, &i) == ERROR)
				return (ERROR);
		i++;
	}
	return (TRUE);
}
