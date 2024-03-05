/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_plus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:50:05 by nbardavi          #+#    #+#             */
/*   Updated: 2024/03/05 09:38:13 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		handle_plus(char *str, char *value, t_env *denv);
int		check_plus(char *str);
char	*remove_plus(char *str);

int	hp(char *str, char *value, t_env *denv)
{
	int		index;
	char	*temp;

	temp = ms_cut_at(ft_strdup(str), '+');
	index = ms_var_exist(temp, denv);
	free(temp);
	if (index != ERROR)
	{
		denv->f_env[index] = ft_sprintf("%s%t1fs", denv->f_env[index], value);
		return (1);
	}
	else
		return (0);
}

int	cp(char *str)
{
	int	i;
	int	trigger;

	i = 0;
	trigger = 0;
	while (str[i])
	{
		if (str[i] == '=' && str[i - 1] == '+' && trigger == 0)
			return (1);
		if (str[i] == '=')
			trigger = 1;
		i++;
	}
	return (0);
}

char	*remove_plus(char *str)
{
	int		i;
	int		j;
	int		trigger;
	char	*new;

	i = 0;
	j = 0;
	trigger = 0;
	new = ft_calloc(ft_strlen(str), sizeof(char));
	while (str[i])
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
