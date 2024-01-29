/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 14:41:28 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/29 10:40:17 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdlib.h>

extern int	g_exitno;

int	ms_is_nbr(char *str)
{
	int	i;

	i = 0;
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
			printf("minishell: exit: too many arguments");
		else
			exit((unsigned char)ft_atoi(args[1]));
	}
	else
	{
		printf("minishell: exit: %s: numeric argument required\n", args[1]);
		exit(2);
	}
}
