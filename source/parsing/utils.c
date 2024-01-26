/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:51:50 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/26 09:28:58 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	extract_delimiter(char *input, t_tok *tdata, t_tokh *v)
{
	int		len;
	char	*tmp;

	len = 0;
	while (input[v->i] && ms_isws(input[v->i]))
		v->i++;
	while (input[v->i] && !ms_isws(input[v->i])
		&& ms_tiktok(&input[v->i]).type == CMD)
	{
		len++;
		v->i++;
	}
	tdata->tokens[v->j] = (char **)ft_calloc(2, sizeof(char *));
	tdata->tokens[v->j][0] = ft_substr(input, v->i - len, len);
	tmp = ms_strtrimf(tdata->tokens[v->j][0], "'");
	tmp = ms_strtrimf(tmp, "\"");
	tdata->tokens[v->j][0] = tmp;
	tdata->type[v->j] = DELIMITER;
	v->j++;
}

char	*grep_word(char *input, t_tokh *v)
{
	int	len;

	len = 0;
	while (input[v->i] && ms_isws(input[v->i]))
		v->i++;
	while (input[v->i] && !ms_isws(input[v->i])
		&& ms_tiktok(&input[v->i]).type == CMD)
	{
		len++;
		v->i++;
	}
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
