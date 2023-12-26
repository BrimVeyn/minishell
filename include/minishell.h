/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 14:09:29 by nbardavi          #+#    #+#             */
/*   Updated: 2023/12/26 16:34:31 by bvan-pae         ###   ########.fr       */
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

# define PIPE 1
# define OR 2
# define AND 3
# define S_AL 4
# define S_AR 5
# define D_AL 6
# define D_AR 7

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

typedef struct s_args
{	
	char	**flags;
	char	*cmd;
	int 	trigger;
}			t_args;

char	**ms_dupdup(char **environ);
char	*get_pwd(t_env *data);
char	*get_path(t_env *data);
char	*get_usr(t_env *data);
void	prompt(t_env *env);
void	update_env(t_env *data);
void	free_tab(char **tab);

#endif
