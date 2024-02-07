/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 11:21:47 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/02/07 16:42:31 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	signal_ctrl(void);

void	init_prompt(t_env **denv, char **input)
{
	char	*prompt;

	*denv = update_env(*denv);
	signal_ctrl();
	prompt = ms_form_prompt(*denv);
	*input = readline("Minishell : ");
	free(prompt);
}

void	print_t(char ***str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i][j])
		{
			printf("tok[%d][%d] %s\n", i, j, str[i][j]);
			j++;
		}
		j = 0;
		i++;
	}
}

int	prompt2(t_tok *d_token, t_env *denv)
{
	if (ms_main_pipe(*d_token, denv) == 1)
	{
		free_tdata(d_token);
		return (1);
	}
	if (d_token->t_size != ERROR)
		free_tdata(d_token);
	return (0);
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
			if (prompt2(&d_token, denv) == 1)
				break ;
		}
	}
	return (ms_free_env(denv), free(input));
}
