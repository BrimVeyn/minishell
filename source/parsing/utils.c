/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:51:50 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/02/01 09:29:44 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_exitno;

char	*return_delimiter(t_tok *tdata, t_tokh *v, int *q)
{
	if (q[0] == 0)
		return (ms_strtrimf(tdata->tokens[v->j][0], "\""));
	else if (q[1] == 0)
		return (ms_strtrimf(tdata->tokens[v->j][0], "\'"));
	else
		return (tdata->tokens[v->j][0]);
}

void	extract_delimiter(char *input, t_tok *tdata, t_tokh *v)
{
	int	len;
	int	q[2];

	len = 0;
	q[0] = 0;
	q[1] = 1;
	while (input[v->i] && ms_isws(input[v->i]))
		v->i++;
	while (input[v->i] && ((!ms_isws(input[v->i])
				&& ms_tiktok(&input[v->i]).type == CMD) || (q[0] || q[1])))
	{
		q[0] ^= (input[v->i] == '\"');
		q[1] ^= (input[v->i] == '\'');
		len++;
		v->i++;
	}
	tdata->tokens[v->j] = (char **)ft_calloc(2, sizeof(char *));
	tdata->tokens[v->j][0] = ft_substr(input, v->i - len, len);
	tdata->tokens[v->j][0] = return_delimiter(tdata, v, q);
	tdata->type[v->j] = DELIMITER;
	v->j++;
}

char	*grep_word(char *input, t_tokh *v)
{
	int	len;
	int	q[2];

	q[0] = 0;
	q[1] = 0;
	len = 0;
	while (input[v->i] && ms_isws(input[v->i]))
		v->i++;
	while (input[v->i] && ((!ms_isws(input[v->i])
				&& ms_tiktok(&input[v->i]).type == CMD) || (q[0] || q[1])))
	{
		q[0] ^= (input[v->i] == '\"');
		q[1] ^= (input[v->i] == '\'');
		len++;
		v->i++;
	}
	if (q[0] == 0)
		return (ms_strtrimf(ft_substr(input, v->i - len, len), "\""));
	else if (q[1] == 0)
		return (ms_strtrimf(ft_substr(input, v->i - len, len), "\'"));
	else
		return (ft_substr(input, v->i - len, len));
}

int	ms_wl2(char *ptr)
{
	if (!ft_strncmp(ptr, ">>", 2) || !ft_strncmp(ptr, ">", 1)
		|| (!ft_strncmp(ptr, "<", 1) && ft_strncmp(ptr, "<<", 2)))
		return (1);
	return (0);
}

int	f_lcmd_index(t_tok *tdata, int j)
{
	j--;
	while (tdata->type[j] != CMD)
		j--;
	return (j);
}
