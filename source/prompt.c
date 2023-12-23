/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 14:17:38 by nbardavi          #+#    #+#             */
/*   Updated: 2023/12/23 15:23:18 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <readline/readline.h>

char *ms_form_prompt(t_env *env)
{
	char *prompt;
	
	prompt = ft_strjoin(ft_strjoin(ft_strdup("\033[38;2;80;255;125m" ), env->pwd), ft_strdup(" \033[38;2;189;147;249m ❯ \033[0m"));
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
