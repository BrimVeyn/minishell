/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:42:50 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/03/05 09:13:22 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_tokvar	ms_tiktok(char *ptr)
{
	if (!ft_strncmp(ptr, "||", 2))
		return (init_tokvar("||", OR));
	if (!ft_strncmp(ptr, "&&", 2))
		return (init_tokvar("&&", AND));
	if (!ft_strncmp(ptr, ">>", 2))
		return (init_tokvar(">>", D_AR));
	if (!ft_strncmp(ptr, "<<", 2))
		return (init_tokvar("<<", D_AL));
	if (!ft_strncmp(ptr, "<", 1))
		return (init_tokvar("<", S_AL));
	if (!ft_strncmp(ptr, ">", 1))
		return (init_tokvar(">", S_AR));
	if (!ft_strncmp(ptr, "(", 1))
		return (init_tokvar("(", P_O));
	if (!ft_strncmp(ptr, ")", 1))
		return (init_tokvar(")", P_C));
	if (!ft_strncmp(ptr, "|", 1))
		return (init_tokvar("|", PIPE));
	return (init_tokvar("", CMD));
}

static int	parse_error_checker(t_tok *tdata)
{
	if (ms_token_error(tdata) == ERROR || ms_newline_error(tdata) == ERROR)
	{
		tdata->exitno = 2 << 8;
		tdata->t_size = ERROR;
		return (ERROR);
	}
	return (TRUE);
}

static int	empty_string(t_tok *tdata)
{
	if (tdata->t_size == ZERO)
	{
		tdata->t_size = ERROR;
		tdata->tokens = NULL;
		tdata->type = NULL;
		return (ERROR);
	}
	return (TRUE);
}

static char	*fill_heredoc(char *input, t_tok *tdata)
{
	if (ft_strchr(input, '\n'))
	{
		tdata->heredoc = ft_split(ft_strchr(input, '\n'), '\n');
		input = ms_cut_at(input, '\n');
	}
	return (input);
}

void	parse_input(char *input, t_tok *tdata)
{
	tdata->heredoc = NULL;
	tdata->tok_copy = NULL;
	input = fill_heredoc(input, tdata);
	if (quotes_parity_check(input, tdata) == ERROR)
	{
		tdata->t_size = ERROR;
		tdata->tokens = NULL;
		tdata->type = NULL;
		if (tdata->heredoc)
			free(input);
		return ;
	}
	tdata->t_size = count_tokens(input);
	if (empty_string(tdata) == ERROR)
	{
		if (tdata->heredoc)
			free(input);
		return ;
	}
	tdata->tokens = ms_split(tdata, input);
	tdata->tok_copy = ms_copy_tok(tdata->tokens, tdata->t_size);
	ms_par_check(input, tdata);
	if (parse_error_checker(tdata) == ERROR)
		return ;
}
