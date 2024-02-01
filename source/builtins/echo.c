/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:40:15 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/02/01 14:40:23 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_exitno;

int	flag_echo(char *flag)
{
	int	i;

	i = 0;
	if (ft_strlen(flag) == 0)
		return (0);
	if (flag[0] != '-')
		return (0);
	i++;
	if (!flag)
		return (0);
	while (flag[i])
	{
		if (flag[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	b_echo(t_tok *d_token, int *i)
{
	int	flag;
	int	t;
	int	j;

	j = 1;
	t = 0;
	flag = flag_echo(d_token->tokens[*i][j]);
	j += flag;
	while (d_token->tokens[*i][j])
	{
		if (t == 0)
			if (flag_echo(d_token->tokens[*i][j]) == 0)
				t = 1;
		if (t == 1)
		{
			t = 1;
			printf("%s", d_token->tokens[*i][j]);
			if (d_token->tokens[*i][j + 1])
				printf(" ");
		}
		j++;
	}
	if (flag == 0)
		printf("\n");
	g_exitno = 0;
}
