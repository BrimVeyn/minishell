/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 11:08:22 by nbardavi          #+#    #+#             */
/*   Updated: 2024/01/26 14:25:01 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ms_free_history(t_h_lst **head)
{
	t_h_lst	*tmp;

	while (*head)
	{
		tmp = (*head)->next;
		free((*head)->content);
		free(*head);
		*head = tmp;
	}
}

void	ms_free_env(t_env *denv)
{
	free_tab(denv->f_env);
	free(denv->usr);
	free(denv->path);
	free(denv->pwd);
	if (denv->history)
		ms_free_history(&denv->history);
}

void	ms_free_pipe(t_pipe *d_pipe)
{
	free(d_pipe->fork_id);
	free(d_pipe->f_id);
	free(d_pipe->p_return);
	close(d_pipe->old_stdout);
	close(d_pipe->old_stdin);
}

void	free_tpe(t_tok *dt, t_pipe *dp, t_env *de)
{
	free_tdata(dt);
	ms_free_pipe(dp);
	ms_free_env(de);
}
