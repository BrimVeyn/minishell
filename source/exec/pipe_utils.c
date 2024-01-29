/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:10:04 by nbardavi          #+#    #+#             */
/*   Updated: 2024/01/25 13:11:54 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	next_ope(t_tok *d_token, int i)
{
	i++;
	while (i < d_token->t_size)
	{
		if (d_token->type[i] == AND)
			return (AND);
		else if (d_token->type[i] == PIPE)
			return (PIPE);
		else if (d_token->type[i] == OR)
			return (OR);
		else if (d_token->type[i] == WRONG)
			return (WRONG);
		i++;
	}
	return (-42);
}

int	previous_ope(t_tok *d_token, int i)
{
	i--;
	while (i >= 0)
	{
		if (d_token->type[i] == CMD)
			return (CMD);
		else if (d_token->type[i] == AND)
			return (AND);
		else if (d_token->type[i] == PIPE)
			return (PIPE);
		else if (d_token->type[i] == OR)
			return (OR);
		else if (d_token->type[i] == WRONG)
			return (WRONG);
		i--;
	}
	return (-42);
}
