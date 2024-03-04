/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:25:22 by nbardavi          #+#    #+#             */
/*   Updated: 2024/03/04 15:40:00 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	b_export_helper2(char *identifier, int *i, t_tok *tdata);

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

void	b_export_helper2(char *identifier, int *i, t_tok *tdata)
{
	fd_printf(2, "minishell: export: `%fs': not a valid identifier\n",
		identifier);
	tdata->exitno = 1 << 8;
	(*i)++;
	return ;
}
