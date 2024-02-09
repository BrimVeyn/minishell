/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 09:30:42 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/02/09 09:30:58 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <unistd.h>

extern int	g_exitno;

char	**remove_first(t_tok *dt, int skip_type, int c);
int	handle_append(char *token, t_pipe *d_pipe);
int	handle_output(char *token, t_pipe *d_pipe);
int	handle_heredoc(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i);
int	cmd_return(t_pipe *d_pipe);
int	count_cmd(char **string, int *type);
int	check_next(int signe);
int	handle_input(char *token, t_pipe *d_pipe);

int	handle_append(char *token, t_pipe *d_pipe)
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

int	handle_output(char *token, t_pipe *d_pipe)
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

int	handle_input(char *token, t_pipe *d_pipe)
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

int	handle_heredoc(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i)
{
	int	returnvalue;

	d_pipe->h_trigger = 0;
	d_pipe->h_cpt = 0;
	returnvalue = heredoc(d_pipe, d_token, denv, i);
	d_token->tokens[*i] = remove_first(d_token, DELIMITER, *i);
	return (returnvalue);
}

int	cmd_return(t_pipe *d_pipe)
{
	// char *buffer;
	// buffer = ft_calloc(1000, 1);
	if (d_pipe->failure)
		return (r_parse_error(d_pipe), 1);
	if (d_pipe->input != -1)
	{
		dup2(d_pipe->input, STDIN_FILENO);
		close(d_pipe->input);
	}
	return (0);
}

int	count_cmd(char **string, int *type)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (string[i])
	{
		if (type[i] == CMD || type[i] == BUILTIN)
			len++;
		i++;
	}
	return (len);
}

char	**remove_first(t_tok *dt, int skip_type, int c)
{
	int		i;
	int		j;
	int		skipped;
	char	**new;
	int		*new_type;

	j = 0;
	skipped = 0;
	i = 0;
	new_type = ft_calloc(ft_strlenlen(dt->tokens[c]), sizeof(int));
	new = ft_calloc(ft_strlenlen(dt->tokens[c]), sizeof(char *));
	while (dt->tokens[c][i])
	{
		if (dt->type[c][i] != skip_type || skipped)
		{
			new[j] = ft_strdup(dt->tokens[c][i]);
			new_type[j] = dt->type[c][i];
			j++;
		}
		else
			skipped = 1;
		i++;
	}
	free_tab(dt->tokens[c]);
	free(dt->type[c]);
	dt->tokens[c] = new;
	dt->type[c] = new_type;
	return (new);
}

void	tprint(char ***string)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (string[i])
	{
		while (string[i][j])
		{
			fd_printf(2, "tokens[%d][%d] : %fs\n", i, j, string[i][j]);
			j++;
		}
		fd_printf(2, "\n");
		j = 0;
		i++;
	}
}

int	check_next(int signe)
{
	if (signe == S_AR || signe == D_AR || signe == S_AL || signe == D_AL)
		return (1);
	return (0);
}

