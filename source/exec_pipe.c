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
	int id;
	char *buffer;

	j = 0;
	id = fork();

	if (id != 0) // PROCESSUS PERE
	{
		waitpid(id, &d_token->exitno ,0);
		d_pipe->failed = 0;
		if (d_token->exitno != 0)
			d_pipe->failed = 1;
		// if (d_pipe->failed == 0 && d_token->tokens[*i - 1])
		// 	d_pipe->or_return = 0;
		if (d_pipe->failed == 1 && *i < d_token->t_size)
		{
			if (d_token->type[*i + 1] != OR)
			{
				if (d_token->type[*i + 1] == P_C)
					if (d_pipe->p_cpt >= 0)
						d_pipe->p_return[d_pipe->p_cpt] = 1;
				ft_printf("or_return = 1, command = %s\n", d_token->tokens[*i][0]);
				d_pipe->or_return = 1;
				d_pipe->failed = 0;
			}
		}
		return;
	}

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
	exit(EXIT_FAILURE);//TEMPORAIRE -> LEAKS, FONCTION SPECIAL A FAIRE
}

void p_parse_type(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i)
{
	if (d_token->type[*i] == P_O)
	{
		d_pipe->p_cpt++;
	}
	if (d_token->type[*i] == P_C)
	{
		if (d_pipe->or_return == 1 || d_pipe->skip_and == 1)
			d_pipe->p_return[d_pipe->p_cpt] = 1;
		d_pipe->p_nbr--;
		d_pipe->p_cpt--;
	}
	if (d_token->type[*i] == S_AL)
	{
		if (access(d_token->tokens[*i + 1][0], F_OK) != 0 && access(d_token->tokens[*i + 1][0], X_OK) != 0)
			// exit_file(); // A FAIRE
		d_pipe->input = open(d_token->tokens[*i + 1][0], O_RDONLY);
	}
	if (d_token->type[*i] == CMD && d_pipe->skip_and == 0)
	{
		// ft_printf("=======\nskip_and: %d\nskip_or:%d\nor_return:%d\n======\n", d_pipe->skip_and, d_pipe->skip_or, d_pipe->or_return);
		if (d_pipe->skip_and == 0 && d_pipe->skip_or == 0 && d_pipe->or_return == 0 && d_pipe->p_return[d_pipe->p_cpt] == 0)
			exec_cmd(d_token, d_pipe, denv, i);
	}
	if (d_token->type[*i] == AND)
	{
		if (d_pipe->failed == 1)
		{
			d_pipe->skip_and = 1;
			d_pipe->failed = 0;
			// write(1, "SKIP AND\n", 10);
		}
	}
	if (d_token->type[*i] == OR)
	{
		if (d_pipe->failed == 0)
		{
			d_pipe->skip_or = 1;
			// write(1, "SKIP OR\n", 9);
		}
	}
}

void p_while(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i)
{
	(*i)++;
	while(d_pipe->p_nbr > 0)
	{
		p_parse_type(d_token, d_pipe, denv, i);
		(*i)++;
	}
}

void parse_type(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i)
{
	int j;

	if (d_token->type[*i] == S_AL)
	{
		if (access(d_token->tokens[*i + 1][0], F_OK) != 0 && access(d_token->tokens[*i + 1][0], X_OK) != 0)
			// exit_file(); // A FAIRE
		d_pipe->input = open(d_token->tokens[*i + 1][0], O_RDONLY);
	}
	if (d_token->type[*i] == CMD && d_pipe->skip_and == 0)
	{
		// ft_printf("=======\nskip_and: %d\nskip_or:%d\nor_return:%d\n======\n", d_pipe->skip_and, d_pipe->skip_or, d_pipe->or_return);
		if (*i < d_token->t_size)
		{
			j = 0;
			while(*i + j < d_token->t_size && d_token->type[*i + 1 + j] == S_AR)
			{
				d_pipe->output = open(d_token->tokens[*i + 2 + j][0], O_WRONLY | O_CREAT | O_TRUNC, 000064); //A Securiser + fuite fd
				dup2(d_pipe->output, STDOUT_FILENO);
				j +=2;
			}
		}
		if (d_pipe->skip_and == 0 && d_pipe->skip_or == 0 && d_pipe->or_return == 0)
			exec_cmd(d_token, d_pipe, denv, i);
		if (d_pipe->output != 0)
		{
			dup2(d_pipe->old_stdout, STDOUT_FILENO);
		}
	}
	if (d_token->type[*i] == P_O)
	{
		d_pipe->p_cpt++;
		p_while(d_token, d_pipe, denv, i);
	}
	if (d_token->type[*i] == P_C)
	{
		d_pipe->p_nbr--;
		d_pipe->p_cpt--;
	}
	if (d_token->type[*i] == AND)
	{
		d_pipe->skip_or = 0;
		if (d_pipe->failed == 1)
		{
			d_pipe->skip_and = 1;
			d_pipe->failed = 0;
			// write(1, "SKIP AND\n", 10);
		}
	}
	if (d_token->type[*i] == OR)
	{
		if (d_pipe->failed == 0)
		{
			d_pipe->skip_or = 1;
			// write(1, "SKIP OR\n", 9);
		}
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

void p_count(t_tok *d_token, t_pipe *d_pipe)
{
	int i;

	i = 0;
	while(i < d_token->t_size)
	{
		if (d_token->type[i] == P_O)
			d_pipe->p_nbr++;
		i++;
	}
	d_pipe->p_return = ft_calloc(d_pipe->p_nbr, sizeof(int));
}

void ms_main_pipe(t_tok d_token, t_env *denv)
{
	int i;
	int j;
	t_pipe d_pipe;
	
	ft_printf("%s== Return ==\n", ft_strdup(BLUE));
	j = 0;
	i = 0;
	init_d_pipe(&d_pipe);
	p_count(&d_token, &d_pipe);
	while(j < d_token.t_size)
	{
		parse_type(&d_token, &d_pipe, denv, &i);
		i++;
		j++;
	}
	ft_printf("exit no: %d\n", d_token.exitno);
	ft_printf("===========\n%s", ft_strdup(RESET));
	// while()
	// {
	//
	// }
	// set_output();
}

