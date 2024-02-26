/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 10:35:07 by nbardavi          #+#    #+#             */
/*   Updated: 2024/02/26 11:49:35 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <unistd.h>



int	cmd_return(t_pipe *d_pipe, t_tok *tdata)
{
	if (d_pipe->failure)
		return (r_parse_error(d_pipe, tdata), 1);
	if (d_pipe->input != -1)
	{
		dup2(d_pipe->input, STDIN_FILENO);
		close(d_pipe->input);
	}
	return (0);
}

int	count_cmd(char **string, int *type)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (string[i])
	{
		if (type[i] == CMD || type[i] == BUILTIN)
			len++;
		i++;
	}
	return (len);
}

char	**remove_first(t_tok *dt, int skip_type, int c, int i)
{
	int		j;
	int		skipped;
	char	**new;
	int		*new_type;

	j = 0;
	skipped = 0;
	new_type = ft_calloc(ft_strlenlen(dt->tokens[c]), sizeof(int));
	new = ft_calloc(ft_strlenlen(dt->tokens[c]), sizeof(char *));
	while (dt->tokens[c][i])
	{
		if (dt->type[c][i] != skip_type || skipped)
		{
			new[j] = ft_strdup(dt->tokens[c][i]);
			new_type[j++] = dt->type[c][i];
		}
		else
			skipped = 1;
		i++;
	}
	free_tab(dt->tokens[c]);
	free(dt->type[c]);
	dt->tokens[c] = new;
	dt->type[c] = new_type;
	return (new);
}

void	tprint(char ***string)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (string[i])
	{
		while (string[i][j])
		{
			fd_printf(2, "tokens[%d][%d] : %fs\n", i, j, string[i][j]);
			j++;
		}
		fd_printf(2, "\n");
		j = 0;
		i++;
	}
}

int	check_next(int signe)
{
	if (signe == S_AR || signe == D_AR || signe == S_AL || signe == D_AL)
		return (1);
	return (0);
}
