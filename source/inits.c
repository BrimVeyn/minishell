/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 10:13:33 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/12/28 10:14:33 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_tokvar init_tokvar(char *symbol, int type)
{
	t_tokvar self;

	self.type = type;
	self.len = ft_strlen(symbol);
	self.str = symbol;
	return (self);
}

t_tokh init_tokh(void)
{
	t_tokh self;
	
	self.i = 0;
	self.j = 0;
	self.k = 0;
	self.tri = 0;
	return (self);
}
