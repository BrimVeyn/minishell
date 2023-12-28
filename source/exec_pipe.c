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

// #include "../include/minishell.h"
//
// void exec_pipe()
// {
//
// }
//
// void set_output()
// {
// }
//
// char *ms_getlast(t_env *denv)
// {
// 	t_h_lst *lst;
//
// 	lst = denv->history;
// 	while(lst->next != NULL)
// 		lst = lst->next;
// 	return (lst->content);
// }
//
// void reset_history(t_env *denv)
// {
// 	t_h_lst *lst;
//
// 	lst = denv->history;
// 	rl_clear_history();
// 	while(lst->next != NULL)
// 	{
// 		add_history(lst->content);
// 		lst = lst->next;
// 	}
// }
//
// void heredoc(t_pipe *d_pipe, char *limiter, t_env *denv)
// {
// 	char	*input;
// 	char	*save;
//
// 	d_pipe->input = open(ft_sprintf("%fs%d", ".temp_heredoc", d_pipe->nbr_h++), O_WRONLY | O_CREAT);
// 	save = ft_strdup("");
// 	while(1)
// 	{
// 		input = readline(">");
// 		if (ft_strcmp(limiter, input) == 0)
// 			break;
// 		save = ft_sprintf("%s%s\n", save, input);
// 	}
// 	save = ft_sprintf("%fs\n%s%fs", ms_getlast(denv), save, limiter);
// 	ms_lst_b(&denv->history, ms_lst_new(save));
// 	reset_history(denv);
// 	// write(d_pipe->input, save, ft_strlen(save));
// 	fd_printf(d_pipe->input, "%s",save);
// 	fd_printf(STDIN, "%s", save);
// 	add_history(save);
// }
//
// // void set_input(t_tok *d_token, t_pipe *d_pipe, t_env *denv)
// // {
// // 	//TEMPORAIRE
// // 	// char **temp;
// // 	//
// // 	//
// // 	// if (ft_strcmp("make", d_token->tokens[0][0]) == 0)
// // 	// {
// // 	// 	temp = ft_calloc(3, sizeof(char *));
// // 	// 	temp[0] = ft_strdup("/chemin/vers/make");
// // 	// 	temp[2] = NULL;
// // 	//
// // 	// 	execve(temp[0], temp, denv->f_env);
// // 	// 
// // 	if (d_token->type[0] == S_AL)
// // 	{
// // 		d_pipe->input = open(d_token->tokens[0][0], O_RDONLY);
// // 	}
// // 	if (d_token->type[0] == D_AL)
// // 	{
// // 		heredoc(d_pipe, d_token->tokens[1][0], denv); //HEREDOC PAS FORCEMENT AU DEBUT
// // 	}
// // 
//
// void exec_cmd(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i)
// {
// 	int j;
//
// 	j = 1;
// 	while(d_token->tokens[*i][j])
// 	{
// 		if (d_token->type[*i][j] == D_AL)
// 		{
// 			heredoc(d_pipe, d_token[*i][j + 1], denv);
// 			d_token[*i][j + 1] = ft_sprintf("%fs%d", ".temp_heredoc", d_pipe->nbr_h);
// 		}
// 		j++;
// 	}
// 	execve(d_token[*i][0], d_token[*i], denv->f_env);
//
// 	exit(EXIT_FAILURE);//TEMPORAIRE -> LEAKS, FONCTION SPECIAL A FAIRE
// }
//
// void parse_type(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i)
// {
// 	if (d_token->type[*i][0] == S_AL)
// 	{
// 		if (access(d->token[*i + 1][0], F_OK) != 0 && access(d->token[*i + 1][0], X_OK) != 0)
// 			exit_file();
// 		d_pipe->input = open(d->token[i + 1][0], O_RDONLY);
// 	}
// 	if (d_token->type[*i][0] == commands)
// 		exec_cmd(d_token, denv, d_pipe);
// 	//if (d_token->type[i] == )
// 	// {i
// 	// 	if (access(d->token[i + 1][0], F_OK) != 0 && access(d->token[i + 1][0], X_OK) != 0)
// 	// 		exit_file();
// 	// 	d_pipe->output = open(d->token[i + 1][0], O_WRONLY);
// 	// 
// 	if (d_token->type[*i][0] == D_AL)
// 		heredoc(d_pipe, d_token->token[i + 1][0], denv)
// }
//
// void ms_main_pipe(t_tok d_token, t_env *denv)
// {
// 	int i;
// 	t_pipe d_pipe;
//
// 	init_d_pipe(&d_pipe);
// 	parse_type(&d_token, &d_pipe, denv);
// 	// while()
// 	// {
// 	//
// 	// }
// 	// set_output();
// }
//
