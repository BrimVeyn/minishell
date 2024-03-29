/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_var_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 11:19:26 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/02/26 11:30:02 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*r_dollarquestion(char *split, int *i, t_tok *tdata)
{
	char	*p1;
	char	*var;
	char	*p2;
	char	*tmp;

	p1 = ft_substr(split, 0, *i);
	var = ft_itoa(tdata->exitno);
	p2 = ft_substr(split, *i + 2, (ft_strlen(split) - (*i + 2)));
	*i += ft_strlen(var);
	tmp = ft_sprintf("%s%s%s", p1, var, p2);
	free(split);
	return (tmp);
}

char	*r_dollar(char *split, int *i, int start, t_env *denv)
{
	char		*p1;
	char		*var;
	char		*p2;
	char		*tmp;
	int const	end = *i;

	p1 = ft_substr(split, 0, start - 1);
	var = ms_getenv(ft_substr(split, start, end - start), denv);
	p2 = ft_substr(split, end, (ft_strlen(split) - end));
	*i = ft_strlen(split) - ft_strlen(p2) - (end - start) - 1;
	tmp = ft_sprintf("%s%s%s", p1, var, p2);
	free(split);
	return (tmp);
}

static char	*split_dollar(char *split, int *i, t_env *denv)
{
	int	start;

	start = 0;
	if (split[(*i)] == '$')
	{
		if (split[(*i) + 1])
			(*i)++;
		start = (*i);
		if (ft_isdigit(split[(*i)]) || (!ft_isalpha(split[(*i)])
				&& split[(*i)] != '_'))
			start = INT_MAX;
		else
			(*i)++;
		while (split[(*i)] && (ft_isalnum(split[(*i)]) || split[(*i)] == '_'))
			(*i)++;
		if ((*i) > start)
			split = r_dollar(split, &(*i), start, denv);
		else
			(*i)++;
	}
	return (split);
}

char	*r_env(char *split, t_env *denv, t_tok *tdata)
{
	int	i;

	i = 0;
	while (split && split[i])
	{
		if (!ft_strncmp(&split[i], "$?", 2))
			split = r_dollarquestion(split, &i, tdata);
		split = split_dollar(split, &i, denv);
		if (split[i] && split[i] != '$')
			i++;
	}
	return (split);
}
