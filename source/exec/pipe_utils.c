/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:10:04 by nbardavi          #+#    #+#             */
/*   Updated: 2024/02/05 12:19:32 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//REMOVE WRONG DES OPES, bug possible

int	next_ope(t_tok *d_token, int i)
{
	i++;
	while (i < d_token->t_size)
	{
		if (d_token->type[i][0] == AND)
			return (AND);
		if (d_token->type[i][0] == PIPE)
			return (PIPE);
		else if (d_token->type[i][0] == OR)
			return (OR);
		i++;
	}
	return (-42);
}

int	previous_ope(t_tok *d_token, int i)
{
	i--;
	while (i >= 0)
	{
		if (d_token->type[i][0] == AND)
			return (AND);
		else if (d_token->type[i][0] == PIPE)
			return (PIPE);
		else if (d_token->type[i][0] == OR)
			return (OR);
		i--;
	}
	return (-42);
}
