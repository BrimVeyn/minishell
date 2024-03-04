/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 10:40:47 by nbardavi          #+#    #+#             */
/*   Updated: 2024/02/28 10:48:47 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <signal.h>


void		ctrl_heredoc(int sig_num);
void		signal_ctrl(void);

char	*h_create_file(t_pipe *d_pipe)
{
	char	*f_name;

	f_name = ft_sprintf("%fs%d", ".temp_heredoc", d_pipe->nbr_h++);
	d_pipe->heredoc = open(f_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	return (f_name);
}

char	*h_redo(t_pipe *d_pipe, t_tok *tdata, char *limiter)
{
	char	*save;
	char	*temp;

	save = ft_strdup("");
	while (tdata->heredoc && tdata->heredoc[d_pipe->h_i])
	{
		if (ft_strcmp(tdata->heredoc[d_pipe->h_i], limiter) == 0)
		{
			d_pipe->h_trigger = 1;
			break ;
		}
		save = ft_sprintf("%s%fs\n", save, tdata->heredoc[d_pipe->h_i++]);
	}
	temp = ft_strdup(save);
	free(save);
	save = h_exec(d_pipe, temp, limiter);
	return (save);
}

int get_h_cpt(int trigger)
{
	static int h_cpt;

	if (trigger == 1)
		h_cpt = 0;
	else if (trigger == 0)
		h_cpt++;
	return (h_cpt);
}

extern int g_signal;

char	*h_exec(t_pipe *d_pipe, char *save, char *limiter)
{
	char	*input;
	
	signal(SIGINT, ctrl_heredoc);
	while (d_pipe->h_trigger != 1)
	{
		get_h_cpt(0);
		input = readline("> ");
		if (g_signal == 2)
			return (free(save), NULL);
		if (input == NULL)
		{
			fd_printf(2, "minishell:");
			fd_printf(2, "warning: here-document at line %d ", get_h_cpt(2));
			fd_printf(2, "delimited by end-of-file (wanted '%fs')\n", limiter);
			free(save);
			return (NULL);
		}
		if (ft_strcmp(limiter, input) == 0)
			break ;
		save = ft_sprintf("%s%s\n", save, input);
	}
	return (save);
}

void	cut_here(t_tok *tdata, int *i)
{
	char	**new;
	int		j;
	int		k;
	int		l;
	int		t;

	if (ms_setint(&k, 0), ms_setint(&l, 0), ms_setint(&j, 0), ms_setint(&t, 0),
		1)
		(void)l;
	while (tdata->tokens[*i][l] != NULL)
		l++;
	new = ft_calloc(l, sizeof(char *));
	while (tdata->tokens[*i][j] != NULL && j < l)
	{
		if (ft_strcmp(tdata->tokens[*i][j], "<<") == 0 && t == 0)
		{
			j += 1;
			t = 1;
		}
		if (j >= l)
			break ;
		new[k++] = ft_strdup(tdata->tokens[*i][j++]);
	}
	free_tab(tdata->tokens[*i]);
	tdata->tokens[*i] = new;
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
