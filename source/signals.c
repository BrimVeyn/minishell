/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:28:08 by nbardavi          #+#    #+#             */
/*   Updated: 2024/01/24 15:22:08 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <term.h>

extern int exitno;

void sigint_handler(int sig_num)
{
	(void) sig_num;
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void signal_ctrl()
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_handler);
}

void init_sig()
{
    signal(SIGINT, sigint_handler);
}
