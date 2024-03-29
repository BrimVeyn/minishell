/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 15:16:24 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/03/04 09:12:53 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_signal;
int	get_h_cpt(int trigger);

int	main(int ac, char *av[], char *env[])
{
	t_env	denv;
	t_tok	tdata;

	g_signal = 0;
	if (av && (!env || ac >= 2))
	{
		fd_printf(2, "Either env is null or too many arguments\n");
		exit(EXIT_FAILURE);
	}
	denv.f_env = ms_dupdup(env);
	get_h_cpt(1);
	denv.pwd = get_pwd(&denv);
	denv.path = get_path(&denv);
	denv.usr = get_usr(&denv);
	denv.history = NULL;
	denv.debug = 0;
	tdata.exitno = 0;
	if (ac > 1 && ft_strcmp(av[1], "-d") == 0)
		denv.debug = 1;
	prompt(&denv, &tdata, 0);
	exit(tdata.exitno);
}
