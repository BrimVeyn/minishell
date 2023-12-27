/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 16:27:38 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/12/27 16:52:52 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ms_isws(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

t_tokvar init_tokvar(char *symbol, int type)
{
	t_tokvar self;

	self.type = type;
	self.len = ft_strlen(symbol);
	self.str = symbol;
	return (self);
}

t_tokh init_tokh(void)
{
	t_tokh self;
	
	self.i = 0;
	self.j = 0;
	self.k = 0;
	self.tri = 0;
	return (self);
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
	int j;

	j = 0;
	while (ms_isws(input[v->i]))
		v->i++;
	while (!ms_isws(input[v->i]))
	{
		j++;
		v->i++;
	}
	tdata->tokens[v->j] = (char **) ft_calloc (2, sizeof(char *));
	tdata->tokens[v->j][0] = ft_substr(input, v->i - j, j); 
	tdata->type[v->j] = CMD;
	v->j++;
}

void fill_token(char *input, t_tok *tdata)
{
	t_tokvar tokvar;
	t_tokh	v;

	v = init_tokh();
	while (input[v.i])
	{
		v.tri = 0;
		tokvar = ms_tiktok(&input[v.i]);
		if (input[v.i] && tokvar.type != 0)
		{			
			tdata->tokens[v.j] = (char **) ft_calloc (2, sizeof(char *));
			tdata->tokens[v.j][0] = ft_strdup(tokvar.str); 
			tdata->type[v.j] = tokvar.type;
			v.i += tokvar.len;
			v.j += 1;
		}
		if (input[v.i] && tokvar.type == 6)
			extract_delimiter(input, tdata, &v);
		v.k = 0;
		while(ms_isws(input[v.i]))
			v.i++;
		while (input[v.i] && ms_tiktok(&input[v.i]).type == 0)
		{
			v.tri = 1;
			v.k++;
			v.i++;
		}
		if (v.tri == 1)
		{
			tdata->tokens[v.j] = ft_split(ft_substr(input, v.i - v.k, v.k), ' ');
			tdata->type[v.j] = ms_tiktok(&input[v.i - v.k]).type;
			v.j += 1;
		}
	}
}

int count_tokens(char *input)
{
	t_tokvar tokvar;
	int i;
	int trigger;
	int count;
	int off;

	count = 0;
	i = 0;
	trigger = 0;
	
	while (input[i])
	{
		trigger = 0;
		tokvar = ms_tiktok(&input[i]);
		if (input[i] && tokvar.type != 0)
		{
			count += 1;
			i += tokvar.len;
		}
		if (input[i] && tokvar.type == 6)
			count += 1;
		while(ms_isws(input[i]))
			i++;
		while (input[i] && ms_tiktok(&input[i]).type == 0)
		{
			trigger = 1;
			i++;
		}
		if (trigger == 1)
			count += 1;
	}
	return (count);
}

t_tok ms_alloctok(int tokcount)
{
	t_tok self;

	self.tokens = (char ***) ft_calloc(tokcount + 1, sizeof(char **));
	self.type = (int *) ft_calloc(tokcount + 1, sizeof(int));
	self.par = (int *) ft_calloc(tokcount + 1, sizeof(int));
	return(self);
}

t_tok	parse_input(char *input)
{
	t_tok	tdata;
	int		tokcount;

	tokcount = count_tokens(input);
	tdata = ms_alloctok(tokcount);
	printf("Token count : %d\n", tokcount);
	fill_token(input, &tdata);
	for (int i = 0; tdata.tokens[i]; i++)
	{
		printf("S->TYPE[%d] = %d\n", i, tdata.type[i]);
		for (int j = 0; tdata.tokens[i][j]; j++)
			printf("S[%d][%d] = %s\n", i, j, tdata.tokens[i][j]);
	}
	return (tdata);
}
