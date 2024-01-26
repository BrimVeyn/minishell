/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:40:08 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/26 15:24:41 by bvan-pae         ###   ########.fr       */
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

t_tok	parse_input(char *input, t_env *denv)
{
	t_tok	tdata;
	char	**heredoc;

	heredoc = NULL;
	if (ft_strchr(input, '\n'))
	{
		heredoc = ft_split(ft_strchr(input, '\n'), '\n');
		input = ms_cut_at(input, '\n');
	}
	tdata.t_size = count_tokens(input);
	if (tdata.t_size == ERROR)
		return (tdata);
	tdata = init_tok(tdata.t_size, heredoc);
	fill_token(input, &tdata, denv);
	if (quotes_position_check(&tdata) == ERROR)
	{
		tdata.type[0] = ERROR;
		return (tdata);
	}
	ms_add_path(&tdata, denv);
	// for (int i = 0; tdata.tokens[i]; i++)
	// {
	// 	ft_printf("S->TYPE[%d] = %d\n", i, tdata.type[i]);
	// 	for (int j = 0; tdata.tokens[i][j]; j++)
	// 		ft_printf("S[%d][%d] = |%fs|\n", i, j, tdata.tokens[i][j]);
	// }
	if (missing_delimiter_check(&tdata) == ERROR)
		return (tdata);
	return (tdata);
}
