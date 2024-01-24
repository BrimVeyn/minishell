/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 09:35:44 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/24 11:21:30 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	b_pwd(char **args, t_env *denv)
{
	char current_directory[PATH_MAX];
	
	(void) denv;
	(void) args;
	getcwd(current_directory, sizeof(current_directory));
	ft_printf("%fs\n", current_directory);
	// exit(EXIT_SUCCESS);
}
