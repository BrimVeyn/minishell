/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   robin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 12:38:43 by nbardavi          #+#    #+#             */
/*   Updated: 2024/01/30 17:34:16 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_exitno;

void	b_robin(void)
{
	int		id;
	char	**cmd;

	cmd = ft_calloc(3, sizeof(char *));
	cmd[0] = ft_strdup("/usr/bin/cat");
	cmd[1] = ft_strdup("/home/nbardavi/Desktop/minishell/source/builtins/rrettien.ansi.txt");
	id = fork();
	if (id == 0)
	{
		execve(cmd[0], cmd, NULL);
		perror("");
		exit(EXIT_FAILURE);
	}
	waitpid(id, &g_exitno, 0);
	printf("\033[31m>>>>>>>>>> FAILURE <<<<<<<<<<\033[0m\n");
	g_exitno = 0;
	free_tab(cmd);
}
