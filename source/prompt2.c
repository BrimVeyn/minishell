/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:47:51 by nbardavi          #+#    #+#             */
/*   Updated: 2024/02/01 14:49:10 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void		signal_ctrl(void);

void	init_prompt(t_env **denv, char **input)
{
	char	*prompt;

	*denv = update_env(*denv);
	signal_ctrl();
	prompt = ms_form_prompt(*denv);
	*input = readline("Minishell:");
	free(prompt);
}

void	prompt(t_env *denv, int i)
{
	char	*input;
	t_tok	d_token;

	while (init_prompt(&denv, &input), i++ > -1)
	{
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
				break ;
			if (d_token.t_size != ERROR)
				free_tdata(&d_token);
		}
	}
	return (ms_free_env(denv), free(input));
}
