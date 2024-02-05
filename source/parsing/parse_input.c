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

int	coherence_check_helper(char *input, t_tok *tdata, int *i)
{
	char	*tmp;
	int		type;

	tmp = ms_tiktok(&input[*i]).str;
	type = ms_tiktok(&input[*i]).type;
	*i += ms_tiktok(&input[*i]).len;
	while (ms_isws(input[*i]))
		(*i)++;
	if ((type != P_C && type != P_O)
		&& (!input[*i] || (input[*i] && ms_tiktok(&input[*i]).type != CMD)))
	{
		tdata->t_size = ERROR;
		fd_printf(2, "minishell: syntax error near unexpected token `%fs'\n",
			tmp);
		return (ERROR);
	}
	return (TRUE);
}

int	coherence_check(char *input, t_tok *tdata)
{
	int	i;
	int	q[2];

	i = 0;
	q[0] = 0;
	q[1] = 0;
	while (input[i])
	{
		while (input[i] && (ms_tiktok(&input[i]).type == CMD || (q[0] || q[1])))
		{
			q[0] ^= (input[i] == '\"');
			q[1] ^= (input[i] == '\'');
			i++;
		}
		if (input[i] && coherence_check_helper(input, tdata, &i) == ERROR)
			return (ERROR);
	}
	return (TRUE);
}

t_tok	parse_input(char *input, t_env *denv)
{
	t_tok	tdata;
	char	**heredoc;

	(void) denv;
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
		ft_printf("TYPE[%d] = ~[%d]~\n", i, tdata.type[i]);
		for(int j = 0; tdata.tokens[i][j]; j++)
			ft_printf("Token_[%d][%d] = %fs\n", i, j, tdata.tokens[i][j]);
	}
    ms_expand(&tdata, denv);
    ft_printf("-------------- AFTER EXPAND -----------\n");
	for(int i = 0; tdata.tokens[i]; i++)
	{
		ft_printf("TYPE[%d] = ~[%d]~\n", i, tdata.type[i]);
		for(int j = 0; tdata.tokens[i][j]; j++)
			ft_printf("Token_[%d][%d] = %fs\n", i, j, tdata.tokens[i][j]);
	}
	ms_add_path(&tdata, denv);
    ft_printf("-------------- AFTER PATH_ADD -----------\n");
	for(int i = 0; tdata.tokens[i]; i++)
	{
		ft_printf("TYPE[%d] = ~[%d]~\n", i, tdata.type[i]);
		for(int j = 0; tdata.tokens[i][j]; j++)
			ft_printf("Token_[%d][%d] = %fs\n", i, j, tdata.tokens[i][j]);
	}
	// if (missing_delimiter_check(&tdata) == ERROR)
	return (tdata);
}
