/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 12:59:29 by nbardavi          #+#    #+#             */
/*   Updated: 2024/02/01 10:41:28 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ms_h_unlink(t_pipe *d_pipe)
{
	char	*temp;

	d_pipe->nbr_h--;
	while (d_pipe->nbr_h > -1)
	{
		temp = ft_sprintf("%fs%d", ".temp_heredoc", d_pipe->nbr_h);
		unlink(temp);
		free(temp);
		d_pipe->nbr_h--;
	}
}

void	ms_place_h(t_tok *d_token, char *f_name, int i)
{
	int		j;
	int		k;
	char	**u_char;

	j = 0;
	k = 0;
	while (d_token->tokens[i + 2][j])
		j++;
	u_char = ft_calloc(j + 2, sizeof(char *));
	j = 0;
	while (d_token->tokens[i + 2][j])
	{
		u_char[j] = ft_strdup(d_token->tokens[i + 2][j]);
		j++;
	}
	u_char[j] = ft_strdup(f_name);
	free_tab(d_token->tokens[i + 2]);
	d_token->tokens[i + 2] = u_char;
}

char	*ms_getlast(t_env *denv)
{
	t_h_lst	*lst;

	lst = denv->history;
	while (lst->next != NULL)
		lst = lst->next;
	return (lst->content);
}

void	reset_history(t_env *denv)
{
	t_h_lst	*lst;

	lst = denv->history;
	rl_clear_history();
	while (lst != NULL)
	{
		add_history(lst->content);
		lst = lst->next;
	}
}
