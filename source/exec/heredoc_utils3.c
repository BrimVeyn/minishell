/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 09:42:39 by nbardavi          #+#    #+#             */
/*   Updated: 2024/02/29 09:43:03 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <signal.h>

int	get_h_cpt(int trigger)
{
	static int	h_cpt;

	if (trigger == 1)
		h_cpt = 0;
	else if (trigger == 0)
		h_cpt++;
	return (h_cpt);
}
