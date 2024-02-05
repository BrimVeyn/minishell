/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 11:22:39 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/02/02 16:23:14 by bvan-pae         ###   ########.fr       */
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

// int ms_token_error(t_tok *tdata)
// {
//     int i;
//     int j;
//
//     i = 0;
//     while (tdata->tokens[i])
//     {
//         if (ms_wltoken(tdata->tokens[i][0]) == TRUE)
//         {
//             if (i == 0 && tdata->tokens[i + 1] && ms_wltoken(tdata->tokens[i + 1][0]) == TRUE)
//                 fd_printf(2, "minishell: parsing error near unexpected token `%fs'\n", tdata->tokens[i][0]);
//         }
//         i++;
//     }
//     return (TRUE);
// }


t_tok	parse_input(char *input, t_env *denv)
{
	t_tok	tdata;
	char	**heredoc;

    (void) heredoc;
	heredoc = NULL;
	if (ft_strchr(input, '\n'))
	{
		heredoc = ft_split(ft_strchr(input, '\n'), '\n');
		input = ms_cut_at(input, '\n');
	}
	if (quotes_parity_check(input) == ERROR)
	{
		tdata.t_size = ERROR;
		ft_printf("quotes error\n");
		return (tdata);
	}
	tdata.t_size = count_tokens(input);
	ft_printf("---------- SIZE = %d -----------\n", tdata.t_size);
	tdata.tokens = ms_split(&tdata, denv, input);
	for(int i = 0; tdata.tokens[i]; i++)
	{
		for(int j = 0; tdata.tokens[i][j]; j++)
        {
            ft_printf("TYPE[%d][%d] = ~[%d]~\n", i, j, tdata.type[i][j]);
			ft_printf("Token_[%d][%d] = %fs\n", i, j, tdata.tokens[i][j]);
        }
	}
    ms_expand(&tdata, denv);
    ft_printf("-------------- AFTER EXPAND -----------\n");
	for(int i = 0; tdata.tokens[i]; i++)
	{
		for(int j = 0; tdata.tokens[i][j]; j++)
        {
            ft_printf("TYPE[%d][%d] = ~[%d]~\n", i, j, tdata.type[i][j]);
			ft_printf("Token_[%d][%d] = %fs\n", i, j, tdata.tokens[i][j]);
        }
	}
	ms_add_path(&tdata, denv);
    // if (ms_token_error(&tdata) == ERROR)
    //     tdata.type[0] = ERROR;
    ft_printf("-------------- AFTER PATH_ADD -----------\n");
	for(int i = 0; tdata.tokens[i]; i++)
	{
		for(int j = 0; tdata.tokens[i][j]; j++)
        {
            ft_printf("TYPE[%d][%d] = ~[%d]~\n", i, j, tdata.type[i][j]);
			ft_printf("Token_[%d][%d] = %fs\n", i, j, tdata.tokens[i][j]);
        }
	}
	return (tdata);
}
