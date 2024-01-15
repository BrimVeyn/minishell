/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 10:49:15 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/15 17:18:43 by bvan-pae         ###   ########.fr       */
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
	if (!ft_strncmp(ptr, "(", 1))
		return(init_tokvar("(", P_O));
	if (!ft_strncmp(ptr, ")", 1))
		return(init_tokvar(")", P_C));
	// if (!ft_strncmp(ptr, "$", 1))
	// 	return(init_tokvar("$", DOLLAR));
	if (!ft_strncmp(ptr, "|", 1))
		return(init_tokvar("|", PIPE));
	return(init_tokvar("", CMD));
}
//split ' ' | " " | >> | << | > | < | && | || ( ) | * |

void	extract_delimiter(char *input, t_tok *tdata, t_tokh *v)
{
	int		len;
	char	*tmp;

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
	tmp = ft_strtrimf(tdata->tokens[v->j][0], "'");
	tmp = ft_strtrimf(tmp, "\"");
	tdata->tokens[v->j][0] = tmp;
	tdata->type[v->j] = DELIMITER;
	v->j++;
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
		(!ft_strncmp(ptr, "<", 1)) && ft_strncmp(ptr, "<<", 2))
		return(1);
	return(0);
}

int	f_lcmd_index(t_tok *tdata, int j)
{
	j--;
	while (tdata->type[j] != CMD)
		j--;
	return (j);
}

int ms_tablen(char **tab)
{
	int i;

	i = 0;
	while(tab[i])
		i++;
	return(i);
}

char **ms_joinstarstar(char **p1, char **p2)
{
	char **new;
	int i;
	int	j;

	i = -1;
	j = -1;
	new = ft_calloc(ms_tablen(p1) + ms_tablen(p2) + 1, sizeof(char *));
	while(p1[++i])
		new[i] = ft_strdup(p1[i]);
	while(p2[++j])
		new[i++] = ft_strdup(p2[j]);
	return(new);
}

char **add_args_to_cmd(char *input, t_tokh *v, t_tok *tdata, t_env *denv)
{
	char **to_add;
	char **new;
	v->k = 0;
	while (input[v->i] && ms_tiktok(&input[v->i]).type == CMD)
	{
		v->k++;
		v->i++;
	}
	to_add = ft_splitm(ft_substr(input, v->i - v->k, v->k), tdata, denv);
	new = ms_joinstarstar(tdata->tokens[v->l], to_add);
	// for (int j = 0; new[j]; j++)
	// 	ft_printf("to_add[%d] = %s\n", j, new[j]);
	free_tab(tdata->tokens[v->l]);
	free_tab(to_add);
	return (new);
}

char **add_here_to_cmd(char **token, char *input, t_tokh *v)
{
	char	**to_add;
	char	**new;
	char	*d_al;
	char	*delimiter;
	v->k = 0;
	to_add = (char **) ft_calloc(3, sizeof(char *));
	d_al = ft_strdup(ms_tiktok((&input[v->i])).str);
	v->i += 2;
	while (input[v->i] && !ms_isws(input[v->i]))
	{
		v->k++;
		v->i++;
	}
	delimiter = ft_substr(input, v->i - v->k, v->k);
	to_add[0] = d_al;
	to_add[1] = delimiter;
	new = ms_joinstarstar(token, to_add);
	// for (int j = 0; new[j]; j++)
	// 	ft_printf("to_add[%d] = %s\n", j, new[j]);
	free_tab(token);
	free_tab(to_add);
	return (new);
}

