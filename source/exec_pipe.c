/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:26:22 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/23 16:26:41 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		check_here(char ***tokens, int i);
void	cut_here(t_tok *d_token, int *i);
void	exec_pipe(t_tok *d_token, t_pipe *d_pipe, char *env[], int *i);
void	pipe_parse(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i);
void	w_exec_pipe(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i);
void	ms_free_env(t_env *denv);
// void exec_pipe()
// {
//
// }
//
// void set_output()
// {
// }

char *ms_getlast(t_env *denv)
{
	t_h_lst *lst;

	lst = denv->history;
	while(lst->next != NULL)
		lst = lst->next;
	return (lst->content);
}

void print_history(t_env *denv)
{
	t_h_lst *lst;

	lst = denv->history;
	while(lst != NULL)
	{
		ft_printf("content: %fs\n", lst->content);
		lst = lst->next;
		ft_printf("=======\n");
	}
}

void reset_history(t_env *denv)
{
	t_h_lst *lst;

	lst = denv->history;
	rl_clear_history();
	while(lst != NULL)
	{
		add_history(lst->content);
		lst = lst->next;
	}
}

char *h_before(t_pipe *d_pipe, t_tok *d_token, t_env *denv, int *i)
{
	char	*input;
	char	*save;
	char	*f_name;
	char	*limiter;
	char	*sasave;
	int		cpt;
	int		trigger;

	trigger = 0;
	cpt = 1;
	limiter = d_token->tokens[*i + 1][0];
	cut_here(d_token, i);
	f_name = ft_sprintf("%fs%d", ".temp_heredoc", d_pipe->nbr_h++);
	d_pipe->heredoc = open(f_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	save = ft_strdup("");
	while(d_token->heredoc && d_token->heredoc[d_pipe->h_i])
	{
		if (ft_strcmp(d_token->heredoc[d_pipe->h_i], limiter) == 0)
		{
			trigger = 1;
			break;
		}	
		save = ft_sprintf("%s%fs\n", save, d_token->heredoc[d_pipe->h_i++]);
	}
	while(1 && trigger != 1)
	{
		input = readline("> ");
		if (input == NULL)
		{
			printf("minishell: warning: here-document at line %d delimited by end-of-file (wanted '%s')\n", cpt, limiter);
			return (NULL);
		}
		if (ft_strcmp(limiter, input) == 0)
			break;
		cpt++;
		save = ft_sprintf("%s%s\n", save, input);
	}
	sasave = ft_strdup(save);
	if (trigger == 0)
		save = ft_sprintf("%fs\n%s%fs", ms_getlast(denv), save, limiter);
	else
	{
		save = ft_sprintf("%fs", ms_getlast(denv));
		ft_printf("Save trigger = 1: %fs\n", save);
	}
	ms_lst_b(&denv->history, ms_lst_new(ft_strdup(save)));
	reset_history(denv);
	ft_printf("Sasave : %fs\n", sasave);
	fd_printf(d_pipe->heredoc, "%s", sasave);
	add_history(save);
	ft_printf("%fs\n", "===============");
	free(save);
	close(d_pipe->heredoc);
	return (f_name);
}

void print_tokens(t_tok *d_token)
{
    for (int i = 0; d_token->tokens[i]; i++)
    {
        ft_printf("S->TYPE[%d] = %d\n", i, d_token->type[i]);
        for (int j = 0; d_token->tokens[i][j]; j++)
            ft_printf("S[%d][%d] = %fs\n", i, j, d_token->tokens[i][j]);
    }
}


char *heredoc(t_pipe *d_pipe, t_tok *d_token, t_env *denv, int *i)
{
	char	*input;
	char	*save;
	char	*f_name;
	char	*limiter;
	char	*sasave;
	int		cpt;
	int		trigger;

	trigger = 0;
	cpt = 1;
	limiter = d_token->tokens[*i][check_here(d_token->tokens, *i) + 1];
	cut_here(d_token, i);
	f_name = ft_sprintf("%fs%d", ".temp_heredoc", d_pipe->nbr_h++);
	d_pipe->heredoc = open(f_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	save = ft_strdup("");
	while(d_token->heredoc && d_token->heredoc[d_pipe->h_i])
	{
		if (ft_strcmp(d_token->heredoc[d_pipe->h_i], limiter) == 0)
		{
			trigger = 1;
			break;
		}	
		save = ft_sprintf("%s%fs\n", save, d_token->heredoc[d_pipe->h_i++]);
	}
	while(1 && trigger != 1)
	{
		input = readline("> ");
		if (input == NULL)
		{
			printf("minishell: warning: here-document at line %d delimited by end-of-file (wanted '%s')\n", cpt, limiter);
			return (NULL);
		}
		if (ft_strcmp(limiter, input) == 0)
			break;
		cpt++;
		save = ft_sprintf("%s%s\n", save, input);
	}
	sasave = ft_strdup(save);
	if (trigger == 0)
		save = ft_sprintf("%fs\n%s%fs", ms_getlast(denv), save, limiter);
	else
	{
		save = ft_sprintf("%fs", ms_getlast(denv));
		ft_printf("Save trigger = 1: %fs\n", save);
	}
	ms_lst_b(&denv->history, ms_lst_new(ft_strdup(save)));
	reset_history(denv);
	ft_printf("Sasave : %fs\n", sasave);
	fd_printf(d_pipe->heredoc, "%s", sasave);
	add_history(save);
	ft_printf("%fs\n", "===============");
	free(save);
	close(d_pipe->heredoc);
	return (f_name);
}

void t_heredoc(t_tok *d_token, int *i, char *limiter)
{
	char	*input;
	int		cpt;

	cpt = 1;
	if (limiter == NULL)
		limiter = d_token->tokens[*i + 1][0];
	while(1)
	{
		input = readline("> ");
		if (input == NULL)
		{
			printf("minishell: warning: here-document at line %d delimited by end-of-file (wanted '%s')\n", cpt, limiter);
			return;
		}
		else if (ft_strcmp(limiter, input) == 0)
			break;
		cpt++;
	}
	d_token->exitno = 0;
}

int check_here(char ***tokens, int i)
{
	int j;

	j = 0;
	// ft_printf("i:%d\n", i);
	while(tokens[i][j])
	{
		// printf("j:%d\n", j);
		if(ft_strcmp(tokens[i][j], "<<") == 0)
			return (j);
		j++;
	}
	return (-1);
}

int ft_strlenlen(char **str)
{
	int i;

	i = 0;
	while(str[i])
		i++;
	return(i);
}

void	apply_redi(t_tok *d_token, t_pipe *d_pipe,int i)
{
	int j;
	char **new;

	j = 0;
	new = ft_calloc(ft_strlenlen(d_token->tokens[i]), sizeof(char *));
	while(d_token->tokens[i][j])
	{
		if (ft_strcmp(d_token->tokens[i][j], "<") == 0)
		{
			if (access(d_token->tokens[i][j + 1], F_OK | R_OK))
				perror("minishell input:");
			if (d_pipe->input != -1)
				close(d_pipe->input);
			d_pipe->input = open(d_token->tokens[i][j + 1], O_RDONLY);
			j++;
		}
		else
			new[j] = ft_strdup(d_token->tokens[i][j]);
		j++;
	}
	free(d_token->tokens[i]);
	d_token->tokens[i] = new;
	dup2(d_pipe->input, STDIN_FILENO);
}

void	b_redi(t_tok *d_token, t_pipe *d_pipe, int i)
{
	if (access(d_token->tokens[i + 1][0], F_OK | R_OK) == 0)
		perror("Minishell:");
	if (d_pipe->input != -1)
		close(d_pipe->input);
	d_pipe->input = open(d_token->tokens[i + 1][0], O_RDONLY);
}

void print_tok(t_tok *d_token)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(i < d_token->t_size)
	{
		while(d_token->tokens[i][j])
		{
			printf("tokens[%d][%d] = %s\n", i, j, d_token->tokens[i][j]);
			j++;
		}
		j = 0;
		i++;
	}
}

void cut_here(t_tok *d_token, int *i)
{
	char **new;
	int j;
	int k;
	int len;
	int trigger;

	trigger = 0;
	len = 0;
	k = 0;
	j = 0;
	while (d_token->tokens[*i][len] != NULL)
		len++;
	new = ft_calloc(len, sizeof(char*)); //-1 psk heredoc dans deux args + NULL A CHANGER SI PLUSIEURS HEREDOC
	j = 0;
	while(d_token->tokens[*i][j] != NULL && j < len)
	{
		if (ft_strcmp(d_token->tokens[*i][j], "<<") == 0 && trigger == 0)
		{
			// ft_printf("Cut un <<\n");
			j += 1;
			trigger = 1;
		}
		if (j >= len)
			break;
		// ft_printf("copie : %fs\n", d_token->tokens[*i][j]);
		new[k++] = ft_strdup(d_token->tokens[*i][j++]);
	}
	free(d_token->tokens[*i]);
	d_token->tokens[*i] = new;
	// print_tok(d_token);
}

void exec_cmd(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i)
{
	int j;
	int id;

	j = 0;
	id = fork();
	
	if (id != 0) // PROCESSUS PERE
	{
		signal(SIGINT, SIG_IGN);
		waitpid(id, &d_token->exitno ,0);
		init_sig();
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
				// ft_printf("or_return = 1, command = %s\n", d_token->tokens[*i][0]);
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
			heredoc(d_pipe, d_token, denv, i);
			d_token->tokens[*i][j + 1] = ft_sprintf("%fs%d", ".temp_heredoc", d_pipe->nbr_h);
		}
		j++;
	}
	// ft_printf("tokens debug:%fs\n", d_token->tokens[*i][0]);
	close(d_pipe->old_stdin);
	close(d_pipe->old_stdout);
	execve(d_token->tokens[*i][0], d_token->tokens[*i], denv->f_env);
	perror("execve failed");
	exit(EXIT_FAILURE);//TEMPORAIRE -> LEAKS, FONCTION SPECIAL A FAIRE
}

