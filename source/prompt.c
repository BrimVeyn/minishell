/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 16:11:18 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/12/23 16:21:03 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <readline/readline.h>

char *ms_form_prompt(t_env *env)
{
	char	*prompt;
	char	*full_home;

	full_home = ft_strjoin_free(ft_strdup("/home/"), env->usr);
	if (ft_strncmp(env->pwd, full_home, ft_strlen(full_home)) == 0)
		full_home = ft_strjoin_free(ft_strdup("~"), ft_substr_free(env->pwd, ft_strlen(full_home), ft_strlen(env->pwd)));
	else
		full_home = ft_strdup(env->pwd);
	prompt = ft_strjoin_free(ft_strjoin_free(ft_strdup("\033[38;2;80;255;125m" ), full_home), ft_strdup(" \033[38;2;189;147;249m ❯ \033[0m"));
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
