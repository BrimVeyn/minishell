/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 16:27:38 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/12/28 17:21:24 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ms_isws(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

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
	if (!ft_strncmp(ptr, "$", 1))
		return(init_tokvar("$", DOLLAR));
	if (!ft_strncmp(ptr, "|", 1))
		return(init_tokvar("|", PIPE));
	return(init_tokvar("", CMD));
}
//split ' ' | " " | >> | << | > | < | && | || ( ) | * |

void	extract_delimiter(char *input, t_tok *tdata, t_tokh *v)
{
	int len;

	len = 0;
	while (input[v->i] && ms_isws(input[v->i]))
		v->i++;
	while (input[v->i] && !ms_isws(input[v->i]) && ms_tiktok(&input[v->i]).type == CMD)
	{
		len++;
		v->i++;
	}
	tdata->tokens[v->j] = (char **) ft_calloc (2, sizeof(char *));
	tdata->tokens[v->j][0] = ft_substr(input, v->i - len, len); 
	tdata->type[v->j] = DELIMITER;
	v->j++;
}


char **parse_command(char *cmd)
{
	char **args;

	printf("%s", cmd);
	return (args);
}

char *grep_word(char *input, t_tokh *v)
{
	int	len;

	len = 0;
	while(input[v->i] && ms_isws(input[v->i]))
		v->i++;
	while(input[v->i] && !ms_isws(input[v->i]) && ms_tiktok(&input[v->i]).type == CMD)
	{
		len++;
		v->i++;
	}
	return(ft_substr(input, v->i - len, len));
}

int	ms_wl2(char *ptr)
{
	if (!ft_strncmp(ptr, ">>", 2) ||
		!ft_strncmp(ptr, ">", 1) ||
		!ft_strncmp(ptr, "<", 1))
		return(1);
	return(0);
}

void fill_token(char *input, t_tok *tdata)
{
	t_tokvar tokvar;
	t_tokh	v;

	v = init_tokh();
	while (input[v.i])
	{
		v.tri = 0;
		if (input[v.i])
			tokvar = ms_tiktok(&input[v.i]);
		if (input[v.i] && tokvar.type != CMD)
		{
			tdata->tokens[v.j] = (char **) ft_calloc (2, sizeof(char *));
			tdata->tokens[v.j][0] = ft_strdup(tokvar.str); 
			tdata->type[v.j] = tokvar.type;
			v.j++;
			v.i += tokvar.len;
			if (input[v.i] && ms_wl2(&input[v.i - tokvar.len]) && ms_tiktok(&input[v.i]).type == CMD)
			{
				// printf("J = %d I = %d\n", v.j, v.i);
				tdata->tokens[v.j] = (char **) ft_calloc (2, sizeof(char *));
				tdata->tokens[v.j][0] = grep_word(input, &v); 
				tdata->type[v.j] = FAILE; 
				// printf("J = %d I = %d\n", v.j, v.i);
				v.j++;
			}
		}
		if (input[v.i] && tokvar.type == D_AL)
		{
			// ft_printf("DEL %d\n", v.j);
			extract_delimiter(input, tdata, &v);
		}
		// ft_printf("I = %d",  v.i);
		while(input[v.i] && ms_isws(input[v.i]))
			v.i++;
		v.k = 0;
		while (input[v.i] && ms_tiktok(&input[v.i]).type == CMD)
		{
			v.tri = 1;
			v.k++;
			v.i++;
		}
		if (v.tri == 1)
		{
			// tdata->tokens[v.j] = parse_command(ft_substr(input, v.i - v.k, v.k));
			// ft_printf("SYM %d\n", v.j);
			tdata->tokens[v.j] = ft_split(ft_substr(input, v.i - v.k, v.k), ' ');
			tdata->type[v.j] = ms_tiktok(&input[v.i - v.k]).type;
			v.j++;
		}
	}
}

int	count_delimiter(char *input)
{
	int len;
	int i;

	len = 0;
	i = 0;
	while (ms_isws(input[i]))
		i++;
	while (input[i] && !ms_isws(input[i]) && ms_tiktok(&input[i]).type == CMD)
	{
		len++;
		i++;
	}
	// ft_printf("len ===== %d\n", len);
	if (len == 0 && !input[i])
	{
		fd_printf(2, "bash: syntax error near unexpected token `newline'\n");
	}
	else if (len ==  0 && input[i] && ms_tiktok(&input[i]).type != CMD)
	{
		fd_printf(2, "bash: syntax error near unexpected token `%fs'\n", ms_tiktok(&input[i]).str);
	}
	return (len);
}

int	ms_wl(char *ptr)
{
	if (!ft_strncmp(ptr, "||", 2) ||
		!ft_strncmp(ptr, "&&", 2) ||
		!ft_strncmp(ptr, "|", 1))
		return(1);
	return(0);
}

int	check_errors(char *input, t_tokvar tokvar, int i)
{
	int icpy;

	icpy = i;
	if (icpy != 0)
	{
		icpy -= ms_tiktok(&input[i]).len;
	}
	while (icpy != 0 && input[icpy] && ms_isws(input[icpy]))
		icpy--;
	if(icpy == 0 && ms_wl(ms_tiktok(&input[i]).str))
	{
		fd_printf(2, "bash: syntax error near unexpected token `%fs'\n", ms_tiktok(&input[i]).str);
		return(ERROR);
	}
	else if (icpy == 0)
	{
		if (input[i + 1] && ms_tiktok(&input[i + ms_tiktok(&input[i]).len]).type != CMD)
			fd_printf(2, "bash: syntax error near unexpected token `%fs'\n", ms_tiktok(&input[i + ms_tiktok(&input[i]).len]).str);
		else
			fd_printf(2, "bash: syntax error near unexpected token `newline'\n");
		return (ERROR);
	}
	return (0);
}


int count_tokens(char *input)
{
	t_tokvar tokvar;
	int i;
	int trigger;
	int count;
	int off;
	int dcount;

	count = 0;
	i = 0;
	trigger = 0;
	dcount = 0;
	while (input[i])
	{
		trigger = 0;
		tokvar = ms_tiktok(&input[i]);
		if (input[i] && tokvar.type != CMD && tokvar.type != D_AL)
		{
			// printf("COUNTED ANYSYM\n");
			count += 1;
			if (check_errors(input, tokvar, i) == ERROR)
				return (ERROR);
			i += tokvar.len;
		}
		if (input[i] && tokvar.type == D_AL)
		{
			// printf("COUNTED <<\n");
			dcount = count_delimiter(&input[i + 2]);
			i += 2 + dcount;
			if (!dcount)
				return (ERROR);
			// printf("COUNTED DELIMITER\n");
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
		{
			// printf("COUNTED CMD\n");
			count += 1;
		}
	}
	return (count);
}

t_tok	parse_input(char *input, t_env *denv)
{
	t_tok	tdata;
	int		tokcount;

	tokcount = count_tokens(input);
	if (tokcount == ERROR)
		return (tdata);
	tdata = init_tok(tokcount);
	printf("Token count : %d\n", tokcount);
	fill_token(input, &tdata);
	// ms_add_path(&tdata, denv);
	for (int i = 0; tdata.tokens[i]; i++)
	{
		printf("S->TYPE[%d] = %d\n", i, tdata.type[i]);
		for (int j = 0; tdata.tokens[i][j]; j++)
			printf("S[%d][%d] = %s\n", i, j, tdata.tokens[i][j]);
	}
	return (tdata);
}
