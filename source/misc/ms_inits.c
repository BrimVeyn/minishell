/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_inits.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 14:42:22 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/02/08 16:11:42 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_tokvar	init_tokvar(char *symbol, int type)
{
	t_tokvar	self;

	self.type = type;
	self.len = ft_strlen(symbol);
	self.str = symbol;
	return (self);
}

t_tokh	init_tokh(void)
{
	t_tokh	self;

	self.i = 0;
	self.j = 0;
	self.k = 0;
	self.tri = 0;
	self.quotes[0] = 0;
	self.quotes[1] = 0;
	return (self);
}

t_tok	init_tok(int tokcount, char **heredoc)
{
	t_tok	self;

	self.tokens = (char ***)ft_calloc(tokcount + 1, sizeof(char **));
	self.type = (int **)ft_calloc(tokcount + 1, sizeof(int *));
	self.t_size = tokcount;
	self.heredoc = heredoc;
	return (self);
}

void	init_d_pipe(t_pipe *d_pipe)
{
	d_pipe->input = -1;
	d_pipe->output = -1;
	d_pipe->skip_and = 0;
	d_pipe->failed = 0;
	d_pipe->skip_or = 0;
	d_pipe->or_return = 0;
	d_pipe->p_nbr = 0;
	d_pipe->p_return = 0;
	d_pipe->p_cpt = -1;
	d_pipe->nbr_h = 0;
	d_pipe->p_trig = 0;
	d_pipe->h_i = 0;
	d_pipe->t_exit = 0;
	d_pipe->b_pipefd[0] = -1;
	d_pipe->b_pipefd[1] = -1;
	d_pipe->cpt_wait = 0;
	d_pipe->file_name = NULL;
	d_pipe->failure = 0;
	d_pipe->redi_o = 0;
	d_pipe->old_stdin = dup(STDIN_FILENO);
	d_pipe->old_stdout = dup(STDOUT_FILENO);
	d_pipe->fork_id = ft_calloc(1000, sizeof(int));
	d_pipe->f_id = ft_calloc(1000, sizeof(int));
	d_pipe->tab_wait = ft_calloc(1000, sizeof(int));
}
