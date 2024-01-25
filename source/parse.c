/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:40:08 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/25 14:40:52 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <string.h>

t_tokvar ms_tiktok(char *ptr)
{
	if (!ft_strncmp(ptr, "||", 2))
		return(init_tokvar("||", OR));
	if (!ft_strncmp(ptr, "&&", 2))
		return(init_tokvar("&&", AND));
	if (!ft_strncmp(ptr, ">>", 2))
		return(init_tokvar(">>", D_AR));
	if (!ft_strncmp(ptr, "<<", 2))
		return(init_tokvar("<<", D_AL));
	if (!ft_strncmp(ptr, "<", 1))
		return(init_tokvar("<", S_AL));
	if (!ft_strncmp(ptr, ">", 1))
		return(init_tokvar(">", S_AR));
	if (!ft_strncmp(ptr, "(", 1))
		return(init_tokvar("(", P_O));
	if (!ft_strncmp(ptr, ")", 1))
		return(init_tokvar(")", P_C));
	if (!ft_strncmp(ptr, "|", 1))
		return(init_tokvar("|", PIPE));
	return(init_tokvar("", CMD));
}

int count_tokens(char *input)
{
	t_tokvar tokvar;
	int i;
	int trigger;
	int count;
	int dcount;

	count = 0;
	i = 0;
	trigger = 0;
	dcount = 0;
	if (parenthesis_check(input) == ERROR || quotes_parity_check(input) == ERROR)
		return (ERROR);
	
	while (input[i])
	{
		trigger = 0;
		tokvar = ms_tiktok(&input[i]);
		if (input[i] && tokvar.type != CMD && tokvar.type != D_AL && tokvar.type != S_AL)
		{
			count += 1;
			if (start_check(input, tokvar, i) == ERROR)
				return (ERROR);
			if (end_check(input, tokvar, i) == ERROR)
				return (ERROR);
			i += tokvar.len;
		}
		if (input[i] && (tokvar.type == D_AL || tokvar.type == S_AL))
		{
			if (tokvar.type == S_AL)
				dcount = delimiter_check(&input[i + 1]);
			else if (tokvar.type == D_AL)
				dcount = delimiter_check(&input[i + 2]);
			i += 2 + dcount;
			if (dcount == 0)
				return (ERROR);
			count += 2;
		}
		while(input[i] && ms_isws(input[i]))
			i++;
		while (input[i] && ms_tiktok(&input[i]).type == CMD)
		{
			trigger = 1;
			i++;
		}
		if (trigger == 1)
			count += 1;
		while (input[i] && (ms_tiktok(&input[i]).type == D_AL || ms_tiktok(&input[i]).type == S_AL))
		{
			i += 2;
			while (input[i] && !ms_isws(input[i]))
				i++;
			while (input[i] && ms_tiktok(&input[i]).type == CMD)
				i++;
		}
	}
	return (count);
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
	printf("Token count : %d\n", tdata.t_size);
	fill_token(input, &tdata, denv);
	if (quotes_position_check(&tdata) == ERROR)
	{
		tdata.type[0] = ERROR;
		return (tdata);
	}
	ms_add_path(&tdata, denv);
	if (missing_delimiter_check(&tdata) == ERROR)
    {
		fd_printf(2, "minishell: syntax error near unexpected token `newline'\n");
		printf("SALOPE");
		tdata.type[0] = WRONG;
		return (tdata);
    }
	for (int i = 0; tdata.tokens[i]; i++)
	{
		printf("S->TYPE[%d] = %d\n", i, tdata.type[i]);
		for (int j = 0; tdata.tokens[i][j]; j++)
			printf("S[%d][%d] = %s\n", i, j, tdata.tokens[i][j]);
	}
	return (tdata);
}
