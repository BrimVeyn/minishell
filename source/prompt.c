/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 16:11:18 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/12/26 15:30:41 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*   Updated: 2023/12/26 15:20:12 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/ioctl.h>

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

char	*ms_form_prompt(t_env *env)
{
	char	*prompt;
	char	*full_home;
	char	*time_char;
	char	*temp_home;

	full_home = ft_strjoin("/home/", env->usr);
	if (ft_strncmp(env->pwd, full_home, ft_strlen(full_home)) == 0)
		temp_home = ft_sprintf("~%s", ft_substr_free(ft_strdup(env->pwd), ft_strlen(full_home), ft_strlen(env->pwd)));
	else
		temp_home = ft_sprintf("%s", ft_strdup(env->pwd));
	free(full_home);
	full_home = ft_strdup_free(temp_home);
	full_home = cut_size(full_home);
	prompt = ft_sprintf("%s%fs%s%fs ❯%fs", get_time(), GREEN, full_home, VIOLET,
			WHITE);
	return (prompt);
}

void	prompt(t_env *env)
{
	char	*input;
	char	*prompt;

	while (1)
	{
		update_env(env);
		prompt = ms_form_prompt(env);
		input = readline(prompt);
		free(prompt);
		if (input == NULL)
			break ;
        if (input && *input)
            add_history(input);
		free(input);
	}
	free(input);
}
