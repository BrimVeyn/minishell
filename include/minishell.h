/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:25:44 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/25 14:41:11 by nbardavi         ###   ########.fr       */
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
# define RESET "\e[0m"
/*_.-=-._.-=-._.-=-._.-=-._.- Enums -._.-=-._.-=-._.-=-._.-=-._.-=-._*/

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
	DIRECTORY = 1000,
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
}	t_starlist;

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
	int	t_r;
	//heredoc
	int h_cpt;
	int h_trigger;
	int h_before;
	//BUILTIN
	int b_pipefd[2];
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
t_dlist		*get_flist(t_env *denv);
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

char		**ft_splitm(char *str, t_tok *tdata, t_env *denv);
char		*get_pwd(t_env *data);
char		*get_path(t_env *data);
char		*get_usr(t_env *data);
char		*ft_strtrimf(char const *s1, char const *set);
void		free_startab(char ***tokens);

char		**ms_join_tab(char **tab, char *str);
char		**ms_dupdup(char **environ);
char		**ms_joinstarstar(char **p1, char **p2);
int			ms_isws(char c);
int			ms_tablen(char **tab);
int			ms_strstrchr(char c, char *charset);
int			ms_findstar(char *word);
char		*ms_strtolower(char *str);
char		*ms_cut_at(char *input, char c);
char		*ms_getenv(char *var, t_env *denv);
int			ft_strlenlen(char **str);


/*_.-=-._.-=-._.-=-._.-=-._.- MISC -._.-=-._.-=-._.-=-._.-=-._.-=-._*/

int			ms_filetype(char *path);
void		ms_setint(int *i, int value);
void		ms_setchar(char *c, int value);

/*_.-=-._.-=-._.-=-._.-=-._.--._.-=-._.--._.-=-._.-=-._.-=-._.-=-._.-=-._*/
/*_.-=-._.-=-._.-=-._.-=-._.- BUILTIN -._.-=-._.-=-._.-=-._.-=-._.-=-._*/


void		b_export(char **args, t_env *denv);
void		b_unset(char **args, t_env *denv);
void		b_env(t_env *denv);
void		b_exit(t_pipe *d_pipe, char **args);
void		b_pwd(char **args, t_env *denv);
void		b_cd(char **args, t_env *denv);
int			ms_var_exist(char *var, t_env *denv);
char		**ms_replace_value(char **f_env, int index, char *arg);
char		**del_var(char **f_env, int index);
char		*ms_find_var(t_env *denv, char *var);


/*_.-=-._.-=-._.-=-._.-=-._.--._.-=-._.--._.-=-._.-=-._.-=-._.-=-._.-=-._*/
/*_.-=-._.-=-._.-=-._.-=-._.- TYPE PARSE -._.-=-._.-=-._.-=-._.-=-._.-=-._*/

void handle_d_al(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i);
void handle_or(t_pipe *d_pipe);
void handle_po(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i);
void	handle_pc(t_pipe *d_pipe);
void handle_wrong(t_tok *d_token, t_pipe *d_pipe);
void handle_and(t_pipe *d_pipe);

void cmd_pipe(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i);
void cmd_here(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i);
void cmd_redi(t_tok *d_token, t_pipe *d_pipe, int *i, int j);
void cmd_reset_fd(t_pipe *d_pipe);
void handle_cmd(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i);

void	pipe_parse(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i);
void	exec_pipe(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i);
void	cmd_exec_pipe(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i);
void	handle_cmd_pipe(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i);

int previous_ope(t_tok *d_token, int i);
int next_ope(t_tok *d_token, int i);

void p_count(t_tok *d_token, t_pipe *d_pipe);

void p_redi(t_tok *d_token, t_pipe *d_pipe, int *i);
void handle_pc_paran(t_pipe *d_pipe);
void p_redi(t_tok *d_token, t_pipe *d_pipe, int *i);
void p_while(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i);

void ms_h_unlink(t_pipe *d_pipe);
void ms_place_h(t_tok *d_token, char *f_name, int i);
char *ms_getlast(t_env *denv);
void reset_history(t_env *denv);

void	print_history(t_env *denv);
void	print_tokens(t_tok *d_token);
void	print_tok(t_tok *d_token);

int ft_strlenlen(char **str);

void handle_built(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i);
void	b_redi(t_tok *d_token, t_pipe *d_pipe, int i);
void b_parse(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i);
/*_.-=-._.-=-._.-=-._.-=-._.- HEREDOC -._.-=-._.-=-._.-=-._.-=-._.-=-._*/

char *h_exec(t_pipe *d_pipe, char *save, char *limiter);
char *h_redo(t_pipe *d_pipe, t_tok *d_token, char *limiter);
char *h_handle(t_pipe *d_pipe, t_tok *d_token, t_env *denv, int *i);
char *heredoc(t_pipe *d_pipe, t_tok *d_token, t_env *denv, int *i);
void t_heredoc(t_tok *d_token, int *i, char *limiter);

char *h_create_file(t_pipe *d_pipe);
int check_here(char ***tokens, int i);
void reset_history(t_env *denv);
void ms_h_unlink(t_pipe *d_pipe);
void ms_place_h(t_tok *d_token, char *f_name, int i);
char *ms_getlast(t_env *denv);

void c_execve(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i);
/*_.-=-._.-=-._.-=-._.-=-._.- FREE && EXIT -._.-=-._.-=-._.-=-._.-=-._.-=-._*/

void ms_free_history(t_h_lst **head);
void ms_free_env(t_env *denv);
void ms_free_pipe(t_pipe *d_pipe);

/*_.-=-._.-=-._.-=-._.-=-._.--._.-=-._.--._.-=-._.-=-._.-=-._.-=-._.-=-._*/
/*_.-=-._.-=-._.-=-._.-=-._.--._.-=-._.--._.-=-._.-=-._.-=-._.-=-._.-=-._*/

void		init_sig();

void		prompt(t_env *env);
t_env		*update_env(t_env *denv);
void		ms_lst_b(t_h_lst **lst, t_h_lst *newlst);
int			ms_main_pipe(t_tok d_token, t_env *denv);
void		ms_add_path(t_tok *tdata, t_env *denv);

void		free_tab(char **tab);
void		free_tdata(t_tok *tdata);

int		check_here(char ***tokens, int i);
void	b_parse(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i);
void	b_redi(t_tok *d_token, t_pipe *d_pipe, int i);
void	p_while(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i);
void	w_exec_pipe(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i);
void	exec_cmd(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i);
void	apply_redi(t_tok *d_token, t_pipe *d_pipe,int i);
char	*h_before(t_pipe *d_pipe, t_tok *d_token, t_env *denv, int *i);
void	ms_place_h(t_tok *d_token, char *f_name, int i);
void	parse_type(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i);
int		next_ope(t_tok *d_token, int i);
int		previous_ope(t_tok *d_token, int i);

void print_tokens(t_tok *d_token);
void p_parse_type(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i);

void	cut_here(t_tok *d_token, int *i);
char *ms_getlast(t_env *denv);
void reset_history(t_env *denv);
#endif
