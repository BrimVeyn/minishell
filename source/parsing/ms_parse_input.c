/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:20:38 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/02/15 10:32:28 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_exitno;

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

static int	parse_error_checker(char *input, t_tok *tdata, char ***tok_copy)
{
	if (ms_token_error(tdata) == ERROR || ms_newline_error(tdata) == ERROR
		|| parenthesis_check(input) == ERROR)
	{
		g_exitno = 2 << 8;
		tdata->t_size = ERROR;
		return (ERROR);
	}
	if (ms_ambiguous_error(tdata, tok_copy) == ERROR)
	{
		g_exitno = 1 << 8;
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

t_tok	parse_input(char *input, t_env *denv)
{
	t_tok	tdata;
	char	***tok_copy;

	tdata.heredoc = NULL;
	tok_copy = NULL;
	if (ft_strchr(input, '\n'))
	{
		tdata.heredoc = ft_split(ft_strchr(input, '\n'), '\n');
		input = ms_cut_at(input, '\n');
	}
	if (quotes_parity_check(input, &tdata) == ERROR)
		return (tdata);
	tdata.t_size = count_tokens(input);
	if (empty_string(&tdata) == ERROR)
		return (tdata);
	tdata.tokens = ms_split(&tdata, input);
	tok_copy = ms_copy_tok(tdata.tokens, tdata.t_size);
	ms_expand(&tdata, denv);
	if (parse_error_checker(input, &tdata, tok_copy) == ERROR)
		return (free_copy(tok_copy), tdata);
	ms_add_path(&tdata, denv);
	return (free_copy(tok_copy), tdata);
}
