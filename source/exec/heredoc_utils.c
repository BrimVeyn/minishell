/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 10:40:47 by nbardavi          #+#    #+#             */
/*   Updated: 2024/02/09 10:39:51 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <signal.h>

extern int	g_exitno;
void		ctrl_heredoc(int sig_num);
void		signal_ctrl(void);

char	*h_create_file(t_pipe *d_pipe)
{
	char	*f_name;

	f_name = ft_sprintf("%fs%d", ".temp_heredoc", d_pipe->nbr_h++);
	d_pipe->heredoc = open(f_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	return (f_name);
}

char	*h_redo(t_pipe *d_pipe, t_tok *d_token, char *limiter)
{
	char	*save;
	char	*temp;

	save = ft_strdup("");
	while (d_token->heredoc && d_token->heredoc[d_pipe->h_i])
	{
		if (ft_strcmp(d_token->heredoc[d_pipe->h_i], limiter) == 0)
		{
			d_pipe->h_trigger = 1;
			break ;
		}
		save = ft_sprintf("%s%fs\n", save, d_token->heredoc[d_pipe->h_i++]);
	}
	temp = ft_strdup(save);
	free(save);
	save = h_exec(d_pipe, temp, limiter);
	return (save);
}

char	*h_exec(t_pipe *d_pipe, char *save, char *limiter)
{
	char	*input;

	signal(SIGINT, ctrl_heredoc);
	while (d_pipe->h_trigger != 1)
	{
		input = readline("> ");
		if (g_exitno == 130)
		{
			signal_ctrl();
			return (NULL);
		}
		if (input == NULL)
		{
			fd_printf(2, "minishell:");
			fd_printf(2, "warning: here-document at line %d ", d_pipe->h_cpt);
			fd_printf(2, "delimited by end-of-file (wanted '%fs')\n", limiter);
			free(save);
			return (NULL);
		}
		if (ft_strcmp(limiter, input) == 0)
			break ;
		d_pipe->h_cpt++;
		save = ft_sprintf("%s%s\n", save, input);
	}
	return (save);
}

void	cut_here(t_tok *d_token, int *i)
{
	char	**new;
	int		j;
	int		k;
	int		l;
	int		t;

	if (ms_setint(&k, 0), ms_setint(&l, 0), ms_setint(&j, 0), ms_setint(&t, 0),
		1)
		(void)l;
	while (d_token->tokens[*i][l] != NULL)
		l++;
	new = ft_calloc(l, sizeof(char *));
	while (d_token->tokens[*i][j] != NULL && j < l)
	{
		if (ft_strcmp(d_token->tokens[*i][j], "<<") == 0 && t == 0)
		{
			j += 1;
			t = 1;
		}
		if (j >= l)
			break ;
		new[k++] = ft_strdup(d_token->tokens[*i][j++]);
	}
	free_tab(d_token->tokens[*i]);
	d_token->tokens[*i] = new;
}

int	check_here(char ***tokens, int i)
{
	int	j;

	j = 0;
	while (tokens[i][j])
	{
		if (ft_strcmp(tokens[i][j], "<<") == 0)
			return (j);
		j++;
	}
	return (-1);
}
