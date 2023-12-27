/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 15:06:31 by nbardavi          #+#    #+#             */
/*   Updated: 2023/12/27 17:11:39 by bvan-pae         ###   ########.fr       */
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
	ft_printf("content: %s", lst->content);
	while(lst->next != NULL)
	{
		lst = lst->next;
	}
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
	lst = lst->next;
}

void heredoc(t_pipe *d_pipe, char *limiter, t_env *denv)
{
	char	*input;
	char	*save;

	d_pipe->input = open(".temp_heredoc", O_WRONLY | O_CREAT);
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
	write(d_pipe->input, save, ft_strlen(save));
	add_history(save);
}

void set_input(t_tok *d_token, t_pipe *d_pipe, t_env *denv)
{
	//TEMPORAIRE
	// char **temp;
	//
	//
	// if (ft_strcmp("make", d_token->tokens[0][0]) == 0)
	// {
	// 	temp = ft_calloc(3, sizeof(char *));
	// 	temp[0] = ft_strdup("/chemin/vers/make");
	// 	temp[2] = NULL;
	//
	// 	execve(temp[0], temp, denv->f_env);
	// }
	if (d_token->type[0] == S_AL)
	{
		d_pipe->input = open(d_token->tokens[0][0], O_RDONLY);
	}
	if (d_token->type[0] == D_AL)
	{
		heredoc(d_pipe, d_token->tokens[1][0], denv); //HEREDOC PAS FORCEMENT AU DEBUT
	}
}

void ms_main_pipe(t_tok d_token, t_env *denv)
{
	int i;
	t_pipe d_pipe;
	
	set_input(&d_token, &d_pipe, denv);
	// while()
	// {
	//
	// }
	// set_output();
}

