/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:13:39 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/26 14:21:19 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"
#include <stdlib.h>

extern int g_exitno;

int ms_is_nbr(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return(1);
		i++;
	}
	return(0);
}

void b_exit(t_pipe *d_pipe, char **args)
{
	if (ft_strlenlen(args) == 1)
	{
		g_exitno = 0;
		fd_printf(d_pipe->b_pipefd[1], "1");
	}
	else if (ms_is_nbr(args[1]) == 0)
	{
		if (ft_strlenlen(args) > 2)
		{
			printf("minishell: exit: too many arguments");
			fd_printf(d_pipe->b_pipefd[1], "1");
		}
		else
		{
			d_pipe->t_exit = 1;
			g_exitno = (unsigned char)ft_atoi(args[1]);
		}
	}
	else
	{
		printf("minishell: exit: %s: numeric argument required\n", args[1]);
		g_exitno = 2;
		fd_printf(d_pipe->b_pipefd[1], "1");
	}
	exit(g_exitno);
}
