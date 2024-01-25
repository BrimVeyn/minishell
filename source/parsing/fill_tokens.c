/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 14:40:02 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/25 14:40:43 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void fill_token_helper(t_tok *tdata, t_tokh *v, t_env *denv, char *input)
{
	tdata->tokens[v->j] = (char **) ft_calloc (2, sizeof(char *));
	tdata->tokens[v->j][0] = ft_strdup(v->tokvar.str); 
	tdata->type[v->j] = v->tokvar.type;
	v->j++;
	v->i += v->tokvar.len;
	if (input[v->i] && ms_wl2(&input[v->i - v->tokvar.len]) && ms_tiktok(&input[v->i]).type == CMD)
	{
		tdata->tokens[v->j] = (char **) ft_calloc (2, sizeof(char *));
		tdata->tokens[v->j][0] = grep_word(input, v); 
		tdata->type[v->j] = FAILE; 
		v->j++;
		if (input[v->i] && ms_tiktok(&input[v->i]).type == CMD && tdata->type[0] != S_AL)
		{
			v->l = f_lcmd_index(tdata, v->j);
			tdata->tokens[v->l] = add_args_to_cmd(input, v, tdata, denv);
		}
	}
}

void fill_token_helper2(t_tok *tdata, t_tokh *v, t_env *denv, char *input)
{
	char *tmp;

	tmp = ft_substr(input, v->i - v->k, v->k);
	tdata->tokens[v->j] = ft_splitm(tmp, tdata, denv);
	free(tmp);
	tdata->type[v->j] = ms_tiktok(&input[v->i - v->k]).type;
	v->j++;
}

void fill_token_helper3(t_tokh *v)
{
	v->tri = 1;
	v->k++;
	v->i++;
}

void fill_token(char *input, t_tok *tdata, t_env *denv)
{
	t_tokh	v;

	v = init_tokh();
	while (input[v.i])
	{
		v.tokvar = ms_tiktok(&input[v.i]);
		if (input[v.i] && v.tokvar.type != CMD)
			fill_token_helper(tdata, &v, denv, input);
		if (input[v.i] && v.tokvar.type == D_AL)
			extract_delimiter(input, tdata, &v);
		while(input[v.i] && ms_isws(input[v.i]))
			v.i++;
		v.k = 0;
		v.tri = 0;
		while (input[v.i] && ms_tiktok(&input[v.i]).type == CMD)
			fill_token_helper3(&v);
		if (v.tri == 1)
			fill_token_helper2(tdata, &v, denv, input);
		while ((ms_tiktok(&input[v.i]).type == S_AL || ms_tiktok(&input[v.i]).type == D_AL) && v.i > 0)
		{
			v.l = f_lcmd_index(tdata, v.j);
			tdata->tokens[v.l] = add_here_to_cmd(tdata->tokens[v.l] ,input, &v, tdata);
			tdata->tokens[v.l] = add_args_to_cmd(input, &v, tdata, denv);
		}
	}
}
