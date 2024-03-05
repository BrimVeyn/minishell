/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:20:02 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/03/05 13:48:21 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <limits.h>

static long	ms_latoi(const char *theString)
{
	int		i;
	int		sign;
	long	result;

	result = 0;
	sign = 1;
	i = 0;
	while ((theString[i] >= 9 && theString[i] <= 13) || theString[i] == 32)
		i++;
	if (theString[i] == '+' && theString[i + 1] != '-')
		i++;
	if (theString[i] == '-')
	{
		i++;
		sign = -1;
	}
	while (theString[i] && theString[i] >= '0' && theString[i] <= '9')
	{
		result *= 10;
		result += theString[i] - '0';
		i++;
	}
	return (result * sign);
}

static int	ms_is_nbr(char *str)
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

static void	set_exitno(char **args, t_pipe *d_pipe, t_tok *tdata)
{
	char	*to_cmp;
	long	no;

	no = ms_latoi(args[1]);
	to_cmp = ft_litoa(no);
	if (args[1][0] == '+')
		args[1] = ft_substr_free(args[1], 1, ft_strlen(args[1]) - 1);
	d_pipe->t_exit = 1;
	if (ft_strcmp(args[1], to_cmp))
	{
		tdata->exitno = 2 << 8;
		fd_printf(2, "minishell: exit: %fs: numeric argument required\n",
			args[1]);
	}
	else
		tdata->exitno = ((unsigned char)no) << 8;
	free(to_cmp);
}

void	b_exit(char **args, t_pipe *d_pipe, t_tok *tdata)
{
	if (ft_strlenlen(args) == 1)
	{
		d_pipe->t_exit = 1;
		tdata->exitno = 0;
	}
	else if (ms_is_nbr(args[1]) == 0)
	{
		if (ft_strlenlen(args) > 2)
		{
			fd_printf(2, "minishell: exit: too many arguments\n");
			tdata->exitno = 1 << 8;
		}
		else
			set_exitno(args, d_pipe, tdata);
	}
	else if (ms_is_nbr(args[1]) != 0)
	{
		fd_printf(2, "minishell: exit: %fs: numeric argument required\n",
			args[1]);
		d_pipe->t_exit = 1;
		tdata->exitno = 2 << 8;
	}
}
