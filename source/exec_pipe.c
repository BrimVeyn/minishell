/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:26:22 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/24 15:31:35 by nbardavi         ###   ########.fr       */
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
extern int exitno;

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

void exec_cmd(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i)
{
	int j;
	int id;

	j = 0;
	id = fork();
	
	if (id != 0) // PROCESSUS PERE
	{
		signal(SIGINT, SIG_IGN);
		waitpid(id, &exitno ,0);
		init_sig();
		d_pipe->failed = 0;
		if (exitno != 0)
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



int next_ope(t_tok *d_token, int i)
{
	i++;
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
	int j;

	j = 0;
	d_pipe->f_cpt = 0;
	dup2(d_pipe->input, STDIN_FILENO);
	while((next_ope(d_token, *i) == PIPE || (previous_ope(d_token, *i) == PIPE && next_ope(d_token, *i) != PIPE) || d_token->type[*i] == PIPE) && d_token->t_size > *i)
	{
		pipe_parse(d_token, d_pipe, denv, i);
		d_pipe->f_cpt++;
		(*i)++;
	}
	dup2(d_pipe->old_stdin, STDIN_FILENO);
	while(d_pipe->f_cpt >= j)
	{
		waitpid(d_pipe->f_id[d_pipe->f_cpt], &d_token->exitno, 0);
		j++;
	}
	d_pipe->p_trig = 1;
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
		d_pipe.t_r = 0;
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
