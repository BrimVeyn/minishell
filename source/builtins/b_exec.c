/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:22:39 by nbardavi          #+#    #+#             */
/*   Updated: 2024/01/26 10:13:28 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int exitno;

void	b_redi(t_tok *d_token, t_pipe *d_pipe, int i)
{
	if (access(d_token->tokens[i + 1][0], F_OK | R_OK) == 0)
		perror("Minishell:");
	if (d_pipe->input != -1)
		close(d_pipe->input);
	d_pipe->input = open(d_token->tokens[i + 1][0], O_RDONLY);
}

void b_parse(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i)
{
	if (!ft_strcmp(d_token->tokens[*i][0], "echo"))
		b_echo(d_token, i);
	if (!ft_strcmp(d_token->tokens[*i][0], "env"))
		b_env(denv);
	if (!ft_strcmp(d_token->tokens[*i][0], "export"))
		b_export(d_token->tokens[*i], denv);
	if (!ft_strcmp(d_token->tokens[*i][0], "unset"))
		b_unset(d_token->tokens[*i], denv);
	if (!ft_strcmp(d_token->tokens[*i][0], "pwd"))
		b_pwd(d_token->tokens[*i], denv);
	if (!ft_strcmp(d_token->tokens[*i][0], "cd"))
		b_cd(d_token->tokens[*i], denv);
	if (!ft_strcmp(d_token->tokens[*i][0], "exit"))
		b_exit(d_pipe, d_token->tokens[*i]);
}

void handle_built(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i)
{
	b_parse(d_token, d_pipe, denv, i);
	// int id;
	// char *buffer;
	//
	// buffer = ft_calloc(2, sizeof(char));
	// pipe(d_pipe->b_pipefd);
	// id = fork();
	// if (id > 0)
	// {
	// 	waitpid(id, &exitno, 0);
	// 	close(d_pipe->b_pipefd[1]);
	// 	if (read(d_pipe->b_pipefd[0], buffer, 1) == 1)
	// 		d_pipe->t_exit = 1;
	// 	close(d_pipe->b_pipefd[0]);
	// }
	// else if (id == 0)
	// {
	// 	close(d_pipe->b_pipefd[0]);
	// 	b_parse(d_token, d_pipe, denv, i);
	// 	close(d_pipe->b_pipefd[1]);
	// }
}
