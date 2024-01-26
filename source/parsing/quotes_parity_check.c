/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_parity_check.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:49:14 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/26 10:34:24 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int exitno;

void	quotes_check_helper(int *quotes, int c, int *i, char *str)
{
	*quotes += 1;
	(*i)++;
	while (str[*i] && str[*i] != c)
		(*i)++;
	if (str[*i] && str[*i] == c)
	{
		*quotes += 1;
		(*i)++;
	}
}

int quotes_check_helper2(int *quotes)
{
	if (quotes[0] % 2 != 0)
		fd_printf(2, "minishell: parsing error: unclosed double quotes\n");
	else if (quotes[1] % 2 != 0)
		fd_printf(2, "minishell: parsing error: unclosed single quotes\n");
	else
		return (ZERO);
	exitno = 2;
	return (ERROR);
}

int	quotes_parity_check(char *str)
{
	int	i;
	int	quotes[2];

	i = 0;
	quotes[0] = 0;
	quotes[1] = 0;
	while (str[i])
	{
		if (str[i] == DQUOTE)
			quotes_check_helper(&quotes[0], DQUOTE, &i, str);
		if (str[i] == SQUOTE)
			quotes_check_helper(&quotes[1], SQUOTE, &i, str);
		if (str[i] && str[i] != SQUOTE && str[i] != DQUOTE)
			i++;
	}
	if (quotes_check_helper2(quotes) == ERROR)
		return (ERROR);
	return (ZERO);
}
