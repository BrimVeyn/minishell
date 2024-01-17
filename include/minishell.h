/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 14:09:29 by nbardavi          #+#    #+#             */
/*   Updated: 2024/01/17 16:13:34 by bvan-pae         ###   ########.fr       */
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
# include <signal.h>
# include <sys/wait.h>
# include <unistd.h>
# include <time.h>
# include <dirent.h>

#include <readline/readline.h>
#include <readline/history.h>
#include <sys/ioctl.h>

# define VIOLET "\001\e[38;2;189;147;249m\002"
# define GREEN "\001\e[38;2;80;255;125m\002"
# define WHITE "\001\e[0m\002"
# define RED "\033[38;2;255;70;100m"
# define BLUE "\e[1;34m"
#define RESET "\e[0m"
/*_.-=-._.-=-._.-=-._.-=-._.- Enum -._.-=-._.-=-._.-=-._.-=-._.-=-._*/

enum
{
	ERROR = -1,
	WRONG = 127,
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
	SQUOTE = 39,
	DQUOTE = 34,
};

enum
{
	START = 111,
	MID = 101,
	END = 222,
};

/*_.-=-._.-=-._.-=-._.-=-._.- Structs -._.-=-._.-=-._.-=-._.-=-._.-=-._*/

typedef struct s_dlist
{
	char	*str;
	int		i;
	struct	s_dlist	*prev;
	struct	s_dlist	*next;
}	t_dlist;

typedef struct s_starlist
{
	char	*str;
	int		type;
	struct	s_starlist *next;
} t_starlist;

typedef struct s_pipe
{
	int input;
	int output;
	int nbr_h;
	int or_return;
	int *p_return;
	int p_nbr;
	int p_cpt;
	int failed;
	int skip_and;
	int skip_or;
	int *fork_id;
	int pipefd[2];
	int i_f;
	int old_stdin;
	int old_stdout;
	int *heredoc;
	int p_redi_fd;
	//Pour les pipes
	int f_cpt;
	int	*f_id;
	//
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
	int		t_size;
	int 	*type;
	int		exitno;
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
	int		l;
	int		tri;
}			t_tokh;

t_h_lst		*ms_lst_new(char *content);
t_tok		parse_input(char *input, t_env *denv);
t_tok		init_tok(int tokcount);
t_tokvar	init_tokvar(char *symbol, int type);
t_tokh		init_tokh(void);
void		init_d_pipe(t_pipe *d_pipe);

/*_.-=-._.-=-._.-=-._.-=-._.- DOUBLE_LINKED_LIST -._.-=-._.-=-._.-=-._.-=-._.-=-._*/

t_dlist		*ms_dlstnew(void *str, int i);
void		ms_dlstab(t_dlist **lst, t_dlist *new);
void		ms_dlstdelone(t_dlist **lst);
void		ms_dlstdel(t_dlist *el);
void		ms_dlstclear(t_dlist **head);
void		ms_dprint(t_dlist **lst);
t_dlist		*ms_dlstmap(t_dlist **lst, char *word, void (*f)(t_dlist *, char *));
t_dlist		*ms_match_check(t_dlist *el);

/*_.-=-._.-=-._.-=-._.-=-._.--._.-=-._.--._.-=-._.-=-._.-=-._.-=-._.-=-._*/
/*_.-=-._.-=-._.-=-._.-=-._.- STAR_LIST -._.-=-._.-=-._.-=-._.-=-._.-=-._*/

t_starlist	*ms_starlnew(void *str, int i);
void		ms_starlab(t_starlist **lst, t_starlist *new);
void		ms_starclear(t_starlist **head);
t_starlist	*ms_starsplit(char *string);
char		*ms_starjoin(t_dlist **slist);

/*_.-=-._.-=-._.-=-._.-=-._.--._.-=-._.--._.-=-._.-=-._.-=-._.-=-._.-=-._*/

char		**ms_dupdup(char **environ);
char		**ms_joinstarstar(char **p1, char **p2);
char		**ft_splitm(char *str, t_tok *tdata, t_env *denv);
char		**join_tab(char **tab, char *entry);
char		*get_pwd(t_env *data);
char		*get_path(t_env *data);
char		*get_usr(t_env *data);
t_dlist		*get_flist(t_env *denv);
char		*ft_strtrimf(char const *s1, char const *set);

int			ms_isws(char c);
int			ms_tablen(char **tab);


void		init_sig();

void		prompt(t_env *env);
t_env		*update_env(t_env *denv);
void		ms_lst_b(t_h_lst **lst, t_h_lst *newlst);
void		ms_main_pipe(t_tok d_token, t_env *denv);
void		ms_add_path(t_tok *tdata, t_env *denv);

void		free_tab(char **tab);
void		free_tdata(t_tok *tdata);

#endif
