/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:12:28 by nbardavi          #+#    #+#             */
/*   Updated: 2024/01/31 09:25:11 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	cmd_here(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i)
{
	int	p_here;

	p_here = check_here(d_token->tokens, *i);
	while (p_here > -1)
	{
		d_pipe->h_before = 1;
		d_token->tokens[*i][p_here] = h_handle(d_pipe, d_token, denv, i);
		p_here = check_here(d_token->tokens, *i);
	}
}

int	check_redi(char ***tokens, int i)
{
	int	j;

	j = 0;
	while (tokens[i][j])
	{
		if (ft_strcmp("<", tokens[i][j]) == 0)
			return (1);
		j++;
	}
	return (0);
}

extern int g_exitno;

void r_parse_error(int failure, char *file_name, t_pipe *d_pipe)
{
	if (failure == D_AR || failure == S_AR)
	{
		g_exitno = 1;
		fd_printf(2, "minishell: %fs: %fs\n", file_name, strerror(errno));
	}
	if (failure == S_AL)
	{
		d_pipe->t_cat  = 1;
		d_pipe->input = open("/dev/null", O_RDONLY);
		g_exitno = 1;
		fd_printf(2, "minishell: %fs: %fs\n", file_name, strerror(errno));
	}
}

int	cmd_redi(t_tok *d_token, t_pipe *d_pipe, int *i, int j)
{
	int failure;
	char *file_name;
	int k;
	char **new;

	k = 0;
	file_name = NULL;
	// ft_printf("len new: %d", ft_strlenlen(d_token->tokens[*i]));
	new = ft_calloc(ft_strlenlen(d_token->tokens[*i]) + 1, sizeof(char *));
	failure = 0;
	if (d_token->type[*i + 1] == P_C)
		j++;
	while(d_token->tokens[*i][j])
	{
		if (!ft_strcmp(d_token->tokens[*i][j], ">>"))
		{
			d_pipe->output = open(d_token->tokens[*i][++j], O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (d_pipe->output == -1)
			{
				failure = D_AR;
				file_name = ft_sprintf("%s", d_token->tokens[*i][j]);
				break;
			}
			else
				dup2(d_pipe->output, STDOUT_FILENO);
		}
		else if (!ft_strcmp(d_token->tokens[*i][j], ">"))
		{
			d_pipe->output = open(d_token->tokens[*i][++j], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (d_pipe->output == -1)
			{
				failure = S_AR;
				file_name = ft_sprintf("%s", d_token->tokens[*i][j]);
				break;
				// ft_printf("d_pipe->output: %d\n", d_pipe->output);
			}
			else
			{
				dup2(d_pipe->output, STDOUT_FILENO);
				close(d_pipe->output);
			}
		}
		else if (!ft_strcmp(d_token->tokens[*i][j], "<"))
		{
			if (access(d_token->tokens[*i][++j], F_OK | R_OK))
			{
				// ft_printf("Failure <\n");
				failure = S_AL;
				file_name = ft_sprintf("%s", d_token->tokens[*i][j]);
				break;
			}
			if (d_pipe->input != -1)
				close(d_pipe->input);
			d_pipe->input = open(d_token->tokens[*i][j], O_RDONLY);
		}
		else
			new[k++] = ft_strdup(d_token->tokens[*i][j]);
		j++;
	}
	d_token->tokens[*i] = new;
	if (failure != 0)
	{
		r_parse_error(failure, file_name, d_pipe);
		return(1);
	}
	if (d_pipe->input != -1)
		dup2(d_pipe->input, STDIN_FILENO);
	return(0);
}

// int	cmd_redi(t_tok *d_token, t_pipe *d_pipe, int *i, int j)
// {
// 	if (d_token->type[*i + 1] == P_C)
// 		j++;
// 	if (check_redi(d_token->tokens, *i) == 1)
// 		if (apply_redi(d_token, d_pipe, *i) == 1)
// 			return(1);
// 	while (*i + j < d_token->t_size && (d_token->type[*i + 1 + j] == S_AR || d_token->type[*i + 1 + j] == D_AR))
// 	{
// 		if (d_token->type[*i + 1 + j] == S_AR)
// 		{
// 			d_pipe->output = open(d_token->tokens[*i + 2 + j][0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 			if (d_pipe->output == -1)
// 			{
// 				fd_printf(2, "minishell: %fs: %fs\n", d_token->tokens[*i + 2 + j][0], strerror(errno));
// 				g_exitno = 1;
// 				return (1);
// 			}
// 			dup2(d_pipe->output, STDOUT_FILENO);
// 			close(d_pipe->output);
// 			j += 2;
// 		}
// 		if (d_token->type[*i + 1 + j] == D_AR)
// 		{
// 			d_pipe->output = open(d_token->tokens[*i + 2 + j][0], O_WRONLY | O_CREAT | O_APPEND, 0644);
// 			if (d_pipe->output == -1)
// 			{
// 				fd_printf(2, "minishell: %fs: %fs\n", d_token->tokens[*i + 2 + j][0], strerror(errno));
// 				g_exitno = 1;
// 				return (1);
// 			}
// 			dup2(d_pipe->output, STDOUT_FILENO);
// 			j += 2;
// 		}
// 	}
// 	return (0);
// }

void	cmd_reset_fd(t_pipe *d_pipe)
{
	if (d_pipe->input != -1)
	{
		dup2(d_pipe->old_stdin, STDIN_FILENO);
		d_pipe->input = -1;
	}
	if (d_pipe->output != -1)
	{
		dup2(d_pipe->old_stdout, STDOUT_FILENO);
		d_pipe->output = -1;
	}
}

void	handle_cmd(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i)
{
	int	p_here;

	p_here = check_here(d_token->tokens, *i);
	if (*i < d_token->t_size)
		if (cmd_redi(d_token, d_pipe, i, 0) == 1)
			return;
	if (p_here > -1)
		cmd_here(d_token, d_pipe, denv, i);
	if ((d_token->t_size > *i && d_token->type[*i + 1] == PIPE) || (*i > 0
			&& d_token->type[*i - 1] == PIPE))
	{
		w_exec_pipe(d_token, d_pipe, denv, i);
		d_pipe->t_r = 1;
	}
	else if (d_pipe->skip_and == 0 && d_pipe->skip_or == 0
		&& d_pipe->or_return == 0)
		exec_cmd(d_token, d_pipe, denv, i);
	cmd_reset_fd(d_pipe);
}

void	cmd_pipe(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i)
{
	if (d_token->t_size > *i && d_token->type[*i + 1] == PIPE)
	{
		w_exec_pipe(d_token, d_pipe, denv, i);
		return ;
	}
	else if (*i > 0 && d_token->type[*i - 1] == PIPE)
	{
		w_exec_pipe(d_token, d_pipe, denv, i);
		return ;
	}
}
