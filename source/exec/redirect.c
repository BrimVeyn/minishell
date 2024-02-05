/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 10:35:07 by nbardavi          #+#    #+#             */
/*   Updated: 2024/02/05 14:44:18 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_exitno;

char	**remove_first(char **string, int *type, int skip_type);

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
	int returnvalue;

	d_pipe->h_trigger = 0;
	d_pipe->h_cpt = 0;
	returnvalue = heredoc(d_pipe, d_token, denv, i);
	d_token->tokens[*i] = remove_first(d_token->tokens[*i], d_token->type[*i], DELIMITER);
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

int		count_cmd(char **string, int *type)
{
	int i;
	int  len;

	i = 0;
	len = 0;
	while(string[i])
	{
		if (type[i] == CMD || type[i] == BUILTIN)
			len++;
		i++;
	}
	return(len);
}

char	**remove_first(char **string, int *type, int skip_type)
{
	int i;
	char	**new;

	i = 0;
	//pas de +1 car on enleve une case
	new = ft_calloc(ft_strlenlen(string), sizeof(char *)); 
	while(string[i] && type[i] != skip_type)
	{
		if (type[i] != skip_type)
			new[i] = ft_strdup(string[i]);
	}
	i++;
	while(string[i])
	{
		new[i] = ft_strdup(string[i]);
		i++;
	}
	free_tab(string);
	return (new);
}

int	cmd_redi(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i)
{
	int		j;

	j = 0;
	d_pipe->failure = 0;
	while (d_token->tokens[*i][j])
	{
		if (d_token->type[*i][j] == D_AR)
			d_pipe->failure = handle_append(d_token->tokens[*i][j], d_pipe);
		else if (d_token->type[*i][j] == S_AR)
			d_pipe->failure = handle_output(d_token->tokens[*i][j], d_pipe);
		else if (d_token->type[*i][j] == S_AL)
			d_pipe->failure = handle_input(d_token->tokens[*i][j], d_pipe);
		else if (d_token->type[*i][j] == D_AL)
			d_pipe->failure = handle_heredoc(d_token, d_pipe, denv, i);
		if (d_pipe->failure)
			break ;
		if (d_token->type[*i][j] != CMD && d_token->type[*i][j] != BUILTIN && d_token->type[*i][j] != WRONG)
			d_token->tokens[*i] = remove_first(d_token->tokens[*i], d_token->type[*i], d_token->type[*i][j]);
		if (d_token->type[*i][j] == D_AR || d_token->type[*i][j] == S_AR || d_token->type[*i][j] == S_AL)
			d_token->tokens[*i] = remove_first(d_token->tokens[*i], d_token->type[*i], FAILE);
		j++;
	}
	return (cmd_return(d_pipe));
}
