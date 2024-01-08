/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 15:06:31 by nbardavi          #+#    #+#             */
/*   Updated: 2023/12/28 14:12:15 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void exec_pipe()
{

}

void set_output()
{
}

char *ms_getlast(t_env *denv)
{
	t_h_lst *lst;

	lst = denv->history;
	while(lst->next != NULL)
		lst = lst->next;
	return (lst->content);
}

void reset_history(t_env *denv)
{
	t_h_lst *lst;

	lst = denv->history;
	rl_clear_history();
	while(lst->next != NULL)
	{
		add_history(lst->content);
		lst = lst->next;
	}
}

void heredoc(t_pipe *d_pipe, char *limiter, t_env *denv)
{
	char	*input;
	char	*save;

	d_pipe->input = open(ft_sprintf("%fs%d", ".temp_heredoc", d_pipe->nbr_h++), O_WRONLY | O_CREAT);
	save = ft_strdup("");
	while(1)
	{
		input = readline(">");
		if (ft_strcmp(limiter, input) == 0)
			break;
		save = ft_sprintf("%s%s\n", save, input);
	}
	save = ft_sprintf("%fs\n%s%fs", ms_getlast(denv), save, limiter);
	ms_lst_b(&denv->history, ms_lst_new(save));
	reset_history(denv);
	// write(d_pipe->input, save, ft_strlen(save));
	fd_printf(d_pipe->input, "%s",save);
	fd_printf(STDIN_FILENO, "%s", save);
	add_history(save);
}

