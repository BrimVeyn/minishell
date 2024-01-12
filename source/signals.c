/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:28:08 by nbardavi          #+#    #+#             */
/*   Updated: 2024/01/11 16:31:53 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <term.h>

extern int exitno;

void sigint_handler(int sig_num)
{
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void signal_ctrl()
{
	signal(SIGINT, sigint_handler);
}

void init_sig()
{
    struct sigaction sa;

    sa.sa_handler = sigint_handler;   // Spécifiez le gestionnaire de signal
    sigemptyset(&sa.sa_mask);         // Initialise l'ensemble des signaux bloqués
    sa.sa_flags = 0;
    if (sigaction(SIGINT, &sa, NULL) == -1) 
	{
        perror("sigaction");
        exit(1);
	}
}
