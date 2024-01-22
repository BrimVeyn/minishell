/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_dlstmatchs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 11:57:39 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/19 10:26:01 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void ms_del_hidden(t_dlist *el, char *to_match)
{
	(void) to_match;
	if (el->str[0] == '.')
		el->i = ERROR;
}

void	ms_matchstart(t_dlist *el, char *to_match)
{
	int	tm_len;

	tm_len = ft_strlen(to_match);
	if (!ft_strncmp(el->str, to_match, tm_len))
		el->i = tm_len;
	else
		el->i = ERROR;
}

void  ms_matchmid(t_dlist *el, char *to_match)
{
	int tm_len;
	int	str_len;
	int	valid;

	tm_len = ft_strlen(to_match);
	str_len = ft_strlen(el->str);
	valid = 0;
	while (el->str[el->i] && el->i <= str_len - tm_len)
	{
		if (!ft_strncmp(&el->str[el->i], to_match, tm_len))
        {
			el->i += tm_len;
			valid = 1;
			break;
        }
		el->i++;
	}
	if (valid == 0) 
		el->i = ERROR;
}

void ms_matchend(t_dlist *el, char *to_match)
{
	int	tm_len;
	int	str_len;

	tm_len = ft_strlen(to_match);
	str_len = ft_strlen(el->str);
	if (tm_len > str_len)
		el->i = ERROR;
	else if (!ft_strncmp(&el->str[str_len - tm_len], to_match, tm_len))
		el->i = str_len;
	else
		el->i = ERROR;
}

