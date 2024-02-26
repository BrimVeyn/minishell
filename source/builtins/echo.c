/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:40:15 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/02/26 12:56:57 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"



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

void	b_echo(t_tok *tdata, int *i)
{
	int	flag;
	int	t;
	int	j;

	j = 1;
	t = 0;
	flag = flag_echo(tdata->tokens[*i][j]);
	j += flag;
	while (tdata->tokens[*i][j])
	{
		if (t == 0)
			if (flag_echo(tdata->tokens[*i][j]) == 0)
				t = 1;
		if (t == 1)
		{
			t = 1;
			printf("%s", tdata->tokens[*i][j]);
			if (tdata->tokens[*i][j + 1])
				printf(" ");
		}
		j++;
	}
	if (flag == 0)
		printf("\n");
	tdata->exitno = 0;
}
