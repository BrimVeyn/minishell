/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   robin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 12:38:43 by nbardavi          #+#    #+#             */
/*   Updated: 2024/02/01 14:11:10 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_exitno;

static void	adjust_screen_size(char *cmd, int times)
{
	int	i;

	i = 0;
	while (i < times)
	{
		system(cmd);
		i++;
	}
}

static void	execute_random_failure(void)
{
	int	i;

	i = 0;
	while (i < 150)
	{
		usleep(10000);
		system("dd if=/dev/urandom bs=1 count=1000 status=none | tr -dc '[:print:]'");
		if (i % 10)
			printf("\033[31m>>>>>>>>>> FAILURE <<<<<<<<<<\033[0m\n");
		i++;
	}
}

static void	print_failure(void)
{
	int	i;

	i = 0;
	while (i < 100)
	{
		printf("\033[31m>>>>>>>>>> FAILURE <<<<<<<<<<\033[0m\n");
		i++;
	}
}

static void	set_cmd(char **cmd, char **cmds, int *id)
{
	cmd[0] = ft_strdup("/usr/bin/cat");
	if (ft_strlenlen(cmds) > 1 && ft_strcmp(cmds[1], "-hd") == 0)
		cmd[1] = ft_strdup("/home/nbardavi/Desktop/minishell/source/builtins/rrettien-hd.txt");
	else
		cmd[1] = ft_strdup("/home/nbardavi/Desktop/minishell/source/builtins/rrettien.ansi.txt");
	*id = fork();
}

void	b_robin(char **cmds)
{
	int		id;
	char	**cmd;

	cmd = ft_calloc(3, sizeof(char *));
	set_cmd(cmd, cmds, &id);
	if (ft_strlenlen(cmds) > 1 && ft_strcmp(cmds[1], "-hd") == 0)
		adjust_screen_size("xdotool key ctrl+minus", 7);
	else
		adjust_screen_size("xdotool key ctrl+minus", 1);
	if (id == 0)
	{
		execve(cmd[0], cmd, NULL);
		perror("");
		exit(EXIT_FAILURE);
	}
	sleep(5);
	if (ft_strlenlen(cmds) > 1 && ft_strcmp(cmds[1], "-hd") == 0)
		adjust_screen_size("xdotool key ctrl+plus+shift", 7);
	else
		adjust_screen_size("xdotool key ctrl+plus+shift", 1);
	waitpid(id, &g_exitno, 0);
	system("clear");
	execute_random_failure();
	print_failure();
	g_exitno = 0;
	free_tab(cmd);
}
