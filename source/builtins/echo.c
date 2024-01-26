/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 14:57:36 by nbardavi          #+#    #+#             */
/*   Updated: 2024/01/25 15:43:42 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int flag_echo(char *flag)
{
	int i;

	i = 0;
	if (flag[0] != '-')
		return (0);
	i++;
	while(flag[0])
	{
		if (flag[0] != 'n')
			return(0);
	}
	return (1);
}

void b_echo(t_tok *d_token, int *i)
{
	int flag;
	int t;
	int j;

	j = 1;
	t = 0;
	flag = flag_echo(d_token->tokens[*i][0]);
	j += flag;
	while(d_token->tokens[*i][j])
	{
		if (t == 0)
		{
			if (flag_echo(d_token->tokens[*i][j]) == 0)
				t = 1;
		}
		if (t == 1)
		{
			t = 1;
			printf("%s ", d_token->tokens[*i][j]);
		}
		j++;
	}
	if (flag == 0)
		printf("\n");
	exit(EXIT_SUCCESS);
}
