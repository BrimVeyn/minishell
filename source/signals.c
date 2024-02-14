/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 11:41:47 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/02/14 16:53:15 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <term.h>
#include <unistd.h>

extern int	g_exitno;

void	sigint_spe(int sig_num)
{
	(void)sig_num;
	g_exitno = 130;
	ft_printf("\n\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigint_handler(int sig_num)
{
	(void)sig_num;
	g_exitno = 130;
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ctrl_heredoc(int sig_num)
{
	(void)sig_num;
	g_exitno = 130;
	printf("\n");
	close(STDIN_FILENO);
}

void	signal_ctrl(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_handler);
}

void	init_sig(void)
{
	signal(SIGINT, sigint_handler);
}