void fill_token(char *input, t_tok *tdata, t_env *denv)
{
	t_tokvar tokvar;
	t_tokh	v;

	v = init_tokh();
	while (input[v.i])
	{
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
				if (input[v.i] && ms_tiktok(&input[v.i]).type == CMD)
				{
					v.l = f_lcmd_index(tdata, v.j);
					// printf("THE NUMBER IS %d\n", k);
					tdata->tokens[v.l] = add_args_to_cmd(input, &v, tdata, denv);
				}
			}
		}
		if (input[v.i] && tokvar.type == D_AL)
		{
			// ft_printf("DEL %d\n", v.j);
			extract_delimiter(input, tdata, &v);
		}
		while(input[v.i] && ms_isws(input[v.i]))
			v.i++;
		v.k = 0;
		v.tri = 0;
		while (input[v.i] && ms_tiktok(&input[v.i]).type == CMD)
		{
			// ft_printf("\nI = %fs\n",  &input[v.i]);
			v.tri = 1;
			v.k++;
			v.i++;
		}
		if (v.tri == 1)
		{
			// tdata->tokens[v.j] = parse_command(ft_substr(input, v.i - v.k, v.k));
			tdata->tokens[v.j] = ft_splitm(ft_substr(input, v.i - v.k, v.k), tdata, denv);
			tdata->type[v.j] = ms_tiktok(&input[v.i - v.k]).type;
			v.j++;
		}
		while (ms_tiktok(&input[v.i]).type == D_AL && v.i > 0)
		{
			v.l = f_lcmd_index(tdata, v.j);
			// printf("the number is %d\n", k);
			tdata->tokens[v.l] = add_here_to_cmd(tdata->tokens[v.l] ,input, &v);
			tdata->tokens[v.l] = add_args_to_cmd(input, &v, tdata, denv);
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
		fd_printf(2, "minishell: syntax error near unexpected token `newline'\n");
	}
	else if (len ==  0 && input[i] && ms_tiktok(&input[i]).type != CMD)
	{
		fd_printf(2, "minishell: syntax error near unexpected token `%fs'\n", ms_tiktok(&input[i]).str);
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

int start_check(char *input, t_tokvar tokvar, int i)
{
	int icpy;

	icpy = i;
	if (tokvar.type == P_O || tokvar.type == P_C)
		return(0);
	if (icpy != 0)
	{
		icpy -= ms_tiktok(&input[i]).len;
	}
	while (icpy != 0 && input[icpy] && ms_isws(input[icpy]))
		icpy--;
	if(icpy == 0 && ms_wl(ms_tiktok(&input[i]).str))
	{
		fd_printf(2, "minishell: syntax error near unexpected token `%fs'\n", ms_tiktok(&input[i]).str);
		return(ERROR);
	}
	else if (icpy == 0)
	{
		if (input[i + 1] && ms_tiktok(&input[i + ms_tiktok(&input[i]).len]).type != CMD)
		{
			fd_printf(2, "minishell: syntax error near unexpected token `%fs'\n", ms_tiktok(&input[i + ms_tiktok(&input[i]).len]).str);
		}
		else
        {
			fd_printf(2, "minishell: syntax error near unexpected token `newline'\n");
        }
		return (ERROR);
	}
	return (0);
}

int end_check(char *input, t_tokvar tokvar, int i)
{
	int	icpy;

	icpy = i + ms_tiktok(&input[i]).len;
	while (input[icpy] && ms_isws(input[icpy]))
		icpy++;
	if (!input[icpy] && ms_tiktok(&input[icpy - 2]).type != CMD)
    {
		fd_printf(2, "minishell: syntax error near unexpected token `%fs'\n", ms_tiktok(&input[icpy - 2]).str);
		return (ERROR);
    }
	else if (!input[icpy] && ms_tiktok(&input[icpy - 1]).type != CMD && ms_tiktok(&input[icpy - 1]).type != P_O && ms_tiktok(&input[icpy - 1]).type != P_C)
    {
		fd_printf(2, "minishell: syntax error near unexpected token `%fs'\n", ms_tiktok(&input[icpy - 1]).str);
		return (ERROR);
    }
	return (0);	
}

int	parenthesis_check(char *input)
{
	int p;
	int	i;
	
	i = 0;
	p = 0;
	while (input[i])
	{
		if (input[i] == '(')
			p += 1;
		if (input[i] == ')')
			p -= 1;
		i++;
	}
	if (p == 0)
		return (1);
	else if (p > 0)
    {
		fd_printf(2, "minishell: syntax error near unexpected token `)'\n");
		return (ERROR);
    }
	else
	{
		fd_printf(2, "minishell: syntax error near unexpected token `('\n");
		return (ERROR);
	}
}

int quotes_check(char *str)
{
	int	i;
	int	*quotes;

	i = 0;
	quotes = (int *) ft_calloc(3, sizeof(int));
	if (!quotes)
		return (ERROR);
	while (str[i])
	{
		if (str[i] == SQUOTE)
			quotes[0]++;
		else if (str[i] == DQUOTE)
			quotes[1]++;
		i++;
	}
	if (quotes[0] % 2 != 0)
    {
		fd_printf(2, "minishell: parsing error: unclosed single quotes\n");
		return (ERROR);
    }
	if (quotes[1] % 2 != 0)
    {
		fd_printf(2, "minishell: parsing error: unclosed double quotes\n");
		return (ERROR);
    }
	free(quotes);
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
	if (parenthesis_check(input) == ERROR || quotes_check(input) == ERROR)
		return (ERROR);
	while (input[i])
	{
		trigger = 0;
		tokvar = ms_tiktok(&input[i]);
		if (input[i] && tokvar.type != CMD && tokvar.type != D_AL)
		{
			// printf("COUNTED ANYSYM\n");
			count += 1;
			if (start_check(input, tokvar, i) == ERROR)
				return (ERROR);
			if (end_check(input, tokvar, i) == ERROR)
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
		while (input[i] && ms_tiktok(&input[i]).type == D_AL)
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

	// ft_printf("IN_PARSE\n");
	// ms_dprint(denv->flist);
	tdata.t_size = count_tokens(input);
	if (tdata.t_size == ERROR)
		return (tdata);
	tdata = init_tok(tdata.t_size);
	printf("Token count : %d\n", tdata.t_size);
	fill_token(input, &tdata, denv);
	ms_add_path(&tdata, denv);
	for (int i = 0; tdata.tokens[i]; i++)
	{
		printf("S->TYPE[%d] = %d\n", i, tdata.type[i]);
		for (int j = 0; tdata.tokens[i][j]; j++)
			printf("S[%d][%d] = %s\n", i, j, tdata.tokens[i][j]);
	}
	return (tdata);
}
