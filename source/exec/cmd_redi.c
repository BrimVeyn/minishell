/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:10:36 by nbardavi          #+#    #+#             */
/*   Updated: 2024/03/04 11:54:07 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <unistd.h>



void		tprint(char ***string);

void	remove_cmd(t_tok *tdata, t_pipe *d_pipe, int *i, int *j)
{
	if ((tdata->type[*i][*j] != CMD && tdata->type[*i][*j] != BUILTIN
			&& tdata->type[*i][*j] != WRONG && tdata->type[*i][*j] != IGNORE) && !d_pipe->failure)
	{
		tdata->tokens[*i] = remove_first(tdata, tdata->type[*i][*j], *i,
				0);
	}
	else
		(*j)++;
	if ((d_pipe->temp == D_AR || d_pipe->temp == S_AR || d_pipe->temp == S_AL)
		&& !d_pipe->failure)
		tdata->tokens[*i] = remove_first(tdata, FAILE, *i, 0);
}

void	init_cmd_redi(t_pipe *d_pipe, int *j)
{
	*j = 0;
	d_pipe->t_f_redi = 0;
	d_pipe->failure = 0;
	d_pipe->tr_p = 0;
}

void	apply_cmd_r(t_tok *tdata, t_pipe *d_pipe, int *i, int *j)
{
	if (tdata->type[*i][*j] == D_AR)
		d_pipe->failure = handle_append(tdata->tokens[*i][*j + 1], d_pipe);
	else if (tdata->type[*i][*j] == S_AR)
		d_pipe->failure = handle_output(tdata->tokens[*i][*j + 1], d_pipe);
	else if (tdata->type[*i][*j] == S_AL)
		d_pipe->failure = handle_input(tdata->tokens[*i][*j + 1], d_pipe);
}

int	cmd_redi(t_tok *tdata, t_pipe *d_pipe, t_env *denv, int *i)
{
	int	j;

	init_cmd_redi(d_pipe, &j);
	while (tdata->tokens[*i][j])
	{
		d_pipe->temp = tdata->type[*i][j];
		apply_cmd_r(tdata, d_pipe, i, &j);
		if (tdata->type[*i][j] == D_AL)
			d_pipe->failure = handle_heredoc(tdata, d_pipe, denv, i);
		if (tdata->t_size > *i + 2 && (tdata->type[*i + 1][0] == P_C
			&& check_next(tdata->type[*i + 2][0]) == 1)
			&& d_pipe->tr_p == 0)
		{
			d_pipe->tr_p = 1;
			*i += 2;
			d_pipe->failure = cmd_redi(tdata, d_pipe, denv, i);
			*i -= 2;
		}
		remove_cmd(tdata, d_pipe, i, &j);
		if (d_pipe->failure)
			break ;
		if (ft_strlenlen(tdata->tokens[*i]) == 0)
			tdata->type[*i][0] = WRONG;
	}
	return (cmd_return(d_pipe, tdata));
}
