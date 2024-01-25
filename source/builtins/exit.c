/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:13:39 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/25 13:39:39 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

extern int exitno;

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
		exitno = 0;
		d_pipe->t_exit = 1;
	}
	else if (ms_is_nbr(args[1]) == 0)
	{
		if (ft_strlenlen(args) > 2)
		{
			printf("minishell: exit: too many arguments");
			exitno = 1;
		}
		else
		{
			d_pipe->t_exit = 1;
			exitno = (unsigned char)ft_atoi(args[1]);
		}
	}
	else
	{
		printf("minishell: exit: %s: numeric argument required\n", args[1]);
		exitno = 2;
		d_pipe->t_exit = 1;
	}
	exit(exitno);
	
}
