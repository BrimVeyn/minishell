/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_strtolower.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 12:05:48 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/18 12:06:08 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char *ms_strtolower(char *str)
{
	char *cpy;
	int	i;

	i = -1;
	cpy = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	while (str[++i])
		cpy[i] = ft_tolower(str[i]);
	// printf("||%s||\n", cpy);
	return (cpy);
}
