/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 15:16:24 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/12/23 16:15:34 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int main(int ac, char *av[], char *env[])
{
	t_env data;

	(void) ac;
	(void) av;
	if (!env)
		perror("Env is null");
	data.f_env = env;
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
}
