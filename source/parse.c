/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 16:27:38 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/12/27 10:18:23 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ms_isws(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

//split ' ' | " " | >> | << | > | < | && | || ( ) | * |
int ms_istok(char *ptr)
{
	if (!ft_strncmp(ptr, "||", 2))
	{
		return (2);
	}
	if (!ft_strncmp(ptr, "&&", 2))
	{
		return (2);
	}
	if (!ft_strncmp(ptr, ">>", 2))
	{
		return (2);
	}
	if (!ft_strncmp(ptr, "<<", 2))
	{
		return (2);
	}
	if (!ft_strncmp(ptr, "<", 1))
	{
		return (1);
	}
	if (!ft_strncmp(ptr, ">", 1))
	{
		return (1);
	}
	if (!ft_strncmp(ptr, "$", 1))
	{
		return (1);
	}
	return (0);
}

t_tok get_tokens(char *input)
{
	t_tok d;
	return (d);
}

int count_tokens(char *input)
{
	int i;
	int count;
	int off;

	count = 0;
	i = 0;
	while (input[i])
	{
		if (ms_istok(&input[i]))
		{
			off = ms_istok(&input[i]);


		}
		i += off;
		count++;
		i++;
	}
	return (count);
}

void	parse_input(char *input)
{
	t_tok tdata;
	int tokcount;

	tokcount = count_tokens(input);
	tdata = get_tokens(input);
}





