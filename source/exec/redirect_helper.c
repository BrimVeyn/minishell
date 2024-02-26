/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 10:10:41 by nbardavi          #+#    #+#             */
/*   Updated: 2024/02/26 09:57:48 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_append(char *token, t_pipe *d_pipe)
{
	d_pipe->output = open(token, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (d_pipe->output == -1)
	{
		d_pipe->file_name = ft_sprintf("%fs", token);
		return (D_AR);
	}
	d_pipe->redi = 1;
	dup2(d_pipe->output, STDOUT_FILENO);
	return (0);
}

int	handle_output(char *token, t_pipe *d_pipe)
{
	d_pipe->output = open(token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (d_pipe->output == -1)
	{
		d_pipe->file_name = ft_sprintf("%fs", token);
		return (S_AR);
	}
	d_pipe->redi = 1;
	dup2(d_pipe->output, STDOUT_FILENO);
	close(d_pipe->output);
	return (0);
}

int	handle_input(char *token, t_pipe *d_pipe)
{
	if (access(token, F_OK | R_OK))
	{
		d_pipe->file_name = ft_sprintf("%fs", token);
		return (S_AL);
	}
	if (d_pipe->input != -1)
		close(d_pipe->input);
	d_pipe->redi = 1;
	d_pipe->input = open(token, O_RDONLY);
	return (0);
}

int	handle_heredoc(t_tok *tdata, t_pipe *d_pipe, t_env *denv, int *i)
{
	int	returnvalue;

	d_pipe->h_trigger = 0;
	d_pipe->h_cpt = 0;
	returnvalue = heredoc(d_pipe, tdata, denv, i);
	tdata->tokens[*i] = remove_first(tdata, DELIMITER, *i, 0);
	d_pipe->redi = 1;
	return (returnvalue);
}
