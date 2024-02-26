/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 09:35:44 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/02/26 11:22:22 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	b_pwd(t_tok *tdata)
{
	char	current_directory[PATH_MAX];

	if (getcwd(current_directory, sizeof(current_directory)) == NULL)
	{
		tdata->exitno = 1 << 8;
		return ;
	}
	printf("%s\n", current_directory);
	tdata->exitno = 0;
}
