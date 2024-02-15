/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 11:26:10 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/02/15 10:10:21 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_startab(char ***tokens, int **type)
{
	int	i;
	int	j;

	i = 0;
	if (!tokens)
		return ;
	while (tokens[i])
	{
		j = 0;
		while (tokens[i][j])
		{
			free(tokens[i][j]);
			j++;
		}
		free(tokens[i]);
		free(type[i]);
		i++;
	}
	free(type);
	free(tokens);
}

void	free_tdata(t_tok *tdata)
{
	free_startab(tdata->tokens, tdata->type);
	free_tab(tdata->heredoc);
}

void	free_copy(char ***tokens)
{
	int	i;
	int	j;

	i = 0;
	if (!tokens)
		return ;
	while (tokens[i])
	{
		j = 0;
		while (tokens[i][j])
		{
			free(tokens[i][j]);
			j++;
		}
		free(tokens[i]);
		i++;
	}
	free(tokens);
}
