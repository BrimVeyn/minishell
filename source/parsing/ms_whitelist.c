/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_whitelist.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 08:55:01 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/02/08 08:55:58 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ms_typecmdtok(int type)
{
	if (type == D_AL || type == S_AL || type == D_AR || type == S_AR)
		return (TRUE);
	return (ERROR);
}

int	ms_typetok(int type)
{
	if (type == P_O || type == P_C || type == PIPE || type == AND || type == OR)
		return (TRUE);
	return (ERROR);
}

int	ms_wlcmd(char *input)
{
	if (ms_tiktok(input).type == CMD || ms_tiktok(input).type == D_AL
		|| ms_tiktok(input).type == S_AL || ms_tiktok(input).type == D_AR
		|| ms_tiktok(input).type == S_AR)
		return (TRUE);
	return (ERROR);
}

int	ms_wlcmdtok(char *input)
{
	if (ms_tiktok(input).type == D_AL || ms_tiktok(input).type == S_AL
		|| ms_tiktok(input).type == D_AR || ms_tiktok(input).type == S_AR)
		return (TRUE);
	return (ERROR);
}

int	ms_wltoken(char *input)
{
	if (ms_tiktok(input).type == P_O || ms_tiktok(input).type == P_C
		|| ms_tiktok(input).type == PIPE || ms_tiktok(input).type == AND
		|| ms_tiktok(input).type == OR)
		return (TRUE);
	return (ERROR);
}
