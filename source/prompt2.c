/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 11:21:47 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/02/27 10:58:17 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	signal_ctrl(void);
extern int	g_signal;
char	*get_next_line(int fd);

void	init_prompt(t_env **denv, char **input, t_tok *tdata)
{
	char	*prompt;

	*denv = update_env(*denv);
	signal_ctrl();
	prompt = ms_form_prompt(*denv);
	*input = readline(prompt);
	if (g_signal == 2)
		tdata->exitno = 130;
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

int	prompt2(t_tok *tdata, t_env *denv)
{
	if (ms_main_pipe(tdata, denv) == 1)
	{
		free_tdata(tdata);
		return (1);
	}
	free_tdata(tdata);
	return (0);
}

void	prompt(t_env *denv, t_tok *tdata, int i)
{
	char	*input;

	while (init_prompt(&denv, &input, tdata), i++ > -1)
	{
		g_signal = 0;
		if (input == NULL)
		{
			// printf("exit\n");
			break ;
		}
		if (input && *input)
		{
			if (i == 0)
				denv->history = ms_lst_new(ft_strdup(input));
			else
				ms_lst_b(&denv->history, ms_lst_new(ft_strdup(input)));
			add_history(input);
			parse_input(input, denv, tdata);
			if (prompt2(tdata, denv) == 1)
				break ;
		}
		if (g_signal == 1)
			tdata->exitno = 130;
	}
	return (ms_free_env(denv), free(input));
}