void p_redi(t_tok *d_token, t_pipe *d_pipe, int *i)
{
	int j;

	j = 0;
	while (d_token->type[*i + j] != P_C)
		j++;
	if (d_token->type[*i + j + 1] == S_AR)
	{
		d_pipe->p_redi_fd = open(d_token->tokens[*i + 2 +j][0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(d_pipe->p_redi_fd, STDOUT_FILENO);
	}
	else
		d_pipe->p_redi_fd = d_pipe->old_stdout;
	if (d_token->type[*i + j + 1] == S_AL)
	{
		d_pipe->input = open(d_token->tokens[*i + 2 + j][0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(d_pipe->input, STDIN_FILENO);
	}
}

void p_parse_type(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i)
{
	int j;
	int p_here;

	ft_printf("i:%d\n", *i);
	p_here = check_here(d_token->tokens, *i);
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
		if (*i < d_token->t_size) // REDIRECTION
		{
			j = 0;
			if (d_token->type[*i + 1] == P_C)
				j++;
			// while(*i + j < d_token->t_size && d_token->type[*i + 1 + j] == S_AL)
			// {
			// 	d_pipe->input = open(d_token->tokens[*i + 2 + j][0], O_RDONLY);
			// 	if (d_pipe->input == -1)
			// 		perror("Error: ");
			// 	dup2(d_pipe->input, STDIN_FILENO);
			// 	j += 2;
			// }
			while(*i + j < d_token->t_size && (d_token->type[*i + 1 + j] == S_AR || d_token->type[*i + 1 + j] == S_AL || d_token->type[*i + 1 + j] == D_AR))
			{
				if (d_token->type[*i + 1 + j] == S_AR)
				{
					d_pipe->output = open(d_token->tokens[*i + 2 + j][0], O_WRONLY | O_CREAT | O_TRUNC, 0644); //A Securiser + fuite fd
					if (d_pipe->output == -1)
						perror("Error: ");
					dup2(d_pipe->output, STDOUT_FILENO);
					j +=2;
				}
				if (d_token->type[*i + 1 + j] == S_AL)
				{
					d_pipe->input = open(d_token->tokens[*i + 2 + j][0], O_RDONLY);
					if (d_pipe->input == -1)
						perror("Error: ");
					dup2(d_pipe->input, STDIN_FILENO);
					j += 2;
				}
				if (d_token->type[*i + 1 + j] == D_AR)
				{	
					d_pipe->output = open(d_token->tokens[*i + 2 + j][0], O_WRONLY | O_CREAT | O_APPEND, 0644); //A Securiser + fuite fd
					if (d_pipe->output == -1)
						perror("Error: ");
					dup2(d_pipe->output, STDOUT_FILENO);
					j +=2;
				}
			}
		}

		if (p_here > -1) //HEREDOC
		{
			// cut_here(d_token, i);
			while(p_here > -1)
			{
				// print_tok(d_token);
				d_token->tokens[*i][p_here] = heredoc(d_pipe, d_token, denv, i);
				// print_tok(d_token);
				p_here = check_here(d_token->tokens, *i);
				// ft_printf("p_here:%d", p_here);
			}
			// ft_printf("p_here: %d\n", p_here);
			// ft_printf("p_here:%d\nindice 2:%fs\nindice 1:%fs\n", p_here, d_token->tokens[*i][2], d_token->tokens[*i][1]);
		}
		
		if (d_token->t_size > *i)
		{
			if (d_token->type[*i + 1] == PIPE)
			{
				w_exec_pipe(d_token, d_pipe, denv, i);
				return;
			}
		}
		else if(*i > 0)
			if (d_token->type[*i - 1] == PIPE)
			{
				w_exec_pipe(d_token, d_pipe, denv, i);
				return;
			}

		// ft_printf("Hello");
		if (d_pipe->skip_and == 0 && d_pipe->skip_or == 0 && d_pipe->or_return == 0)
			exec_cmd(d_token, d_pipe, denv, i);
		
		if (d_pipe->input != -1)
		{
			ft_printf("Reset stdint");
			dup2(d_pipe->old_stdin, STDIN_FILENO);
			d_pipe->input = -1;
		}
		if (d_pipe->output != -1) // RESET FD
		{
			dup2(d_pipe->old_stdout, STDOUT_FILENO);
			d_pipe->output = -1;
		}
	}

	if (d_token->type[*i] == WRONG)
	{
		d_token->exitno = 127;
		d_pipe->failed = 1;
	}
	if (d_token->type[*i] == AND)
	{
		d_pipe->skip_or = 0;
		if (d_pipe->failed == 1 )
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
	p_redi(d_token, d_pipe, i);
	while(d_pipe->p_nbr > 0)
	{
		// ft_printf("parenthese nbr:%d\n", d_pipe->p_nbr);
		p_parse_type(d_token, d_pipe, denv, i);
		if (d_pipe->p_trig == 0)
			(*i)++;
		else
			d_pipe->p_trig = 0;
	}
	dup2(d_pipe->old_stdout, STDOUT_FILENO);
}

int next_ope(t_tok *d_token, int i)
{
	i++;
	// fd_printf(2, "i: %d, size%d\n", i, d_token->t_size);
	while(i < d_token->t_size)
	{
		if (d_token->type[i] == AND)
			return (AND);
		else if (d_token->type[i] == PIPE)
			return (PIPE);
		else if (d_token->type[i] == OR)
			return (OR);
		else if (d_token->type[i] == WRONG)
			return (WRONG); 
		i++;
		// fd_printf(2, "%d\n", i);
	}
	return (-42);
}

int previous_ope(t_tok *d_token, int i)
{
	i--;
	while(i >= 0)
	{
		if (d_token->type[i] == CMD)
			return (CMD);
		else if (d_token->type[i] == AND)
			return (AND);
		else if (d_token->type[i] == PIPE)
			return (PIPE);
		else if (d_token->type[i] == OR)
			return (OR);
		else if (d_token->type[i] == WRONG)
			return (WRONG);
		i--;
	}
	return (-42);
}

void	w_exec_pipe(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i)
{
	// exec_pipe(d_token, d_pipe, denv->f_env, i);
	// waitpid(d_pipe->f_id, &d_token->exitno, 0);
	int j;

	j = 0;
	d_pipe->f_cpt = 0;
	dup2(d_pipe->input, STDIN_FILENO);
	while((next_ope(d_token, *i) == PIPE || (previous_ope(d_token, *i) == PIPE && next_ope(d_token, *i) != PIPE) || d_token->type[*i] == PIPE) && d_token->t_size > *i)
	{
		pipe_parse(d_token, d_pipe, denv, i);
		// fd_printf(2, "Execution de %s\n", d_token->tokens[*i][0]);
		// printf("f_cpt: %d\n", d_pipe->f_cpt);
		// printf("next_ope: %d\n, previous ope: %d\n==\n", next_ope(d_token, *i), previous_ope(d_token, *i));
		d_pipe->f_cpt++;
		(*i)++;
	}
	dup2(d_pipe->old_stdin, STDIN_FILENO);
	while(d_pipe->f_cpt >= j)
	{
		// ft_printf("Wait\n");
		waitpid(d_pipe->f_id[d_pipe->f_cpt], &d_token->exitno, 0);
		j++;
	}
	d_pipe->p_trig = 1;
}

void pipe_parse(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i)
{
	int j;
	int p_here;

	// ft_printf("i nbr:%d\n", *i);
	p_here = check_here(d_token->tokens, *i);
	
	if (d_token->type[*i] == S_AL)
	{
		if (access(d_token->tokens[*i + 1][0], F_OK) != 0 && access(d_token->tokens[*i + 1][0], X_OK) != 0)
			// exit_file(); // A FAIRE
		d_pipe->input = open(d_token->tokens[*i + 1][0], O_RDONLY);
	}


	// if (p_here > -1) //HEREDOC
	// {
	// 	// cut_here(d_token, i);
	// 	while(p_here > -1)
	// 	{
	// 		// print_tok(d_token);
	// 		d_token->tokens[*i][p_here] = heredoc(d_pipe, d_token, denv, i);
	// 		// print_tok(d_token);
	// 		p_here = check_here(d_token->tokens, *i);
	// 		// ft_printf("p_here:%d", p_here);
	// 	}
	// 	// ft_printf("p_here: %d\n", p_here);
	// 	// ft_printf("p_here:%d\nindice 2:%fs\nindice 1:%fs\n", p_here, d_token->tokens[*i][2], d_token->tokens[*i][1]);
	// }	

	if ((d_token->type[*i] == CMD && d_pipe->skip_and == 0) || d_token->type[*i] == WRONG)
	{
		// ft_printf("=======\nskip_and: %d\nskip_or:%d\nor_return:%d\n======\n", d_pipe->skip_and, d_pipe->skip_or, d_pipe->or_return);
		if (*i < d_token->t_size) // REDIRECTION
		{
			j = 0;
			if (d_token->type[*i + 1] == P_C)
				j++;
			// while(*i + j < d_token->t_size && d_token->type[*i + 1 + j] == S_AL)
			// {
			// 	d_pipe->input = open(d_token->tokens[*i + 2 + j][0], O_RDONLY);
			// 	if (d_pipe->input == -1)
			// 		perror("Error: ");
			// 	dup2(d_pipe->input, STDIN_FILENO);
			// 	j += 2;
			// }
			while(*i + j < d_token->t_size && (d_token->type[*i + 1 + j] == S_AR || d_token->type[*i + 1 + j] == S_AL || d_token->type[*i + 1 + j] == D_AR))
			{
				if (d_token->type[*i + 1 + j] == S_AR)
				{
					d_pipe->output = open(d_token->tokens[*i + 2 + j][0], O_WRONLY | O_CREAT | O_TRUNC, 0644); //A Securiser + fuite fd
					if (d_pipe->output == -1)
						perror("Error: ");
					dup2(d_pipe->output, STDOUT_FILENO);
					j +=2;
				}
				if (d_token->type[*i + 1 + j] == S_AL)
				{
					d_pipe->input = open(d_token->tokens[*i + 2 + j][0], O_RDONLY);
					if (d_pipe->input == -1)
						perror("Error: ");
					dup2(d_pipe->input, STDIN_FILENO);
					j += 2;
				}
				if (d_token->type[*i + 1 + j] == D_AR)
				{	
					d_pipe->output = open(d_token->tokens[*i + 2 + j][0], O_WRONLY | O_CREAT | O_APPEND, 0644); //A Securiser + fuite fd
					if (d_pipe->output == -1)
						perror("Error: ");
					dup2(d_pipe->output, STDOUT_FILENO);
					j +=2;
				}
			}
		}

		if (p_here > -1) //HEREDOC
		{
			// cut_here(d_token, i);
			while(p_here > -1)
			{
				// print_tok(d_token);
				d_token->tokens[*i][p_here] = heredoc(d_pipe, d_token, denv, i);
				// print_tok(d_token);
				p_here = check_here(d_token->tokens, *i);
				// ft_printf("p_here:%d", p_here);
			}
			// ft_printf("p_here: %d\n", p_here);
			// ft_printf("p_here:%d\nindice 2:%fs\nindice 1:%fs\n", p_here, d_token->tokens[*i][2], d_token->tokens[*i][1]);
		}
		// ft_printf("Hello");
		if (d_pipe->skip_and == 0 && d_pipe->skip_or == 0 && d_pipe->or_return == 0)
		{
			if(d_pipe->output == -1)
				d_pipe->output = d_pipe->old_stdout;
			if(d_pipe->input == -1)
				d_pipe->input = d_pipe->old_stdin;
			exec_pipe(d_token, d_pipe, denv->f_env, i);
			if (d_pipe->output == d_pipe->old_stdout)
				d_pipe->output = -1;
			if (d_pipe->input == d_pipe->old_stdin)
				d_pipe->input = -1;
		}

		if (d_pipe->input != -1)
		{
			ft_printf("Reset stdint");
			dup2(d_pipe->old_stdin, STDIN_FILENO);
			d_pipe->input = -1;
		}
		if (d_pipe->output != -1) // RESET FD
		{
			dup2(d_pipe->old_stdout, STDOUT_FILENO);
			d_pipe->output = -1;
		}
	}

	if (d_token->type[*i] == P_O)
	{
		d_pipe->p_cpt++;
		// d_pipe->p_trig = 1;
		p_while(d_token, d_pipe, denv, i);
	}
	if (d_token->type[*i] == P_C)
	{
		d_pipe->p_nbr--;
		d_pipe->p_cpt--;
	}

	// if (d_token->type[*i] == WRONG)
	// {
	// 	d_token->exitno = 127;
	// 	d_pipe->failed = 1;
	// }
	if (d_token->type[*i] == AND)
	{
		d_pipe->skip_or = 0;
		if (d_pipe->failed == 1 )
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
		heredoc(d_pipe, d_token, denv, i);
}

void	exec_pipe(t_tok *d_token, t_pipe *d_pipe, char *env[], int *i)
{
	// killfork(data);
	pipe(d_pipe->pipefd);
	d_pipe->f_id[d_pipe->f_cpt] = fork();
	if (d_pipe->f_id[d_pipe->f_cpt] > 0)
	{
		close(d_pipe->pipefd[1]);
		dup2(d_pipe->pipefd[0], STDIN_FILENO);
		close(d_pipe->pipefd[0]);
	}
	else if (d_pipe->f_id[d_pipe->f_cpt] == 0)
	{
		// fd_printf(2, "f_cpt: %d\n", d_pipe->f_cpt);
		close(d_pipe->pipefd[0]);
		close(d_pipe->input);
		// fd_printf(2, "Next ope: %d\nPrevious ope: %d\n", next_ope(d_token, *i), previous_ope(d_token, *i));
		if (previous_ope(d_token, *i) != PIPE)
		{
			dup2(d_pipe->input, STDIN_FILENO);
		}
		if (next_ope(d_token, *i) == PIPE)
		{
			// printf("Redirection Output vers Pipe de %s\n", d_token->tokens[*i][0]);
			dup2(d_pipe->pipefd[1], STDOUT_FILENO);
		}
		else
		{
			// fd_printf(2, "Redirection Output vers output de %fs\n", d_token->tokens[*i][0]);
			// fd_printf(2, "output: %d", d_pipe->output);
			dup2(d_pipe->output, STDOUT_FILENO);
		}
		close(d_pipe->pipefd[1]);
		close(d_pipe->output);
		execve(d_token->tokens[*i][0], d_token->tokens[*i], env);
		perror("");
		exit (EXIT_FAILURE);
		// exit_execve(data);
	}
	else 
		perror("fork");
}

void ms_place_h(t_tok *d_token, char *f_name, int i)
{
	int j;
	int k;
	char **u_char;

	j = 0;
	k = 0;
	while(d_token->tokens[i + 2][j])
		j++;
	u_char = ft_calloc(j + 2, sizeof(char *));
	j = 0;
	while(d_token->tokens[i + 2][j])
	{	
		u_char[j] = ft_strdup(d_token->tokens[i + 2][j]);
		j++;
	}
	u_char[j] = ft_strdup(f_name);
	free_tab(d_token->tokens[i + 2]);
	d_token->tokens[i + 2] = u_char;
}

void b_parse(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i)
{
	(void) d_pipe;
	(void)denv;
	// if (ft_strcmp(d_token->tokens[*i][0], "echo"))
	// 	b_echo();
	if (!ft_strcmp(d_token->tokens[*i][0], "env"))
		b_env(denv);
	if (!ft_strcmp(d_token->tokens[*i][0], "export"))
		b_export(d_token->tokens[*i], denv);
	if (!ft_strcmp(d_token->tokens[*i][0], "unset"))
		b_unset(d_token->tokens[*i], denv);
	// if (ft_strcmp(d_token->tokens[*i][0], "pwd"))
	// 	b_pwd();
	// if (ft_strcmp(d_token->tokens[*i][0], "cd"))
	// 	b_cd();
	// if (ft_strcmp(d_token->tokens[*i][0], "exit"))
	// 	b_exit();
	if (!ft_strcmp(d_token->tokens[*i][0], "exit"))
	{
		ft_printf("WHOUUU");
		b_exit(d_pipe,d_token->tokens[*i]);
	}
}

void parse_type(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i)
{
	int j;
	int p_here;

	// ft_printf("i nbr:%d\n", *i);
	p_here = check_here(d_token->tokens, *i);
	// p_redi = check_redi(d_token->tokens, *i);

	if (d_token->type[*i] == BUILTIN)
	{
		b_parse(d_token, d_pipe, denv, i);
	}
	if (d_token->type[*i] == D_AL)
	{
		if (d_token->type[*i + 2] == CMD && d_token->t_size > 2)
		{
			ms_place_h(d_token, h_before(d_pipe, d_token, denv, i), *i);
		}
		else
		{
			t_heredoc(d_token, i, NULL);
		}
		return;
	}
	if (d_token->type[*i] == S_AL)
	{
		b_redi(d_token, d_pipe, *i);
	}
	if (d_token->type[*i] == CMD && d_pipe->skip_and == 0)
	{
		// ft_printf("=======\nskip_and: %d\nskip_or:%d\nor_return:%d\n======\n", d_pipe->skip_and, d_pipe->skip_or, d_pipe->or_return);
		if (*i < d_token->t_size) // REDIRECTION
		{
			j = 0;
			if (d_token->type[*i + 1] == P_C)
				j++;
			apply_redi(d_token, d_pipe, *i);
			while(*i + j < d_token->t_size && (d_token->type[*i + 1 + j] == S_AR || d_token->type[*i + 1 + j] == D_AR))
			{
				if (d_token->type[*i + 1 + j] == S_AR)
				{
					d_pipe->output = open(d_token->tokens[*i + 2 + j][0], O_WRONLY | O_CREAT | O_TRUNC, 0644); //A Securiser + fuite fd
					if (d_pipe->output == -1)
						perror("Error: ");
					dup2(d_pipe->output, STDOUT_FILENO);
					close(d_pipe->output);
					j +=2;
				}
				if (d_token->type[*i + 1 + j] == D_AR)
				{	
					d_pipe->output = open(d_token->tokens[*i + 2 + j][0], O_WRONLY | O_CREAT | O_APPEND, 0644); //A Securiser + fuite fd
					if (d_pipe->output == -1)
						perror("Error: ");
					dup2(d_pipe->output, STDOUT_FILENO);
					j +=2;
				}
			}
		}

		if (p_here > -1) //HEREDOC
		{
			// cut_here(d_token, i);
			while(p_here > -1)
			{
				// print_tok(d_token);
				d_token->tokens[*i][p_here] = heredoc(d_pipe, d_token, denv, i);
				// print_tok(d_token);
				p_here = check_here(d_token->tokens, *i);
				// ft_printf("p_here:%d", p_here);
			}
			// ft_printf("p_here: %d\n", p_here);
			// ft_printf("p_here:%d\nindice 2:%fs\nindice 1:%fs\n", p_here, d_token->tokens[*i][2], d_token->tokens[*i][1]);
		}
		
		if (d_token->t_size > *i)
		{
			if (d_token->type[*i + 1] == PIPE)
			{
				w_exec_pipe(d_token, d_pipe, denv, i);
				return;
			}
		}
		else if(*i > 0)
			if (d_token->type[*i - 1] == PIPE)
			{
				w_exec_pipe(d_token, d_pipe, denv, i);
				return;
			}

		// ft_printf("Hello");
		if (d_pipe->skip_and == 0 && d_pipe->skip_or == 0 && d_pipe->or_return == 0)
			exec_cmd(d_token, d_pipe, denv, i);
		
		if (d_pipe->input != -1)
		{
			ft_printf("Reset stdint");
			dup2(d_pipe->old_stdin, STDIN_FILENO);
			d_pipe->input = -1;
		}
		if (d_pipe->output != -1) // RESET FD
		{
			dup2(d_pipe->old_stdout, STDOUT_FILENO);
			d_pipe->output = -1;
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
	if (d_token->type[*i] == WRONG)
	{
		d_token->exitno = 127;
		d_pipe->failed = 1;
	}
	if (d_token->type[*i] == AND)
	{
		d_pipe->skip_or = 0;
		if (d_pipe->failed == 1 )
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
	// if (d_token->type[i] == )
	// {i
	// 	if (access(d->token[i + 1][0], F_OK) != 0 && access(d->token[i + 1][0], X_OK) != 0)
	// 		exit_file();
	// 	d_pipe->output = open(d->token[i + 1][0], O_WRONLY);
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

void ms_h_unlink(t_pipe *d_pipe)
{
	char *temp;

	d_pipe->nbr_h--;
	while(d_pipe->nbr_h > -1)
	{
		temp = ft_sprintf("%fs%d", ".temp_heredoc", d_pipe->nbr_h);
		unlink(temp);
		free(temp);
		ft_printf("nbr_h: %d\n", d_pipe->nbr_h);
		d_pipe->nbr_h--;
	}
}

void ms_free_history(t_h_lst **head)
{
	t_h_lst *tmp;
	
	while (*head)
	{
		tmp = (*head)->next;
		free(*head);
		*head = tmp;
	}
}

void ms_free_env(t_env *denv)
{
	free_tab(denv->f_env);
	free(denv->usr);
	free(denv->path);
	free(denv->pwd);
	if(denv->history)
		ms_free_history(&denv->history);
}

void ms_free_pipe(t_pipe *d_pipe)
{
	free(d_pipe->fork_id);
	free(d_pipe->f_id);
	free(d_pipe->p_return);
	close(d_pipe->old_stdout);
	close(d_pipe->old_stdin);
}

int ms_main_pipe(t_tok d_token, t_env *denv)
{
	int i;
	t_pipe d_pipe;
	
	ft_printf("%s== Return ==\n", ft_strdup(BLUE));
	i = 0;
	if (d_token.tokens == NULL)
		return(0);
	init_d_pipe(&d_pipe);
	p_count(&d_token, &d_pipe);
	while(i < d_token.t_size)
	{
		if (d_token.type[0] == -1)
			break;
		parse_type(&d_token, &d_pipe, denv, &i);
		i++;
		if (d_pipe.t_exit == 1)
			break;
	}
	ft_printf("===========\n%s", ft_strdup(RESET));
	ms_h_unlink(&d_pipe);
	// ms_free_env(denv);
	ms_free_pipe(&d_pipe);
	if (d_pipe.t_exit == 1)
		return(1);
	return(0);
	// while()
	// {
	//
	// }
	// set_output();
}


/*
Notes:

-faire calloc structure d_pipe

==
-fuites fd
-securiser malloc
-securiser open
-securiser pipe
-securiser signal ??
-Norminette

 ls (grep h | grep h) ne return pas derreurs
*/
