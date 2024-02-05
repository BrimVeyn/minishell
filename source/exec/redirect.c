/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 10:35:07 by nbardavi          #+#    #+#             */
/*   Updated: 2024/02/05 13:36:24 by nbardavi         ###   ########.fr       */
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

static int	handle_heredoc(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i)
{

	d_pipe->h_trigger = 0;
	d_pipe->h_cpt = 0;
	return (heredoc(d_pipe, d_token, denv, i));
}

int	cmd_return(t_pipe *d_pipe)
{
	if (d_pipe->failure)
		return (r_parse_error(d_pipe), 1);
	if (d_pipe->input != -1)
		dup2(d_pipe->input, STDIN_FILENO);
	return (0);
}

char	**remove_redi(char **string, int *type)
{
	int i;
	char	**new;
	int		len;

	len = 0;
	i = 0;
	while(string[i])
	{
		if (type[i] == CMD || type[i] == BUILTIN)
			len++;
		i++;
	}
	new = ft_calloc(len + 1, sizeof(char *));
	i = 0;
	while(string[i])
	{
		if (type[i] == CMD || type[i] == BUILTIN)
			new[i] = ft_strdup(string[i]);
		i++;
	}
	free_tab(string);
	return (new);
}

int	cmd_redi(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i)
{
	int		k;
	int		j;

	k = 0;
	j = 0;
	d_pipe->failure = 0;
	j += (d_token->type[*i + 1][0] == P_C);
	while (d_token->tokens[*i][j])
	{
		if (d_token->type[*i][k] == D_AR)
			d_pipe->failure = handle_append(d_token->tokens[*i][j], d_pipe);
		else if (d_token->type[*i][k] == S_AR)
			d_pipe->failure = handle_output(d_token->tokens[*i][j], d_pipe);
		else if (d_token->type[*i][k] == S_AL)
			d_pipe->failure = handle_input(d_token->tokens[*i][j], d_pipe);
		else if (d_token->type[*i][k] == D_AL)
		{
			d_pipe->failure = handle_heredoc(d_token, d_pipe, denv,i);
		}
		if (d_pipe->failure)
			break ;
		j++;
	}
	d_token->tokens[*i] = remove_redi(d_token->tokens[*i], d_token->type[*i]);
	return (cmd_return(d_pipe));
}
