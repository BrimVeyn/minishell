/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 09:35:44 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/29 14:33:11 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_exitno;

void	b_pwd(char **args, t_env *denv)
{
	char	current_directory[PATH_MAX];

	(void)denv;
	(void)args;
	getcwd(current_directory, sizeof(current_directory));
	printf("%s\n", current_directory);
	g_exitno = 0;
}
