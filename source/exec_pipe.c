/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:26:22 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/29 09:05:02 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int g_exitno;

void	apply_redi(t_tok *d_token, t_pipe *d_pipe,int i)
{
	int j;
	char **new;

	j = 0;
	new = ft_calloc(ft_strlenlen(d_token->tokens[i]), sizeof(char *));
	while(d_token->tokens[i][j])
	{
		if (ft_strcmp(d_token->tokens[i][j], "<") == 0)
		{
			if (access(d_token->tokens[i][j + 1], F_OK | R_OK))
				perror("minishell input:");
			if (d_pipe->input != -1)
				close(d_pipe->input);
			d_pipe->input = open(d_token->tokens[i][j + 1], O_RDONLY);
			j++;
		}
		else
			new[j] = ft_strdup(d_token->tokens[i][j]);
		j++;
	}
	free(d_token->tokens[i]);
	d_token->tokens[i] = new;
	dup2(d_pipe->input, STDIN_FILENO);
}

