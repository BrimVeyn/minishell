/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 16:11:18 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/12/23 19:14:57 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <readline/readline.h>

char *get_time(void)
{
	time_t current_time;
	struct tm *timeinfo;
	char *time_char;

	time(&current_time);
	timeinfo = localtime(&current_time);
	time_char = ft_sprintf("%s[%02d:%02d] ", VIOLET, timeinfo->tm_hour, timeinfo->tm_min);
	return(time_char);
}

char *ms_form_prompt(t_env *env)
{
	char	*prompt;
	char	*full_home;

	full_home = ft_strjoin_free(ft_strdup("/home/"), env->usr);
	if (ft_strncmp(env->pwd, full_home, ft_strlen(full_home)) == 0)
		full_home = ft_sprintf("~%s", ft_substr(env->pwd, ft_strlen(full_home), ft_strlen(env->pwd)));
	else
		full_home = ft_sprintf("%s", env->pwd);
	prompt = ft_sprintf("%s%s%s%s ❯%s" , get_time(), GREEN, full_home, VIOLET, WHITE);
	return (prompt);
}

void prompt(t_env *env)
{
	char *input;
	char *prompt;

	prompt = ms_form_prompt(env);
	while(1)
	{
		input = readline(prompt);
		if (input == NULL)
			break;
	}
	free(input);
	free(prompt);
}

// int main(void)
// {
// 	t_env *env;
//
// 	env = ft_calloc(1, sizeof(t_env));
// 	env->pwd = ft_strdup("~/Desktop/minishell");
// 	prompt(env);
// }
