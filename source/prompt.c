/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 16:11:18 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/26 10:44:29 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/ioctl.h>

extern int exitno;

char	*rm_last_slash(char *path, int total_slash)
{
	int		i;
	int		cpt;
	char	*s1;
	char	*s2;

	cpt = 0;
	i = 0;
	while (cpt < total_slash - 1)
	{
		if (path[i] == '/')
			cpt++;
		i++;
	}
	s1 = ft_substr(path, 0, i);
	i++;
	while (path[i] != '/')
		i++;
	s2 = ft_substr_free(path, i, ft_strlen(path));
	path = ft_sprintf("%s..%s", s1, s2);
	return (path);
}

char	*cut_size(char *path)
{
	struct winsize	w;
	int				cpt;
	int				i;

	i = 0;
	cpt = 0;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	while (path[i])
	{
		if (path[i] == '/')
			cpt++;
		i++;
	}
	while (ft_strlen(path) > w.ws_col * 0.25 && cpt > 2)
	{
		path = rm_last_slash(path, cpt);
		cpt--;
	}
	return (path);
}

char	*get_time(void)
{
	time_t		current_time;
	struct tm	*timeinfo;
	char		*time_char;

	time(&current_time);
	timeinfo = localtime(&current_time);
	time_char = ft_sprintf("%s[%02d:%02d] ", ft_strdup(VIOLET),
			timeinfo->tm_hour, timeinfo->tm_min);
	return (time_char);
}

char	*ms_form_prompt(t_env *denv)
{
	char	*prompt;
	char	*full_home;
	char	*temp_home;

	full_home = ft_strjoin("/home/", denv->usr);
	if (ft_strncmp(denv->pwd, full_home, ft_strlen(full_home)) == 0)
		temp_home = ft_sprintf("~%s", ft_substr_free(ft_strdup(denv->pwd), ft_strlen(full_home), ft_strlen(denv->pwd)));
	else
		temp_home = ft_sprintf("%s", ft_strdup(denv->pwd));
	free(full_home);
	full_home = ft_strdup_free(temp_home);
	full_home = cut_size(full_home);
	prompt = ft_sprintf("%s%fs%s%fs ❯ %fs", get_time(), GREEN, full_home, VIOLET,
			WHITE);
	return (prompt);
}

void signal_ctrl();

void	prompt(t_env *denv)
{
	char	*input;
	char	*prompt;
	int		i;
	t_tok	d_token;

	i = 0;
	// init_sig();
	while (1)
	{
		denv = update_env(denv);
		signal_ctrl();
		prompt = ms_form_prompt(denv);
		input = readline(prompt);
		free(prompt);
		// if (exitno == 130)
		// {
		// 	d_token.exitno = exitno;
		// 	exitno = -1;
		// 	continue;
		// }
		if (input == NULL)
		{
			printf("exit\n");
			break ;
		}
		if (input && *input)
		{
			if (i == 0)
				denv->history = ms_lst_new(ft_strdup(input));
			else
				ms_lst_b(&denv->history, ms_lst_new(ft_strdup(input)));
            add_history(input);
			d_token = parse_input(input, denv);
			if (ms_main_pipe(d_token, denv) == 1)
				break;
			if (d_token.t_size != ERROR)
				free_tdata(&d_token);
		}
		i++;
		// free(input); //Ce free c'est un gros fdp
	}
	ms_free_env(denv);
	free(input);
}
