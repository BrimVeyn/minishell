/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 10:13:33 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/22 15:56:49 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_tokvar init_tokvar(char *symbol, int type)
{
	t_tokvar self;

	self.type = type;
	self.len = ft_strlen(symbol);
	self.str = symbol;
	return (self);
}

t_tokh init_tokh(void)
{
	t_tokh self;
	
	self.i = 0;
	self.j = 0;
	self.k = 0;
	self.tri = 0;
	return (self);
}

t_tok init_tok(int tokcount)
{
	t_tok self;

	self.tokens = (char ***) ft_calloc(tokcount + 1, sizeof(char **));
	self.type = (int *) ft_calloc(tokcount + 1, sizeof(int));
	self.t_size = tokcount;
	return(self);
}

void init_d_pipe(t_pipe *d_pipe)
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
	d_pipe->old_stdin = dup(STDIN_FILENO);
	d_pipe->old_stdout = dup(STDOUT_FILENO);
	// d_pipe->heredoc = ft_calloc(1000, sizeof(int)); //TEMPORAIRE
	d_pipe->fork_id = ft_calloc(1000, sizeof(int)); //TEMPORAIRE
	d_pipe->f_id = ft_calloc(1000, sizeof(int)); //TEMPORAIRE
}
