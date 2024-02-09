/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:20:38 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/02/08 14:20:38 by bvan-pae         ###   ########.fr       */
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
	if (quotes_parity_check(input) == ERROR)
	{
		tdata.t_size = ERROR;
		return (tdata);
	}
	tdata.t_size = count_tokens(input);
	// ft_printf("---------- SIZE = %d -----------\n", tdata.t_size);
	tdata.tokens = ms_split(&tdata, input);
	// for(int i = 0; tdata.tokens[i]; i++)
	// {
	// 	for(int j = 0; tdata.tokens[i][j]; j++)
	//        {
	//            ft_printf("TYPE[%d][%d] = ~[%d]~\n", i, j, tdata.type[i][j]);
	// 		ft_printf("Token_[%d][%d] = %fs\n", i, j, tdata.tokens[i][j]);
	//        }
	// }
	tok_copy = ms_copy_tok(tdata.tokens, tdata.t_size);
	ms_expand(&tdata, denv);
	//    ft_printf("-------------- AFTER EXPAND -----------\n");
	// for(int i = 0; tdata.tokens[i]; i++)
	// {
	// 	for(int j = 0; tdata.tokens[i][j]; j++)
	//        {
	//            ft_printf("TYPE[%d][%d] = ~[%d]~\n", i, j, tdata.type[i][j]);
	// 		ft_printf("Token_[%d][%d] = %fs\n", i, j, tdata.tokens[i][j]);
	//        }
	// }
	//    ft_printf("-------------- AFTER EXPAND -----------\n");
	// for(int i = 0; tok_copy[i]; i++)
	// {
	// 	for(int j = 0; tok_copy[i][j]; j++)
	//        {
	// 		ft_printf("COPY[%d][%d] = %fs\n", i, j, tok_copy[i][j]);
	//        }
	// }
	if (ms_token_error(&tdata) == ERROR || ms_newline_error(&tdata) == ERROR
		|| parenthesis_check(input) == ERROR)
	{
		g_exitno = 2 << 8;
		tdata.t_size = ERROR;
		free_copy(tok_copy);
		return (tdata);
	}
	if (ms_ambiguous_error(&tdata, tok_copy) == ERROR)
	{
		g_exitno = 1 << 8;
		tdata.t_size = ERROR;
		free_copy(tok_copy);
		return (tdata);
	}
	ms_add_path(&tdata, denv);
	//    ft_printf("-------------- AFTER PATH_ADD -----------\n");
	// for(int i = 0; tdata.tokens[i]; i++)
	// {
	// 	for(int j = 0; tdata.tokens[i][j]; j++)
	//        {
	//            ft_printf("TYPE[%d][%d] = ~[%d]~\n", i, j, tdata.type[i][j]);
	// 		ft_printf("Token_[%d][%d] = %fs\n", i, j, tdata.tokens[i][j]);
	//        }
	// }
	return (free_copy(tok_copy), tdata);
}
