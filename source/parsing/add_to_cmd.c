/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 14:17:10 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/31 10:51:50 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**add_args_to_cmd(char *input, t_tokh *v, t_tok *tdata, t_env *denv)
{
	char	**to_add;
	char	**new;

	v->k = 0;
	while (input[v->i] && ms_tiktok(&input[v->i]).type == CMD)
	{
		v->k++;
		v->i++;
	}
	to_add = ft_splitm(ft_substr(input, v->i - v->k, v->k), denv);
	new = ms_joinstarstar(tdata->tokens[v->l], to_add);
	free_tab(tdata->tokens[v->l]);
	free_tab(to_add);
	return (new);
}

char *iterate_through_word(char *input, t_tokh *v)
{
	int q[2];

	q[0] = 0;
	q[1] = 0;
	while (input[v->i] && ((ms_tiktok(&input[v->i]).type == CMD) || (q[0] == 1 || q[1] == 1)))
	{
		q[0] ^= (input[v->i] == '\"');
		q[1] ^= (input[v->i] == '\'');
		v->k++;
		v->i++;
	}
	if (q[0] == 0)
		return (ms_strtrimf(ft_substr(input, v->i - v->k, v->k), "\""));
	else if (q[1] == 0)
		return (ms_strtrimf(ft_substr(input, v->i - v->k, v->k), "\'"));
	else
		return (ft_substr(input, v->i - v->k, v->k));
}

char	**add_here_to_cmd(char **token, char *input, t_tokh *v)
{
	char	**to_add;
	char	**new;
	char	*d_al;
	char	*delimiter;

	v->k = 0;
	to_add = (char **)ft_calloc(3, sizeof(char *));
	d_al = ft_strdup(ms_tiktok((&input[v->i])).str);
	v->i += ms_tiktok(&input[v->i]).len;
	while (ms_isws(input[v->i]))
		v->i++;
	delimiter = iterate_through_word(input, v);
	// ft_printf("SALOPE = %fs", delimiter);
	to_add[0] = d_al;
	to_add[1] = delimiter;
	new = ms_joinstarstar(token, to_add);
	free_tab(token);
	free_tab(to_add);
	return (new);
}
