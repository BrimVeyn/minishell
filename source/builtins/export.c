/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 16:09:44 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/30 13:12:40 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int g_exitno;

int	ms_var_exist(char *var, t_env *denv)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = ms_cut_at(ft_strdup(var), '=');
	while (denv->f_env[i])
	{
		if (!ft_strncmp(denv->f_env[i], tmp, ft_strlen(tmp)))
			return (free(tmp), i);
		i++;
	}
	return (free(tmp), ERROR);
}

static int	invalid_identifier(char *identifier)
{
	int	i;

	i = 0;
	while (identifier[i])
	{
		if (ft_isalpha(identifier[i]) == ZERO && identifier[i] != '_' && i != (int)ft_strlen(identifier))
			return (TRUE);
		i++;
	}
	return (ERROR);
}

char	**ms_replace_value(char **f_env, int index, char *arg)
{
	char	**new;
	int		i;

	new = ft_calloc(ms_tablen(f_env) + 1, sizeof(char *));
	if (!new)
		return (NULL);
	i = 0;
	while (f_env[i] && i != index)
	{
		new[i] = ft_strdup(f_env[i]);
		i++;
	}
	if (i == index)
		new[i++] = ft_strdup(arg);
	while (f_env[i])
	{
		new[i] = ft_strdup(f_env[i]);
		i++;
	}
	return (free_tab(f_env), new);
}

void	b_export_helper(int *i, char **args, t_env *denv)
{
	char		*value;
	char	*identifier;
	int			index;

	identifier = NULL;
	if (i > 0 && args[*i])
	{
		value = ft_strchr(args[*i], '=');
		identifier = ms_cut_at(ft_strdup(args[*i]), '=');
		// ft_printf("IDENTIFIER = %fs\n", identifier);
		index = ms_var_exist(args[*i], denv);
		if (invalid_identifier(identifier) == TRUE || !ft_strncmp("", identifier, 2))
        {
			fd_printf(2, "minishell: export: `%fs': not a valid identifier\n",
				identifier);
			g_exitno = 1;
			(*i)++;
			return ;
        }
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


void	b_export(char **args, t_env *denv)
{
	int		i;

	i = 1;
	while (args[i])
		b_export_helper(&i, args, denv);
}
