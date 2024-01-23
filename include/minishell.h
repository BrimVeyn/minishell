/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:25:44 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/23 16:26:15 by bvan-pae         ###   ########.fr       */
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
	TRUE = 1,
	ZERO = 0,
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
	BUILTIN = 200,
	SQUOTE = 39,
	DQUOTE = 34,
};

enum
{
	START = 111,
	MID = 101,
	END = 222,
};

enum
{
	I = 0,
	J = 1,
	K = 2,
};

enum
{
	SQ = 0,
	DQ = 1,
	COUNT = 2,
	IX = 3,
	TRIGGER = 4,
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
	int heredoc;
	int p_redi_fd;
	//Pour les pipes
	int f_cpt;
	int	*f_id;
	int p_trig;
	//
	int h_i;
	int t_exit;
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
	char	**heredoc;
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
t_tok init_tok(int tokcount, char **heredoc);
t_tokvar	init_tokvar(char *symbol, int type);
t_tokh		init_tokh(void);
void		init_d_pipe(t_pipe *d_pipe);

/*_.-=-._.-=-._.-=-._.-=-._.- DOUBLE_LINKED_LIST -._.-=-._.-=-._.-=-._.-=-._.-=-._*/

t_dlist		*ms_dlstnew(void *str, int i);
t_dlist		*ms_dlstmap(t_dlist **lst, char *word, void (*f)(t_dlist *, char *));
t_dlist		*ms_match_check(t_dlist *el);
int			ms_dlstlen(t_dlist **flist);
void		ms_dlstab(t_dlist **lst, t_dlist *new);
void		ms_dlstdelone(t_dlist **lst);
void		ms_dlstdel(t_dlist *el);
void		ms_dlstclear(t_dlist **head);
void		ms_dprint(t_dlist **lst);
char		*ms_dlstjoin(t_dlist **dlist);
void		ms_matchstart(t_dlist *el, char *to_match);
void		ms_matchmid(t_dlist *el, char *to_match);
void		ms_matchend(t_dlist *el, char *to_match);
void		ms_del_hidden(t_dlist *el, char *to_match);
void		ms_dswapstr(t_dlist *current, t_dlist *next);
void		ms_dlsort(t_dlist **flist);

/*_.-=-._.-=-._.-=-._.-=-._.--._.-=-._.--._.-=-._.-=-._.-=-._.-=-._.-=-._*/
/*_.-=-._.-=-._.-=-._.-=-._.- STAR_LIST -._.-=-._.-=-._.-=-._.-=-._.-=-._*/

t_starlist	*ms_starlnew(void *str, int i);
t_starlist	*ms_starsplit(char *string);
void		ms_starlab(t_starlist **lst, t_starlist *new);
void		ms_starclear(t_starlist **head);
char		*ms_starjoin(t_starlist **slist);

/*_.-=-._.-=-._.-=-._.-=-._.--._.-=-._.--._.-=-._.-=-._.-=-._.-=-._.-=-._*/
/*_.-=-._.-=-._.-=-._.-=-._.- STRING_UTILS -._.-=-._.-=-._.-=-._.-=-._.-=-._*/

char		**ms_dupdup(char **environ);
char		**ms_joinstarstar(char **p1, char **p2);
char		**ft_splitm(char *str, t_tok *tdata, t_env *denv);
char		**ms_join_tab(char **tab, char *str);
char		*get_pwd(t_env *data);
char		*get_path(t_env *data);
char		*get_usr(t_env *data);
t_dlist		*get_flist(t_env *denv);
char		*ft_strtrimf(char const *s1, char const *set);
void		free_startab(char ***tokens);

int			ms_isws(char c);
int			ms_tablen(char **tab);
int			ms_strstrchr(char c, char *charset);
int			ms_findstar(char *word);
char		*ms_strtolower(char *str);
char		*ms_cut_at(char *input, char c);
char		*ms_getenv(char *var, t_env *denv);


int ft_strlenlen(char **str);
/*_.-=-._.-=-._.-=-._.-=-._.- MISC -._.-=-._.-=-._.-=-._.-=-._.-=-._*/

void ms_setint(int *i, int value);
void ms_setchar(char *c, int value);

/*_.-=-._.-=-._.-=-._.-=-._.--._.-=-._.--._.-=-._.-=-._.-=-._.-=-._.-=-._*/
/*_.-=-._.-=-._.-=-._.-=-._.- BUILTIN -._.-=-._.-=-._.-=-._.-=-._.-=-._*/


void	b_export(char **args, t_env *denv);
void	b_unset(char **args, t_env *denv);
int		var_exist(char *var, t_env *denv);
void	b_env(t_env *denv);
void	b_exit(t_pipe *d_pipe, char **args);

/*_.-=-._.-=-._.-=-._.-=-._.--._.-=-._.--._.-=-._.-=-._.-=-._.-=-._.-=-._*/
// Pas touche
void	ms_free_env(t_env *denv);
void t_heredoc(t_tok *d_token, int *i, char *limiter);

//
void		init_sig();

void		prompt(t_env *env);
t_env		*update_env(t_env *denv);
void		ms_lst_b(t_h_lst **lst, t_h_lst *newlst);
int			ms_main_pipe(t_tok d_token, t_env *denv);
void		ms_add_path(t_tok *tdata, t_env *denv);

void		free_tab(char **tab);
void		free_tdata(t_tok *tdata);

#endif
