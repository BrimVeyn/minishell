/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:10:36 by nbardavi          #+#    #+#             */
/*   Updated: 2024/02/09 13:01:11 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <unistd.h>

extern int	g_exitno;

void		tprint(char ***string);

void	remove_cmd(t_tok *d_token, t_pipe *d_pipe, int *i, int *j)
{
	if ((d_token->type[*i][*j] != CMD && d_token->type[*i][*j] != BUILTIN
			&& d_token->type[*i][*j] != WRONG) && !d_pipe->failure)
	{
		d_token->tokens[*i] = remove_first(d_token, d_token->type[*i][*j], *i,
				0);
	}
	else
		(*j)++;
	if ((d_pipe->temp == D_AR || d_pipe->temp == S_AR || d_pipe->temp == S_AL)
		&& !d_pipe->failure)
		d_token->tokens[*i] = remove_first(d_token, FAILE, *i, 0);
}

void	init_cmd_redi(t_pipe *d_pipe, int *j)
{
	*j = 0;
	d_pipe->t_f_redi = 0;
	d_pipe->failure = 0;
	d_pipe->tr_p = 0;
}

void	apply_cmd_r(t_tok *d_token, t_pipe *d_pipe, int *i, int *j)
{
	if (d_token->type[*i][*j] == D_AR)
		d_pipe->failure = handle_append(d_token->tokens[*i][*j + 1], d_pipe);
	else if (d_token->type[*i][*j] == S_AR)
		d_pipe->failure = handle_output(d_token->tokens[*i][*j + 1], d_pipe);
	else if (d_token->type[*i][*j] == S_AL)
		d_pipe->failure = handle_input(d_token->tokens[*i][*j + 1], d_pipe);
}

int	cmd_redi(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i)
{
	int	j;

	init_cmd_redi(d_pipe, &j);
	while (d_token->tokens[*i][j])
	{
		d_pipe->temp = d_token->type[*i][j];
		apply_cmd_r(d_token, d_pipe, i, &j);
		if (d_token->type[*i][j] == D_AL)
			d_pipe->failure = handle_heredoc(d_token, d_pipe, denv, i);
		if (d_token->t_size > *i + 2 && (d_token->type[*i + 1][0] == P_C
			&& check_next(d_token->type[*i + 2][0]) == 1)
			&& d_pipe->tr_p == 0)
		{
			d_pipe->tr_p = 1;
			*i += 2;
			d_pipe->failure = cmd_redi(d_token, d_pipe, denv, i);
			*i -= 2;
		}
		remove_cmd(d_token, d_pipe, i, &j);
		if (d_pipe->failure)
			break ;
		if (ft_strlenlen(d_token->tokens[*i]) == 0)
			d_token->type[*i][0] = WRONG;
	}
	return (cmd_return(d_pipe));
}
