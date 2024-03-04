/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 11:41:47 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/02/28 09:31:14 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <term.h>
#include <unistd.h>

extern int	g_signal;

void	sigint_handler(int sig_num)
{
	(void)sig_num;
	g_signal = 2;
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ctrl_heredoc(int sig_num)
{
	(void)sig_num;
	printf("\n");
	g_signal = 2;
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
