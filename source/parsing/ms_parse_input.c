/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:20:38 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/03/04 10:33:38 by bvan-pae         ###   ########.fr       */
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

void	parse_input(char *input, t_tok *tdata)
{
	tdata->heredoc = NULL;
	tdata->tok_copy = NULL;
	if (ft_strchr(input, '\n'))
	{
		tdata->heredoc = ft_split(ft_strchr(input, '\n'), '\n');
		input = ms_cut_at(input, '\n');
	}
	if (quotes_parity_check(input, tdata) == ERROR)
    {
		tdata->t_size = ERROR;
		tdata->tokens = NULL;
		tdata->type = NULL;
		return ;
    }
	tdata->t_size = count_tokens(input);
	if (empty_string(tdata) == ERROR)
		return ;
	tdata->tokens = ms_split(tdata, input);
	tdata->tok_copy = ms_copy_tok(tdata->tokens, tdata->t_size);
	if (parenthesis_check(input) == ERROR)
	{
		tdata->exitno = 2 << 8;
		tdata->t_size = ERROR;
		return ;
	}
	if (parse_error_checker(tdata) == ERROR)
		return ;
	return ;
}

void ms_parse(t_tok *tdata, t_env *denv, int index)
{
	// ft_printf("t[0] = %fs\n", tdata->tokens[index][0]);
	// ft_printf("t[0] = %d\n", tdata->type[index][0]);
	ms_expand(tdata, denv, index);
	ms_add_path(tdata, denv, index);
	if (ms_ambiguous_error(tdata, index) == ERROR)
	{
		tdata->exitno = 1 << 8;
		tdata->t_size = ERROR;
		tdata->type[index][0] = WRONG;
	}
	// ft_printf("t[0] = %fs\n", tdata->tokens[index][0]);
	// ft_printf("t[0] = %d\n", tdata->type[index][0]);
}

