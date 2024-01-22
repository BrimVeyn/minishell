/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cut_at.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 14:50:40 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/22 14:50:59 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char *ms_cut_at(char *input, char c)
{
	int	i;
	char *new;

	i = 0;
	while (input[i] && input[i] != c)
		i++;
	new = ft_substr(input, 0, i);
	free(input);
	return (new);
}
