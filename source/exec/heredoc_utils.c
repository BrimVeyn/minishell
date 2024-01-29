/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 10:40:47 by nbardavi          #+#    #+#             */
/*   Updated: 2024/01/29 11:03:46 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*h_create_file(t_pipe *d_pipe)
{
	char	*f_name;

	f_name = ft_sprintf("%fs%d", ".temp_heredoc", d_pipe->nbr_h++);
	d_pipe->heredoc = open(f_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	return (f_name);
}

char	*h_redo(t_pipe *d_pipe, t_tok *d_token, char *limiter)
{
	char	*save;

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
	save = h_exec(d_pipe, save, limiter);
	return (save);
}

char	*h_exec(t_pipe *d_pipe, char *save, char *limiter)
{
	char	*input;

	while (d_pipe->h_trigger != 1)
	{
		input = readline("> ");
		if (input == NULL)
		{
			printf("minishell: warning: here-document at line %d delimited by end-of-file (wanted '%s')\n", d_pipe->h_cpt,
				limiter);
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
	int		len;
	int		trigger;

	if (ms_setint(&k, 0), ms_setint(&len, 0), ms_setint(&j, 0),
		ms_setint(&trigger, 0), 1)
		(void)len;
	while (d_token->tokens[*i][len] != NULL)
		len++;
	new = ft_calloc(len, sizeof(char *));
	j = 0;
	while (d_token->tokens[*i][j] != NULL && j < len)
	{
		if (ft_strcmp(d_token->tokens[*i][j], "<<") == 0 && trigger == 0)
		{
			j += 1;
			trigger = 1;
		}
		if (j >= len)
			break ;
		new[k++] = ft_strdup(d_token->tokens[*i][j++]);
	}
	free(d_token->tokens[*i]);
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
