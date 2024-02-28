/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 16:09:44 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/02/28 11:47:04 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

void	b_export_helper2(char *identifier, int *i, t_tok *tdata)
{
	fd_printf(2, "minishell: export: `%fs': not a valid identifier\n",
		identifier);
	tdata->exitno = 1 << 8;
	(*i)++;
	return ;
}

int	handle_plus(char *str, char *value, t_env *denv)
{
	int index;
	char *temp;

	temp = ms_cut_at(ft_strdup(str), '+');
	index = ms_var_exist(temp, denv);
	if (index != ERROR)
	{
		denv->f_env[index] = ft_sprintf("%s%t1fs", denv->f_env[index], value);
		return (1);
	}
	else
		return(0);
}

int		check_plus(char *str)
{
	int	i;
	int	trigger;

	i = 0;
	trigger = 0;
	while(str[i])
	{
		if (str[i] == '=' && str[i - 1] == '+' && trigger == 0)
			return(1);
		if (str[i] == '=')
			trigger = 1;
		i++;
	}
	return(0);
}

char *remove_plus(char *str)
{
	int		i;
	int		j;
	int		trigger;
	char	*new;

	i = 0;
	j = 0;
	trigger = 0;
	new = ft_calloc(ft_strlen(str), sizeof(char));
	while(str[i])
	{
		if (str[i] == '+' && trigger == 0)
		{
			i++;
			trigger = 1;
		}
		new[j++] = str[i++];
	}
	free(str);
	return (new);
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
		if (check_plus(args[*i]) == 1 && handle_plus(args[*i], value, denv) == 1)
		{
			(*i)++;
			return;
		}
		if (check_plus(args[*i]) == 1)
			args[*i] = remove_plus(args[*i]);
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
	while(lst[i] != NULL)
	{
		j = i + 1;
		while(lst[j])
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
	char **lst;
	int i;
	int	len;

	i = 0;
	len = ft_strlenlen(denv->f_env);
	lst = ft_calloc(len + 1, sizeof(char*));
	while(i < len)
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
		final = ft_sprintf("declare -x %fs=\"%s\"" , lst[i], value);
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
