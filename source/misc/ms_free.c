/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 11:26:10 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/26 11:32:35 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

// typedef struct s_tok
// {
// 	char	***tokens;
// 	int		t_size;
// 	int 	*type;
// 	int		exitno;
// }			t_tok;

void	free_startab(char ***tokens)
{
	int	i;
	int	j;

	i = 0;
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

void	free_tdata(t_tok *tdata)
{
	free_startab(tdata->tokens);
	// free_tab(tdata->heredoc);
	free(tdata->type);
}