/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:49:52 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/23 11:06:11 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char *ms_getenv(char *var, t_env *denv)
{
	char *new;
	char *tmp;
	int	i;

	i = 0;
	new = NULL;
	var = ft_strjoin_free(var, ft_strdup("="));
	while (denv->f_env[i])
	{
		if (!ft_strncmp(var, denv->f_env[i], ft_strlen(var)))
		{
			tmp = ft_strchr(denv->f_env[i], '=');
			new = ft_substr(tmp, 1, ft_strlen(tmp));
			// ft_printf("SALOPE = %fs\n", new);
		}
		i++;
	}
	if (!new)
		return (free(var), ft_strdup(" "));
	return (free(var), new);
}
