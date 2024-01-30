/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 14:41:28 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/29 16:11:14 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdlib.h>

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

void	b_exit(char **args)
{
	if (ft_strlenlen(args) == 1)
		exit(0);
	else if (ms_is_nbr(args[1]) == 0)
	{
		if (ft_strlenlen(args) > 2)
			fd_printf(2, "minishell: exit: too many arguments");
		else
			exit((unsigned char)ft_atoi(args[1]));
	}
	else
	{
		fd_printf(2, "minishell: exit: %fs: numeric argument required\n",
			args[1]);
		exit(2);
	}
	g_exitno = 1;
}
