/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:33:04 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/26 14:29:32 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_exitno;

int	ms_wl(char *ptr)
{
	if (!ft_strncmp(ptr, "||", 2) || !ft_strncmp(ptr, "&&", 2)
		|| !ft_strncmp(ptr, "|", 1))
		return (1);
	return (0);
}

int	start_check_helper(char *input, int i)
{
	if (input[i + 1] 
		&& ms_tiktok(&input[i + ms_tiktok(&input[i]).len]).type != CMD)
	{
		fd_printf(2, "minishell: syntax error near unexpected token `%fs'\n",
			ms_tiktok(&input[i + ms_tiktok(&input[i]).len]).str);
	}
	else
	{
		fd_printf(2,
			"minishell: syntax error near unexpected token `newline'\n");
	}
	g_exitno = 2;
	return (ERROR);
}

int	start_check(char *input, t_tokvar tokvar, int i)
{
	int	icpy;

	icpy = i;
	if (tokvar.type == P_O || tokvar.type == P_C || tokvar.type == S_AL
		|| tokvar.type == D_AL)
		return (TRUE);
	if (icpy != 0)
	{
		icpy -= ms_tiktok(&input[i]).len;
	}
	while (icpy != 0 && input[icpy] && ms_isws(input[icpy]))
		icpy--;
	if (icpy == 0 && ms_wl(ms_tiktok(&input[i]).str))
	{
		fd_printf(2, "minishell: syntax error near unexpected token `%fs'\n",
			ms_tiktok(&input[i]).str);
		g_exitno = 2;
		return (ERROR);
	}
	else if (icpy == 0)
		if (start_check_helper(input, i) == ERROR)
			return (ERROR);
	return (TRUE);
}
