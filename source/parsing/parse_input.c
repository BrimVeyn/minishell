/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 11:22:39 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/02/07 17:30:01 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int g_exitno;

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

int ms_typecmdtok(int type)
{
	if (type == D_AL
	|| type == S_AL
	|| type == D_AR
	|| type == S_AR)
		return (TRUE);
	return (ERROR);
}


int	ms_typetok(int type)
{
	if (type == P_O
	|| type == P_C
	|| type == PIPE
	|| type == AND
	|| type == OR)
		return (TRUE);
	return (ERROR);
}

int ms_token_error(t_tok *tdata)
{
    int i;

    i = 0;
    if (ms_typetok(tdata->type[0][0]) == TRUE && tdata->type[0][0] != P_O)
    {
        fd_printf(2, "minishell: syntax error near unexpected token `%fs'\n", tdata->tokens[0][0]);
        return (ERROR);
    }
    while (tdata->tokens[i])
    {
		if (tdata->type[i][0] == P_C && tdata->type[i + 1] && tdata->type[i + 1][0] == CMD)
		{
			fd_printf(2, "minishell: syntax error near unexpected token `%fs'\n", tdata->tokens[i + 1][0]);
			return (ERROR);
		}
		if (tdata->type[i][0] == CMD && tdata->type[i + 1] && tdata->type[i + 1][0] == P_O)
		{
			fd_printf(2, "minishell: syntax error near unexpected token `%fs'\n", tdata->tokens[i + 1][0]);
			return (ERROR);
		}
        if (ms_typetok(tdata->type[i][0]) == TRUE)
        {
            if (tdata->tokens[i + 1] && ms_typetok(tdata->type[i + 1][0]) == TRUE && ms_typetok(tdata->type[i][0]) != P_C 
                && ms_typetok(tdata->type[i + 1][0]) != P_O)
            {
                fd_printf(2, "minishell: syntax error near unexpected token `%fs'\n", tdata->tokens[i + 1][0]);
                return (ERROR);
            }
            else if (!tdata->tokens[i + 1] && tdata->type[i][0] != P_C)
            {
                fd_printf(2, "minishell: syntax error near unexpected token `%fs'\n", tdata->tokens[i][0]);
                return (ERROR);
            }
        }
        i++;
    }
    return (TRUE);
}

int ms_newline_error(t_tok *tdata)
{
    int i;
    int j;

    i = 0;
    while (tdata->tokens[i])
    {
        j = 0;
        while (tdata->tokens[i][j])
        {
            if (ms_typecmdtok(tdata->type[i][j]) == TRUE)
            {
                if (tdata->tokens[i][j + 1] && ms_typecmdtok(tdata->type[i][j + 1]) == TRUE)
                {
                    fd_printf(2, "minishell: syntax error near unexpected token `%fs'\n", tdata->tokens[i][j + 1]);
                    return (ERROR);
                }
                else if (!tdata->tokens[i][j + 1])
                {
                    fd_printf(2, "minishell: syntax error near unexpected token `newline'\n");
                    return (ERROR);
                }
            }
            j++;
        }
        i++;
    }
    return (TRUE);
}


char ***ms_copy_tok(char ***tokens, int t_size)
{
	char ***tok_copy;
	int	i;
	int j;

	tok_copy = ft_calloc(t_size + 2, sizeof(char **));
	i = 0;
	while (tokens[i])
	{
		tok_copy[i] = ft_calloc(ms_tablen(tokens[i]) + 1, sizeof(char *));
		j = 0;
		while (tokens[i][j])
		{
			tok_copy[i][j] = ft_strdup(tokens[i][j]);
			j++;
		}
		i++;
	}
	return (tok_copy);
}

int	ms_count_words(char *input)
{
	int i;
	int counter;
	int trigger;

	i = 0;
	counter = 0;
	while (input[i])
	{
		trigger = 0;
		while (input[i] && ms_isws(input[i]))
			i++;
		while (input[i] && !ms_isws(input[i]))
		{
			i++;
			trigger = 1;
		}
		if (trigger == 1)
			counter += 1;
	}
	return (counter);
}


int ms_ambiguous_error(t_tok *tdata, char ***tok_copy)
{
	int i;
	int j;

	i = 0;
	while (tdata->tokens[i])
	{
		j = 0;
		while (tdata->tokens[i][j])
		{
			if (ms_typecmdtok(tdata->type[i][j]) == TRUE)
				if (ms_count_words(tdata->tokens[i][j + 1]) > 1)
                {
					fd_printf(2, "minishell: %fs: ambiguous redirect\n", tok_copy[i][j + 1]);
					return (ERROR);
                }
			j++;
		}
		i++;
	}
	return (TRUE);
}

void	free_copy(char ***tokens)
{
	int	i;
	int	j;

	i = 0;
	if (!tokens)
		return ;
	while (tokens[i])
	{
		j = 0;
		while (tokens[i][j])
		{
			free(tokens[i][j]);
			j++;
		}
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

t_tok	parse_input(char *input, t_env *denv)
{
	t_tok	tdata;
	char	**heredoc;
	char	***tok_copy;

    (void) heredoc;
	heredoc = NULL;
	tok_copy = NULL;
	if (ft_strchr(input, '\n'))
	{
		heredoc = ft_split(ft_strchr(input, '\n'), '\n');
		input = ms_cut_at(input, '\n');
	}
	if (quotes_parity_check(input) == ERROR)
	{
		tdata.t_size = ERROR;
		return (tdata);
	}
	tdata.t_size = count_tokens(input);
	// ft_printf("---------- SIZE = %d -----------\n", tdata.t_size);
	tdata.tokens = ms_split(&tdata, denv, input);
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
    if (ms_token_error(&tdata) == ERROR || ms_newline_error(&tdata) == ERROR || parenthesis_check(input) == ERROR) 
    {
        g_exitno = 2;
        tdata.t_size = ERROR;
		free_copy(tok_copy);
        return (tdata);
    }
	if (ms_ambiguous_error(&tdata, tok_copy) == ERROR)
	{
		g_exitno = 1;
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
