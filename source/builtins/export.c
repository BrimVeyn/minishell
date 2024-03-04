/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 16:09:44 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/03/04 15:40:01 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**ms_get_identifiers(t_env *denv);

static int	invalid_identifier(char *identifier)
{
	int	i;

	i = 0;
	while (identifier[i])
	{
		if (i == 0 && ft_isdigit(identifier[i]))
			return (TRUE);
		if (ft_isalnum(identifier[i]) == ZERO && identifier[i] != '_'
			&& i != (int)ft_strlen(identifier))
			return (TRUE);
		i++;
	}
	return (ERROR);
}

void	b_export_helper(int *i, char **args, t_env *denv, t_tok *tdata)
{
	char	*value;
	char	*identifier;
	int		index;

	identifier = NULL;
	if (*i > 0 && args[*i])
	{
		value = ft_strchr(args[*i], '=');
		identifier = ms_cut_at(ft_strdup(args[*i]), '=');
		index = ms_var_exist(args[*i], denv);
		if (invalid_identifier(identifier) == TRUE || !ft_strncmp("",
				identifier, 2))
			return (b_export_helper2(identifier, i, tdata), free(identifier));
		if (value)
		{
			if (index == ERROR)
				denv->f_env = ms_join_tab(denv->f_env, args[*i]);
			else if (index != ERROR)
				denv->f_env = ms_replace_value(denv->f_env, index, args[*i]);
		}
	}
	free(identifier);
	(*i)++;
}

char	**ms_sort_identifiers(char **lst)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (lst[i] != NULL)
	{
		j = i + 1;
		while (lst[j])
		{
			if (ft_strcmp(lst[i], lst[j]) > 0)
			{
				temp = lst[i];
				lst[i] = lst[j];
				lst[j] = temp;
			}
			j++;
		}
		i++;
	}
	return (lst);
}

void	b_export_no_args(t_env *denv)
{
	char	**lst;
	char	*final;
	int		i;
	char	*value;

	lst = ms_get_identifiers(denv);
	lst = ms_sort_identifiers(lst);
	i = 0;
	while (lst[i])
	{
		value = ms_getenv(ft_strdup(lst[i]), denv);
		final = ft_sprintf("declare -x %fs=\"%s\"", lst[i], value);
		printf("%s\n", final);
		free(final);
		i++;
	}
}

void	b_export(char **args, t_env *denv, t_tok *tdata)
{
	int	i;

	i = 1;
	if (ms_tablen(args) == 1)
		b_export_no_args(denv);
	while (args[i])
		b_export_helper(&i, args, denv, tdata);
}
