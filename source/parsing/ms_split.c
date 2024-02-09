/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:07:37 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/02/09 09:50:55 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ms_grep_word(char *input, int *j, int *q, int *counter)
{
	int	trigger;

	trigger = 0;
	while (input[(*j)] && ms_isws(input[*j]))
		(*j)++;
	while (input[(*j)] && ((!ms_isws(input[*j])
				&& ms_wlcmdtok(&input[*j]) == ERROR
				&& ms_wltoken(&input[(*j)]) == ERROR) || (q[0] || q[1])))
	{
		q[0] ^= (input[*j] == '\"');
		while (input[*j] && q[0])
		{
			(*j)++;
			q[0] ^= (input[*j] == '\"');
		}
		q[1] ^= (input[*j] == '\'');
		while (input[*j] && q[1])
		{
			(*j)++;
			q[1] ^= (input[*j] == '\'');
		}
		trigger = 1;
		(*j)++;
	}
	*counter += (trigger == 1);
}

int	ms_count_word(char *input, int *j)
{
	int	counter;
	int	q[2];
	int	trigger;

	counter = 0;
	trigger = 0;
	q[0] = 0;
	q[1] = 0;
	while (input[*j] && ms_wltoken(&input[*j]) == ERROR)
	{
		ms_grep_word(input, j, q, &counter);
		if (input[*j] && ms_wlcmdtok(&input[(*j)]) == TRUE)
		{
			(*j) += ms_tiktok(&input[*j]).len;
			counter += 1;
		}
		else if (input[(*j)] && ms_wltoken(&input[*j]) == ERROR)
			(*j)++;
	}
	return (counter);
}

void	ms_fill_word(char *input, int *j, int *q, int *len)
{
	while (input[(*j)] && ((!ms_isws(input[*j])
				&& ms_wlcmdtok(&input[*j]) == ERROR
				&& ms_wltoken(&input[(*j)]) == ERROR) || (q[0] || q[1])))
	{
		q[0] ^= (input[*j] == '\"');
		while (input[*j] && q[0])
		{
			(*j)++;
			(*len)++;
			q[0] ^= (input[*j] == '\"');
		}
		q[1] ^= (input[*j] == '\'');
		while (input[*j] && q[1])
		{
			(*j)++;
			(*len)++;
			q[1] ^= (input[*j] == '\'');
		}
		(*len)++;
		(*j)++;
	}
}

void	ms_type_set(char *input, int *x, int *type, char **split)
{
	if (x[1] > 0)
	{
		split[x[0]] = ft_substr(input, x[2], x[1]);
		if (!type[x[0]])
			type[x[0]] = CMD;
		x[0]++;
	}
	if (input[x[3]] && ms_wlcmdtok(&input[(x[3])]) == TRUE)
	{
		split[x[0]] = ft_strdup(ms_tiktok(&input[x[3]]).str);
		type[x[0]] = ms_tiktok(&input[x[3]]).type;
		if (ms_tiktok(&input[x[3]]).type == S_AL
			|| ms_tiktok(&input[x[3]]).type == S_AR
			|| ms_tiktok(&input[x[3]]).type == D_AR)
			type[x[0] + 1] = FAILE;
		else
			type[x[0] + 1] = DELIMITER;
		x[0]++;
		(x[3]) += ms_tiktok(&input[x[3]]).len;
	}
	else if (input[(x[3])] && ms_wltoken(&input[x[3]]) == ERROR)
		(x[3])++;
}

char	***ms_split(t_tok *tdata, char *input)
{
	t_splith	s;

	s.i = 0;
	s.j = 0;
	s.wc = 0;
	s.split = (char ***)ft_calloc(tdata->t_size + 1, sizeof(char **));
	tdata->type = (int **)ft_calloc(tdata->t_size + 1, sizeof(int *));
	while (s.i < tdata->t_size)
	{
		s.j_save = s.j;
		s.wc = ms_count_word(input, &s.j);
		s.d_value = (!s.wc);
		if (!s.wc)
			s.j += ms_tiktok(&input[s.j]).len;
		s.split[s.i] = (char **)ft_calloc(s.wc + s.d_value + 1, sizeof(char *));
		tdata->type[s.i] = (int *)ft_calloc(s.wc + s.d_value + 1, sizeof(int));
		if (s.wc)
			ms_fill_cmd(s.split[s.i], input, &s.j_save, tdata->type[s.i]);
		else
			ms_fill_token(s.split[s.i], input, &s.j_save, tdata->type[s.i]);
		while (ms_isws(input[s.j]))
			s.j++;
		s.i++;
	}
	return (s.split);
}
