/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_findstar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 12:22:39 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/18 12:22:57 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ms_findstar(char *word)
{
	int	i;

	i = -1;
	while(word[++i])
		if (word[i] == '*')
			return (TRUE);
	return (ERROR);
}
