/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 11:22:14 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/02/07 14:17:38 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_exitno;

int	ms_is_nbr(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	if (str[i] == '+' && i == 0)
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

void	b_exit(char **args, t_pipe *d_pipe)
{
	if (ft_strlenlen(args) == 1)
	{
		d_pipe->t_exit = 1;
		g_exitno = 0;
	}
	else if (ms_is_nbr(args[1]) == 0)
	{
		if (ft_strlenlen(args) > 2)
		{
			fd_printf(2, "minishell: exit: too many arguments\n");
			g_exitno = 1;
		}
		else
		{
			d_pipe->t_exit = 1;
			g_exitno = ((unsigned char)ft_atoi(args[1]));
		}
	}
	else if (ms_is_nbr(args[1]) != 0)
	{
		fd_printf(2, "minishell: exit: %fs: numeric argument required\n",
			args[1]);
		d_pipe->t_exit = 1;
		g_exitno = 2;
	}
}
