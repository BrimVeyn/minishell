/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 15:16:24 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/02/01 15:01:18 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_exitno;

int	main(int ac, char *av[], char *env[])
{
	t_env	denv;

	(void) av;
	if (!env || ac >= 2)
		perror("Env is null");
	denv.f_env = ms_dupdup(env);
	denv.pwd = get_pwd(&denv);
	denv.path = get_path(&denv);
	denv.usr = get_usr(&denv);
	denv.history = NULL;
	denv.debug = 0;
	if (ac > 1 && ft_strcmp(av[1], "-d") == 0)
		denv.debug = 1;
	prompt(&denv, 0);
	exit(g_exitno);
}
