/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 15:06:31 by nbardavi          #+#    #+#             */
/*   Updated: 2023/12/26 15:17:57 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_pipe(t_data *data, char *env[])
{
	if (pipe(data->pipefd) == -1)
		exit(EXIT_FAILURE);
	data->pid[data->cptfork] = fork();
	if (data->pid[data->cptfork] != 0)
	{
		close(data->pipefd[1]);
		dup2(data->pipefd[0], STDIN_FILENO);
		close(data->pipefd[0]);
	}
	if (data->pid[data->cptfork] == 0)
	{
		close(data->pipefd[0]);
		close(data->input);
		if (data->cptfork != data->maxcmd - 1)
			dup2(data->pipefd[1], STDOUT_FILENO);
		else
			dup2(data->output, STDOUT_FILENO);
		close(data->pipefd[1]);
		close(data->output);
		execve(data->cmds[data->cptfork][0], data->cmds[data->cptfork], env);
		exit(EXIT_FAILURE);
	}
}

void ms_while_pipe(t_args **args)
{
	int i;

	i = 0;
	while (args[i])
}
