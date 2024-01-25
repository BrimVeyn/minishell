/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:02:00 by nbardavi          #+#    #+#             */
/*   Updated: 2024/01/25 13:14:33 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void print_history(t_env *denv)
{
	t_h_lst *lst;

	lst = denv->history;
	while(lst != NULL)
	{
		ft_printf("content: %fs\n", lst->content);
		lst = lst->next;
		ft_printf("=======\n");
	}
}

void print_tokens(t_tok *d_token)
{
    for (int i = 0; d_token->tokens[i]; i++)
    {
        ft_printf("S->TYPE[%d] = %d\n", i, d_token->type[i]);
        for (int j = 0; d_token->tokens[i][j]; j++)
            ft_printf("S[%d][%d] = %fs\n", i, j, d_token->tokens[i][j]);
    }
}

void print_tok(t_tok *d_token)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(i < d_token->t_size)
	{
		while(d_token->tokens[i][j])
		{
			printf("tokens[%d][%d] = %s\n", i, j, d_token->tokens[i][j]);
			j++;
		}
		j = 0;
		i++;
	}
}
