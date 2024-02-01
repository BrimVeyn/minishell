/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   robin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 12:38:43 by nbardavi          #+#    #+#             */
/*   Updated: 2024/01/31 14:22:36 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_exitno;

void	b_robin(char **cmds)
{
	int		id;
	char	**cmd;

	cmd = ft_calloc(3, sizeof(char *));
	cmd[0] = ft_strdup("/usr/bin/cat");
	if (ft_strlenlen(cmds) > 1 && ft_strcmp(cmds[1], "-hd") == 0) 
	{
		for (int i=0;i < 7; i++)
			system("xdotool key ctrl+minus");
        cmd[1] = ft_strdup("/home/nbardavi/Desktop/minishell/source/builtins/rrettien-hd.txt");
	}
	else
	{
		system("xdotool key ctrl+minus");
		cmd[1] = ft_strdup("/home/nbardavi/Desktop/minishell/source/builtins/rrettien.ansi.txt");
	}
	id = fork();
	if (id == 0)
	{
		execve(cmd[0], cmd, NULL);
		perror("");
		exit(EXIT_FAILURE);
	}
	sleep(5);
	if (ft_strlenlen(cmds) > 1 && ft_strcmp(cmds[1], "-hd") == 0) 
	{
		for (int i=0;i < 7; i++)
			system("xdotool key ctrl+plus+shift");
	}
	else
	{
		system("xdotool key ctrl+plus+shift");
	}
	waitpid(id, &g_exitno, 0);
	system("clear");
	for (int i=0;i < 150; i++)
	{
		usleep(10000);
		system("dd if=/dev/urandom bs=1 count=1000 status=none | tr -dc '[:print:]'");
		if (i % 10)
			printf("\033[31m>>>>>>>>>> FAILURE <<<<<<<<<<\033[0m\n");
	}
	for (int i=0;i < 100; i++)
		printf("\033[31m>>>>>>>>>> FAILURE <<<<<<<<<<\033[0m\n");
	g_exitno = 0;
	free_tab(cmd);
}
