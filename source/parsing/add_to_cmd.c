/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 14:17:10 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/02/01 13:20:24 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_exitno;

char	**add_args_to_cmd(char *input, t_tokh *v, t_tok *tdata, t_env *denv)
{
	char	**to_add;
	char	**new;
	char	*fdp;

	v->k = 0;
	while (input[v->i] && ms_tiktok(&input[v->i]).type == CMD)
	{
		v->k++;
		v->i++;
	}
	fdp = ft_substr(input, v->i - v->k, v->k);
	to_add = ft_splitm(fdp, denv);
	new = ms_joinstarstar(tdata->tokens[v->l], to_add);
	free_tab(tdata->tokens[v->l]);
	free_tab(to_add);
	return (free(fdp), new);
}

char	*ms_trim(char *input, char c)
{
	int		i;
	int		j;
	int		ct;
	char	*new;

	i = 0;
	ct = 0;
	while (input[i])
	{
		if (input[i] != c)
			ct++;
		i++;
	}
	new = (char *)ft_calloc(ct + 1, sizeof(char));
	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] != c)
			new[j++] = input[i];
		i++;
	}
	return (free(input), new);
}

char	*iterate_through_word(char *input, t_tokh *v)
{
	int	q[2];

	q[0] = 0;
	q[1] = 0;
	v->k = 0;
	while (input[v->i] && ((!ms_isws(input[v->i])
				&& ms_tiktok(&input[v->i]).type == CMD) || (q[0] == 1
				|| q[1] == 1)))
	{
		q[0] ^= (input[v->i] == '\"');
		q[1] ^= (input[v->i] == '\'');
		v->k++;
		v->i++;
	}
	if (q[0] == 0)
		return (ms_trim(ft_substr(input, v->i - v->k, v->k), '\"'));
	else if (q[1] == 0)
		return (ms_trim(ft_substr(input, v->i - v->k, v->k), '\''));
	else
		return (ft_substr(input, v->i - v->k, v->k));
}

char	**empty_token(char **token, char **to_add)
{
	free_tab(token);
	to_add[0] = ft_strdup("WRONG");
	to_add[1] = ft_strdup("WRONG");
	return (to_add);
}

// char	**add_here_to_cmd(t_tok *tdata, char **token, char *input, t_tokh *v)
// {
// 	char	**to_add;
// 	char	**new;
// 	char	*d_al;
// 	char	*delimiter;
//
// 	to_add = (char **)ft_calloc(3, sizeof(char *));
// 	d_al = ft_strdup(ms_tiktok((&input[v->i])).str);
// 	v->i += ms_tiktok(&input[v->i]).len;
// 	while (ms_isws(input[v->i]))
// 		v->i++;
// 	delimiter = iterate_through_word(input, v);
// 	if (!ft_strncmp("", delimiter, 2))
// 	{
// 		tdata->type[v->l] = WRONG;
// 	}
// 	if (!ft_strcmp("*", delimiter))
// 	{
// 		g_exitno = 1;
// 		fd_printf(2, "minishell: '*': ambiguous redirect\n");
// 		tdata->type[v->l] = WRONG;
// 	}
// 	to_add[0] = d_al;
// 	to_add[1] = delimiter;
// 	new = ms_joinstarstar(token, to_add);
// 	return (free_tab(token), free_tab(to_add), new);
// }
