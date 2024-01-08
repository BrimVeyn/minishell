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

// void exec_pipe()
// {
//
// }
//
// void set_output()
// {
// }
//
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

void cut_here(t_tok *d_token, int *i)
{
	char **new;
	int nbr_args;
	int j;
	int k;

	k = 0;
	j = 0;
	while (d_token->tokens[*i][j] != NULL)
		j++;
	new = ft_calloc(j - 1, sizeof(char*)); //-1 psk heredoc dans deux args + NULL
	j = 0;
	while(d_token->tokens[*i][j] != NULL)
	{
		if (ft_strcmp(d_token->tokens[*i][j], ">>") == 0)
			j += 2;
		new[k++] = ft_strdup(d_token->tokens[*i][j++]);
	}
	free(d_token->tokens[*i]);
	d_token->tokens[*i] = new;
}

void exec_cmd(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i)
{
	int j;
	int pipefd[2];
	int id;
	char *buffer;

	j = 0;
	if (pipe(pipefd) == -1)
		exit (EXIT_FAILURE);
	id = fork();
	if (id != 0)
	{
		close(pipefd[1]);
		d_pipe->failed = 0;
		if (read(pipefd[0], buffer, 10) > 0)
			d_pipe->failed = 1;
		close(pipefd[0]);
		wait(NULL);
		return;
	}
	close(pipefd[0]);
	while(d_token->tokens[*i][j])
	{
		if (d_token->type[*i] == D_AL)// UTILISER STRCMP !!!
		{
			heredoc(d_pipe, d_token->tokens[*i][j + 1], denv);
			d_token->tokens[*i][j + 1] = ft_sprintf("%fs%d", ".temp_heredoc", d_pipe->nbr_h);
		}
		j++;
	}
	execve(d_token->tokens[*i][0], d_token->tokens[*i], denv->f_env);
	perror("execve failed");
	write(pipefd[1], "failed", 6);
	close(pipefd[0]);
	exit(EXIT_FAILURE);//TEMPORAIRE -> LEAKS, FONCTION SPECIAL A FAIRE
}

void parse_type(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i)
{
	if (d_token->type[*i] == S_AL)
	{
		if (access(d_token->tokens[*i + 1][0], F_OK) != 0 && access(d_token->tokens[*i + 1][0], X_OK) != 0)
			// exit_file(); // A FAIRE
		d_pipe->input = open(d_token->tokens[*i + 1][0], O_RDONLY);
	}
	if (d_token->type[*i] == CMD && d_pipe->skip_and == 0)
	{
		if (d_pipe->skip_and == 0)
			exec_cmd(d_token, d_pipe, denv, i);
	}
	if (d_token->type[*i] == AND)
	{
		if (d_pipe->failed == 1)
			d_pipe->skip_and = 1;
	}
	//if (d_token->type[i] == )
	// {i
	// 	if (access(d->token[i + 1][0], F_OK) != 0 && access(d->token[i + 1][0], X_OK) != 0)
	// 		exit_file();
	// 	d_pipe->output = open(d->token[i + 1][0], O_WRONLY);
	// 
	if (d_token->type[*i] == D_AL)
		heredoc(d_pipe, d_token->tokens[*i + 1][0], denv);
}

void ms_main_pipe(t_tok d_token, t_env *denv)
{
	int i;
	t_pipe d_pipe;

	i = 0;
	init_d_pipe(&d_pipe);
	parse_type(&d_token, &d_pipe, denv, &i);
	// while()
	// {
	//
	// }
	// set_output();
}

