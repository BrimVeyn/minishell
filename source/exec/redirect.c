/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 10:35:07 by nbardavi          #+#    #+#             */
/*   Updated: 2024/02/08 11:49:00 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <unistd.h>

extern int	g_exitno;

char		**remove_first(t_tok *dt, int skip_type, int c);
void		tprint(char ***string);

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

int	cmd_redi(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i)
{
	int	j;
	int	temp;

	j = 0;
	d_pipe->failure = 0;
	d_pipe->tr_p = 0;
	while (d_token->tokens[*i][j])
	{
		temp = d_token->type[*i][j];
		if (d_token->type[*i][j] == D_AR)
			d_pipe->failure = handle_append(d_token->tokens[*i][j + 1], d_pipe);
		else if (d_token->type[*i][j] == S_AR)
			d_pipe->failure = handle_output(d_token->tokens[*i][j + 1], d_pipe);
		else if (d_token->type[*i][j] == S_AL)
			d_pipe->failure = handle_input(d_token->tokens[*i][j + 1], d_pipe);
		else if (d_token->type[*i][j] == D_AL)
			d_pipe->failure = handle_heredoc(d_token, d_pipe, denv, i);
		if (d_token->t_size > *i + 2 && (d_token->type[*i + 1][0] == P_C
				&& check_next(d_token->type[*i + 2][0]) == 1)
			&& d_pipe->tr_p == 0)
		{
			d_pipe->tr_p = 1;
			*i += 2;
			d_pipe->failure = cmd_redi(d_token, d_pipe, denv, i);
			*i -= 2;
		}
		if ((d_token->type[*i][j] != CMD && d_token->type[*i][j] != BUILTIN
				&& d_token->type[*i][j] != WRONG) && !d_pipe->failure)
			d_token->tokens[*i] = remove_first(d_token, d_token->type[*i][j],
					*i);
		else
			j++;
		if ((temp == D_AR || temp == S_AR || temp == S_AL) && !d_pipe->failure)
			d_token->tokens[*i] = remove_first(d_token, FAILE, *i);
		if (d_pipe->failure)
			break ;
		if (ft_strlenlen(d_token->tokens[*i]) == 0)
			d_token->type[*i][0] = WRONG;
	}
	return (cmd_return(d_pipe));
}
