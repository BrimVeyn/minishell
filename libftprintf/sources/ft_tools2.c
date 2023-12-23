/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbardavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:07:47 by nbardavi          #+#    #+#             */
/*   Updated: 2023/11/16 15:37:31 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_printf.h"

t_trigger	reset_struct(void)
{
	t_trigger	trigger;

	trigger.hyphen = 0;
	trigger.zero = 0;
	trigger.dot = 0;
	trigger.hash = 0;
	trigger.space = 0;
	trigger.plus = 0;
	trigger.number = 0;
	trigger.number1 = 0;
	trigger.number2 = -10;
	trigger.index = 0;
	trigger.origine = 0;
	return (trigger);
}

int	ft_instr(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
		if (c == str[i++])
			return (1);
	return (0);
}
