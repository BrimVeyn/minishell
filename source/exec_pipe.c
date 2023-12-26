/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 15:06:31 by nbardavi          #+#    #+#             */
/*   Updated: 2023/12/26 16:34:31 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void exec_pipe()
{

}

void set_output()
{

}

void set_input(t_args *arg)
{
	if (args->trigger = S_AL)
	{
		dup2(); //INPUT
	}
	if (args->trigger = D_AL)
	{
		heredoc();
	}
}

void ms_main_pipe(t_args **args)
{
	int i;
	
	set_input(args[0]);
	while()
	{

	}
	set_output();
}
