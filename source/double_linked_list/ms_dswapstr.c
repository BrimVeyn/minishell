/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_dswapstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 12:01:00 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/18 12:01:10 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ms_dswapstr(t_dlist *current, t_dlist *next)
{
	char	*tmp;

	tmp = ft_strdup(next->str);
	free(next->str);
	next->str = ft_strdup(current->str);
	free(current->str);
	current->str = tmp;
}
