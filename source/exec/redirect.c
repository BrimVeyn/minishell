/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 10:35:07 by nbardavi          #+#    #+#             */
/*   Updated: 2024/02/01 11:31:05 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_exitno;

static int	handle_append(char *token, t_pipe *d_pipe)
{
	d_pipe->output = open(token, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (d_pipe->output == -1)
	{
		d_pipe->file_name = ft_sprintf("%s", token);
		return (D_AR);
	}
	dup2(d_pipe->output, STDOUT_FILENO);
	return (0);
}

static int	handle_output(char *token, t_pipe *d_pipe)
{
	d_pipe->output = open(token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (d_pipe->output == -1)
	{
		d_pipe->file_name = ft_sprintf("%s", token);
		return (S_AR);
	}
	dup2(d_pipe->output, STDOUT_FILENO);
	close(d_pipe->output);
	return (0);
}

static int	handle_input(char *token, t_pipe *d_pipe)
{
	if (access(token, F_OK | R_OK))
	{
		d_pipe->file_name = ft_sprintf("%s", token);
		return (S_AL);
	}
	if (d_pipe->input != -1)
		close(d_pipe->input);
	d_pipe->redi = 1;
	d_pipe->input = open(token, O_RDONLY);
	return (0);
}

int	cmd_return(t_pipe *d_pipe)
{
	if (d_pipe->failure)
		return (r_parse_error(d_pipe), 1);
	if (d_pipe->input != -1)
		dup2(d_pipe->input, STDIN_FILENO);
	return (0);
}

int	cmd_redi(t_tok *d_token, t_pipe *d_pipe, int *i, int j)
{
	int		k;
	char	**new;

	k = 0;
	d_pipe->failure = 0;
	new = ft_calloc(ft_strlenlen(d_token->tokens[*i]) + 1, sizeof(char *));
	j += (d_token->type[*i + 1] == P_C);
	while (d_token->tokens[*i][j])
	{
		if (!ft_strcmp(d_token->tokens[*i][j], ">>"))
			d_pipe->failure = handle_append(d_token->tokens[*i][++j], d_pipe);
		else if (!ft_strcmp(d_token->tokens[*i][j], ">"))
			d_pipe->failure = handle_output(d_token->tokens[*i][++j], d_pipe);
		else if (!ft_strcmp(d_token->tokens[*i][j], "<"))
			d_pipe->failure = handle_input(d_token->tokens[*i][++j], d_pipe);
		else
			new[k++] = ft_strdup(d_token->tokens[*i][j]);
		if (d_pipe->failure)
			break ;
		j++;
	}
	free(d_token->tokens[*i]);
	d_token->tokens[*i] = new;
	return (cmd_return(d_pipe));
}
