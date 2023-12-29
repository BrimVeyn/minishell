/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 15:06:31 by nbardavi          #+#    #+#             */
/*   Updated: 2023/12/28 14:11:47 by bvan-pae         ###   ########.fr       */
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

// void set_input(t_tok *d_token, t_pipe *d_pipe, t_env *denv)
// {
// 	//TEMPORAIRE
// 	// char **temp;
// 	//
// 	//
// 	// if (ft_strcmp("make", d_token->tokens[0][0]) == 0)
// 	// {
// 	// 	temp = ft_calloc(3, sizeof(char *));
// 	// 	temp[0] = ft_strdup("/chemin/vers/make");
// 	// 	temp[2] = NULL;
// 	//
// 	// 	execve(temp[0], temp, denv->f_env);
// 	// 
// 	if (d_token->type[0] == S_AL)
// 	{
// 		d_pipe->input = open(d_token->tokens[0][0], O_RDONLY);
// 	}
// 	if (d_token->type[0] == D_AL)
// 	{
// 		heredoc(d_pipe, d_token->tokens[1][0], denv); //HEREDOC PAS FORCEMENT AU DEBUT
// 	}
// 

int next_ident(t_tok *d_token, int i)
{
	while(d_token->tokens[i])
	{
		if (d_token->type[i][0] == PIPE)
			return (PIPE);
		else if (d_token->type[i][0] == OR)
			return (OR);
		else if (d_token->type[i][0] == AND)
			return (AND);
	}
	return(-1);
}

void e_cmd_pipe(t_tok *d_token, t_pipe *d_pipe, t_env *denv)
{

}

void pipe_cmd(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i)
{
	int cpt;

	cpt = 0;
	d_pipe->i_f = 0;
	while(next_ident(d_token, *i))
	{
		if (pipe(d_pipe->pipefd) == -1)
			exit(EXIT_FAILURE);
		d_pipe->fork_id[d_pipe->i_f] = fork();
		
		if (d_pipe->fork_id[d_pipe->i_f] != 0)
		{
			close(d_pipe->pipefd[1]);
			dup2(d_pipe->pipefd[0], STDIN_FILENO);
			close(d_pipe->pipefd[0]);
		}
		
		if (d_pipe->fork_id[d_pipe->i_f] == 0)
		{
			close(d_pipe->pipefd[0]);
			close(d_pipe->input);
			if (next_ident(d_token, *i) == PIPE)
				dup2(d_pipe->pipefd[1], STDOUT_FILENO);
			else
				dup2(d_pipe->output, STDOUT_FILENO);
			close(d_pipe->pipefd[1]);
			close(d_pipe->output);
			execve(d_token->tokens[*i][0], d_token->tokens[*i], denv->f_env);
			// exit_execve(d_pipe);
		}
		*i += 2;
	}

	while(cpt < d_pipe->i_f)
		waitpid(d_pipe->fork_id[cpt++], NULL, 0);
}

void exec_cmd(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i)
{
	int j;

	j = 1;
	while(d_token->tokens[*i][j])
	{
		if (d_token->type[*i][j] == D_AL)
		{
			heredoc(d_pipe, d_token->tokens[*i][j + 1], denv);
			d_token->tokens[*i][j + 1] = ft_sprintf("%fs%d", ".temp_heredoc", d_pipe->nbr_h);
		}
		j++;
	}
	execve(d_token->tokens[*i][0], d_token->tokens[*i], denv->f_env);
	exit(EXIT_FAILURE);//TEMPORAIRE -> LEAKS, FONCTION SPECIAL A FAIRE
}

void parse_type(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i)
{
	if (d_token->type[*i][0] == S_AL)
	{
		if (access(d_token->tokens[*i + 1][0], F_OK) != 0 && access(d_token->tokens[*i + 1][0], X_OK) != 0)
			// exit_file();
		d_pipe->input = open(d_token->tokens[*i + 1][0], O_RDONLY);
	}
	if (d_token->type[*i][0] == CMD)
		if (next_ident(d_token, *i) == PIPE)
			pipe_cmd(d_token, d_pipe, denv, i);
		exec_cmd(d_token, d_pipe, denv, i);
	//if (d_token->type[i] == )
	// i
	// 	if (access(d->token[i + 1][0], F_OK) != 0 && access(d->token[i + 1][0], X_OK) != 0)
	// 		exit_file();
	// 	d_pipe->output = open(d->token[i + 1][0], O_WRONLY);
	// 
	if (d_token->type[*i][0] == D_AL)
		heredoc(d_pipe, d_token->tokens[*i + 1][0], denv);
}

void ms_main_pipe(t_tok d_token, t_env *denv)
{
	int i;
	t_pipe d_pipe;

	i = 0;
	// init_d_pipe(&d_pipe);
	while (d_token.tokens[i])
	{
		parse_type(&d_token, &d_pipe, denv, &i);
		i++;
	}
	// while()
	// {
	//
	// }
	// set_output();
}

