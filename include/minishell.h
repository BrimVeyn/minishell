/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 14:09:29 by nbardavi          #+#    #+#             */
/*   Updated: 2023/12/23 19:13:52 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*_.-=-._.-=-._.-=-._.-=-._.- Includes -._.-=-._.-=-._.-=-._.-=-._.-=-._*/

# include "../libftprintf/header/ft_printf.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# include <time.h>

#define VIOLET "\033[38;2;189;147;249m"
#define GREEN "\033[38;2;80;255;125m"
#define WHITE "\033[0m"
/*_.-=-._.-=-._.-=-._.-=-._.- Structs -._.-=-._.-=-._.-=-._.-=-._.-=-._*/

typedef struct s_lst
{
	char	*name;
	void	*content;
	void	*next;
}			t_lst;

typedef struct s_env
{	
	t_lst	lst;
	char	**f_env;
	char	*pwd;
	char	*path;
	char	*usr;
}			t_env;


void prompt(t_env *env);
char *get_pwd(t_env *data);
char *get_path(t_env *data);
char *get_usr(t_env *data);

#endif
