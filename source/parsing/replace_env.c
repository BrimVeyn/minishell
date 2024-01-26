/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 11:19:26 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/26 11:19:45 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int exitno;

char	*r_dollarquestion(char *split, int *i)
{
	char *p1;
	char *var;
	char *p2;

	p1 = ft_substr(split, 0, *i);
	var = ft_itoa(exitno);
	p2 = ft_substr(split, *i + 2, (ft_strlen(split) - (*i + 2)));
	*i += ft_strlen(var);
	split = ft_sprintf("%s%s%s", p1, var, p2);
	return (split);
}

char *r_dollar(char *split, int *i, int start, t_env *denv)
{
	char *p1;
	char *var;
	char *p2;
	const int end = *i;

	p1 = ft_substr(split, 0, start - 1);
	var = ms_getenv(ft_substr(split, start, end - start), denv);
	// (void) denv;
	// var = getenv(ft_substr(split, start, end - start));
	p2 = ft_substr(split, end, (ft_strlen(split) - end));
	*i = ft_strlen(split) - ft_strlen(p2);
	if (!var)
		split = ft_sprintf("%s%s%s", p1, var, p2);
	else
		split = ft_sprintf("%s%fs%s", p1, var, p2);
	return (split);
}

char *r_env(char *split, t_env *denv)
{
	int	i;
	int start;

	i = 0;
	while (split[i])
	{
		if (!ft_strncmp(&split[i], "$?", 2))
			split = r_dollarquestion(split, &i);
		if (split[i] == '$')
		{
			if (split[i + 1])
				i++;
			start = i;
			
			while (split[i] && ft_isalnum(split[i]))
				i++;
			split = r_dollar(split, &i, start, denv);
		}
		if (split[i])
			i++;
	}
	return (split);
}
