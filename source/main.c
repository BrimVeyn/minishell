/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 15:16:24 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/12/26 15:21:44 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void free_env(t_env *env)
{
	free(env->usr);
	free(env->path);
	free(env->pwd);
}

int main(int ac, char *av[], char *env[])
{
	t_env data;
	
	(void) av;
	if (!env || ac >= 2)
		perror("Env is null");
	data.f_env = ms_dupdup(env);
	data.pwd = get_pwd(&data);
	data.path = get_path(&data);
	data.usr = get_usr(&data);
	// printf("%s\n", data.pwd);
	// printf("%s\n", data.path);
	// printf("%s\n", data.usr);
	char *c_line = "\"";
	// for (int i = 0; c_line[i]; i++)
	// 	printf("%d\n", c_line[i]);
	prompt(&data);
	free_env(&data);
}
