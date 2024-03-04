/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_no_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:51:05 by nbardavi          #+#    #+#             */
/*   Updated: 2024/02/29 10:53:09 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

char	**ms_get_identifiers(t_env *denv)
{
	char	**lst;
	int		i;
	int		len;

	i = 0;
	len = ft_strlenlen(denv->f_env);
	lst = ft_calloc(len + 1, sizeof(char *));
	while (i < len)
	{
		lst[i] = ms_cut_at(ft_strdup(denv->f_env[i]), '=');
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
