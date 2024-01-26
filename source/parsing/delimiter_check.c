/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiter_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 14:15:17 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/25 14:18:33 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	delimiter_check(char *input)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (ms_isws(input[i]))
		i++;
	while (input[i] && !ms_isws(input[i]) && ms_tiktok(&input[i]).type == CMD)
	{
		len++;
		i++;
	}
	if (len == 0 && !input[i])
		fd_printf(2,
			"minishell: syntax error near unexpected token `newline'\n");
	else if (len == 0 && input[i] && ms_tiktok(&input[i]).type != CMD)
		fd_printf(2, "minishell: syntax error near unexpected token `%fs'\n",
			ms_tiktok(&input[i]).str);
	return (len);
}
