/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_strstrchr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:46:35 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/18 15:47:00 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ms_strstrchr(char c, char *charset)
{
	int	i;

	i = -1;
	while(charset[++i])
		if (c == charset[i])
			return (ERROR);
	return (TRUE);
}
