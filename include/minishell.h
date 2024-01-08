/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 14:09:29 by nbardavi          #+#    #+#             */
/*   Updated: 2024/01/08 10:33:32 by bvan-pae         ###   ########.fr       */
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

#include <readline/readline.h>
#include <readline/history.h>
#include <sys/ioctl.h>

# define VIOLET "\001\e[38;2;189;147;249m\002"
# define GREEN "\001\e[38;2;80;255;125m\002"
# define WHITE "\001\e[0m\002"

/*_.-=-._.-=-._.-=-._.-=-._.- Enum -._.-=-._.-=-._.-=-._.-=-._.-=-._*/

enum
{
	ERROR = -1,
	CMD = 0,
	PIPE = 1,
	OR = 2,
	AND = 3,
	S_AL = 4,
	S_AR = 5,
	D_AL = 6,
	DELIMITER = 42,
	D_AR = 7,
	DOLLAR = 8,
	P_O = -10,
	P_C = 10,
	FAILE = 100, 
};

/*_.-=-._.-=-._.-=-._.-=-._.- Structs -._.-=-._.-=-._.-=-._.-=-._.-=-._*/

typedef struct s_pipe
{
	int input;
	int output;
	int nbr_h;
	int skip_and;
}			t_pipe;

typedef struct s_lst
{
	char	*name;
	void	*content;
	void	*next;
}			t_lst;

typedef struct s_h_lst
{
	char	*content;
	void	*next;
}			t_h_lst;

typedef struct s_env
{	
	t_lst	lst;
	char	**f_env;
	char	*pwd;
	char	*path;
	char	*usr;
	t_h_lst	*history;
}			t_env;

typedef struct s_tok
{	
	char	***tokens;
	int 	*type;
	int		*par;
}			t_tok;

typedef struct s_tokvar
{
	char	*str;
	int		type;
	int		len;
}			t_tokvar;

typedef struct s_tokh
{
	int		i;
	int		j;
	int		k;
	int		tri;
}			t_tokh;

t_tok		parse_input(char *input, t_env *denv);
t_tok		init_tok(int tokcount);
t_tokvar	init_tokvar(char *symbol, int type);
t_tokh		init_tokh(void);
t_h_lst		*ms_lst_new(char *content);

char		**ms_dupdup(char **environ);
char		*get_pwd(t_env *data);
char		*get_path(t_env *data);
char		*get_usr(t_env *data);
char	*ft_strtrimf(char const *s1, char const *set);

void		prompt(t_env *env);
void		update_env(t_env *data);
void		free_tab(char **tab);
void		ms_lst_b(t_h_lst **lst, t_h_lst *newlst);
void		ms_main_pipe(t_tok d_token, t_env *denv);
void		ms_add_path(t_tok *tdata, t_env *denv);

#endif
