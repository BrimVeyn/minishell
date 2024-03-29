/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:56:55 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/03/05 13:29:27 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*_.-=-._.-=-._.-=-._.-=-._.- Includes -._.-=-._.-=-._.-=-._.-=-._.-=-._*/

# include "../libftprintf/header/ft_printf.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <time.h>
# include <unistd.h>

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
	IGNORE = 999,
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

enum
{
	TRI = 1,
	COUNTER = 2,
	DCOUNTER = 3,
};

/*_.-=-._.-=-._.-=-._.-=-._.- Structs -._.-=-._.-=-._.-=-._.-=-._.-=-._*/

typedef struct s_dlist
{
	char				*str;
	int					i;
	struct s_dlist		*prev;
	struct s_dlist		*next;
}						t_dlist;

typedef struct s_starlist
{
	char				*str;
	int					type;
	struct s_starlist	*next;
}						t_starlist;

typedef struct s_ts
{
	char				**new;
	char				**p1;
	char				**p2;
	int					xi;
	int					index;

}						t_ts;

typedef struct s_jp
{
	char				**mid;
	char				**new;
	int					*newtype;
	int					i;
	int					j;
	int					k;
	int					cp;

}						t_jp;

typedef struct s_pipe
{
	int					input;
	int					output;
	int					nbr_h;
	int					or_return ;
	int					p_return ;
	int					p_nbr;
	int					p_cpt;
	int					failed;
	int					skip_and;
	int					skip_or;
	int					*fork_id;
	int					pipefd[2];
	int					i_f;
	int					old_stdin;
	int					old_stdout;
	int					heredoc;
	int					p_redi_fd;
	int					f_cpt;
	int					*f_id;
	int					p_trig;
	int					redi;
	int					h_i;
	int					t_exit;
	int					t_r;
	int					h_cpt;
	int					h_trigger;
	int					h_before;
	int					b_pipefd[2];
	int					*tab_wait;
	int					cpt_wait;
	char				*file_name;
	int					failure;
	int					tr_p;
	int					redi_o;
	int					t_f_redi;
	int					temp;
}						t_pipe;

typedef struct s_lst
{
	char				*name;
	void				*content;
	void				*next;
}						t_lst;

typedef struct s_h_lst
{
	char				*content;
	void				*next;
}						t_h_lst;

typedef struct s_env
{
	char				**f_env;
	char				*pwd;
	char				*path;
	char				*usr;
	t_h_lst				*history;
	int					debug;
}						t_env;

typedef struct s_tokvar
{
	char				*str;
	int					type;
	int					len;
}						t_tokvar;

typedef struct s_tok
{
	char				***tokens;
	char				***tok_copy;
	int					t_size;
	int					**type;
	int					*w_pos;
	int					w_size;
	int					exitno;
	char				**heredoc;
	int					h_cpt;
	t_starlist			*strl;
}						t_tok;

typedef struct s_tokh
{
	int					i;
	int					j;
	int					k;
	int					l;
	int					tri;
	int					quotes[2];
	t_tokvar			tokvar;
}						t_tokh;

typedef struct s_splith
{
	char				***split;
	int					i;
	int					j;
	int					j_save;
	int					wc;
	int					d_value;
}						t_splith;

t_h_lst					*ms_lst_new(char *content);
void					parse_input(char *input, t_tok *tdata);
void					ms_parse(t_tok *tdata, t_env *denv, int index);
t_tok					init_tok(int tokcount, char **heredoc);
t_tokvar				init_tokvar(char *symbol, int type);
t_tokh					init_tokh(void);
void					init_d_pipe(t_pipe *d_pipe);

/*_.-=-._.-=-._.-=-._.-=-._.- DOUBLE_LINKED_LIST
	-._.-=-._.-=-._.-=-._.-=-._.-=-._*/

t_dlist					*ms_dlstnew(void *str, int i);
t_dlist					*ms_dlstmap(t_dlist **lst, char *word,
							void (*f)(t_dlist *, char *));
t_dlist					*ms_match_check(t_dlist *el);
t_dlist					*get_flist(t_env *denv);
char					*ms_dlstjoin(t_dlist **dlist);
void					ms_dlstab(t_dlist **lst, t_dlist *new);
void					ms_dlstdelone(t_dlist **lst);
void					ms_dlstdel(t_dlist *el);
void					ms_dlstclear(t_dlist **head);
void					ms_dprint(t_dlist **lst);
void					ms_matchstart(t_dlist *el, char *to_match);
void					ms_matchmid(t_dlist *el, char *to_match);
void					ms_matchend(t_dlist *el, char *to_match);
void					ms_del_hidden(t_dlist *el, char *to_match);
void					ms_dswapstr(t_dlist *current, t_dlist *next);
void					ms_dlsort(t_dlist **flist);
int						ms_dlstlen(t_dlist **flist);

/*_.-=-._.-=-._.-=-._.-=-._.--._.-=-._.--._.-=-._.-=-._.-=-._.-=-._.-=-._*/
/*_.-=-._.-=-._.-=-._.-=-._.- STAR_LIST -._.-=-._.-=-._.-=-._.-=-._.-=-._*/

t_starlist				*ms_snew(void *str, int i);
t_starlist				*ms_starsplit(char *s, t_tok *tdata);
char					*ms_starjoin(t_starlist **slist);
void					ms_sab(t_starlist **lst, t_starlist *new);
void					ms_starclear(t_starlist **head);

/*_.-=-._.-=-._.-=-._.-=-._.--._.-=-._.--._.-=-._.-=-._.-=-._.-=-._.-=-._*/
/*_.-=-._.-=-._.-=-._.-=-._.- STRING_UTILS -._.-=-._.-=-._.-=-._.-=-._.-=-._*/

char					**ft_splitm(char *str, t_env *denv);
char					*get_pwd(t_env *data);
char					*get_path(t_env *data);
char					*get_usr(t_env *data);
char					*ms_strtrimf(char const *s1, char const *set);
char					**ms_join_tab(char **tab, char *str);
char					**ms_dupdup(char **environ);
char					**ms_joinstarstar(char **p1, char **p2);
char					*ms_strtolower(char *str);
char					*ms_cut_at(char *input, char c);
char					*ms_getenv(char *var, t_env *denv);
char					**ms_joinstarstar(char **p1, char **p2);
char					**ms_replace_value(char **f_env, int index, char *arg);
int						ms_tablen(char **tab);
int						ms_isws(char c);
int						ms_tablen(char **tab);
int						ms_strstrchr(char c, char *charset);
int						ms_findstar(char *word, t_tok *tdata);

/*_.-=-._.-=-._.-=-._.-=-._.- MISC -._.-=-._.-=-._.-=-._.-=-._.-=-._*/

void					ms_setint(int *i, int value);
void					ms_setchar(char *c, int value);
void					free_startab(char ***tokens, int **type);
void					free_copy(char ***tokens);
int						ms_filetype(char *path);

/*_.-=-._.-=-._.-=-._.-=-._.--._.-=-._.--._.-=-._.-=-._.-=-._.-=-._.-=-._*/
/*_.-=-._.-=-._.-=-._.-=-._.- BUILTIN -._.-=-._.-=-._.-=-._.-=-._.-=-._*/

void					b_echo(t_tok *tdata, int *i);
void					b_export(char **args, t_env *denv, t_tok *tdata);
int						invalid_identifier(char *identifier);
void					b_export_helper2(char *identifier, int *i,
							t_tok *tdata);
void					b_unset(char **args, t_env *denv);
void					b_export_no_args(t_env *denv);
void					b_env(t_env *denv, t_tok *tdata);
char					**ms_get_identifiers(t_env *denv);
void					b_exit(char **args, t_pipe *d_pipe, t_tok *tdata);
void					b_pwd(t_tok *tdata);
void					b_cd(char **args, t_env *denv, t_tok *tdata);
void					cd_minus(t_env *denv, t_tok *tdata);
int						too_many_args(char **args, t_tok *tdata);
int						no_args(char **args, t_env *denv, t_tok *tdata);
char					**ms_replace_value(char **f_env, int index, char *arg);
char					**del_var(char **f_env, int index);
char					*ms_find_var(t_env *denv, char *var);
int						ms_var_exist(char *var, t_env *denv);

/*_.-=-._.-=-._.-=-._.-=-._.--._.-=-._.--._.-=-._.-=-._.-=-._.-=-._.-=-._*/
/*_.-=-._.-=-._.-=-._.-=-._.- PARSING -._.-=-._.-=-._.-=-._.-=-._.-=-._*/

t_tokvar				ms_tiktok(char *ptr);
t_dlist					*ms_wildcard_expand(t_starlist *current,
							t_dlist *flist);
void					fill_token(char *input, t_tok *tdata, t_env *denv);
void					ms_add_path(t_tok *tdata, t_env *denv, int index);
int						no_such_file(char *cmd, t_tok *tdata);
int						is_a_directory(char *cmd, t_tok *tdata);
void					ms_par_check(char *input, t_tok *tdata);
int						hp(char *str, char *value, t_env *denv);
int						cp(char *str);
char					*remove_plus(char *str);
int						command_not_found(char *cmd, t_tok *tdata);
int						permission_denied(char *cmd, t_tok *tdata);
int						empty_var(char *cmd);
char					*grep_word(char *input, t_tokh *v);
char					*r_dollarquestion(char *split, int *i, t_tok *tdata);
char					*r_dollar(char *split, int *i, int start, t_env *denv);
char					*r_env(char *split, t_env *denv, t_tok *tdata);
char					*ms_xt(char *split, int *j, char c);
char					*tild_expand(char *word, t_env *denv);
char					*w_expand(char *word, t_env *denv, t_tok *tdata);
char					**dupdup(void);
int						missing_delimiter_check(t_tok *tdata);
int						quotes_parity_check(char *str, t_tok *tdata);
int						parenthesis_check(char *input);
int						delimiter_check(char *input);
int						count_tokens(char *input);
int						count_words(char *str);
void					fill_split(char **split, char *str);
int						ms_wl2(char *ptr);
int						f_lcmd_index(t_tok *tdata, int j);
int						tild_index(char *word);
char					*check_file(char *cmd, t_tok *tdata);

char					***ms_split(t_tok *tdata, char *input);
int						ms_wlcmd(char *input);
int						ms_wltoken(char *input);
int						ms_wlcmdtok(char *input);
int						ms_typecmdtok(int type);
int						ms_wlp(char *input);
void					ms_expand(t_tok *tdata, t_env *denv, int index);
char					**transform_split(char **split, t_env *denv,
							t_tok *tdata, int index);
char					**ms_joinparts(t_ts *ts, char *words, t_tok *tdata);
void					ms_expandsion_manager(char **split, t_env *denv,
							t_tok *tdata, int *x);
char					**ms_cuttab(char **tab, int start, int end);
char					**ms_strtotab(char *str);
int						ms_double_quote_transform(char **split, t_env *denv,
							int *x, t_tok *tdata);
void					ms_single_quote_transform(char **split, t_env *denv,
							int *x, t_tok *tdata);
int						ms_no_quote_transform(char **split, int *x,
							t_starlist **strl);
int						ms_isinw_pos(int i, t_tok *tdata);
int						ms_typecmdtok(int type);
int						ms_typetok(int type);
int						ms_wlcmd(char *input);
int						ms_wlcmdtok(char *input);
int						ms_wltoken(char *input);
int						ms_wlp(char *input);
char					***ms_copy_tok(char ***tokens, int t_size);
int						ms_count_words(char *input);
int						ms_newline_error(t_tok *tdata);
int						ms_token_error(t_tok *tdata);
int						ms_ambiguous_error(t_tok *tdata, int index);
char					**ms_delindex(char **split, int i);
char					*ms_delimiter(char *delimiter);
int						*ms_intab(int *w_pos, int *w_size, int p_a, int p_b);
char					**ms_check_empty(char **split);
int						ms_delimiter_expand(char **split, t_tok *tdata, int *x,
							int index);
void					ms_fill_cmd(char **split, char *input, int *j,
							int *type);
void					ms_fill_token(char **split, char *input, int *j,
							int *type);
void					ms_fill_word(char *input, int *j, int *q, int *len);
void					ms_type_set(char *input, int *x, int *type,
							char **split);

/*_.-=-._.-=-._.-=-._.-=-._.--._.-=-._.--._.-=-._.-=-._.-=-._.-=-._.-=-._*/
/*_.-=-._.-=-._.-=-._.-=-._.- TYPE PARSE -._.-=-._.-=-._.-=-._.-=-._.-=-._*/

void					handle_d_al(t_tok *tdata, t_pipe *d_pipe, t_env *denv,
							int *i);
void					handle_or(t_pipe *d_pipe);
void					handle_po(t_tok *tdata, t_pipe *d_pipe, t_env *denv,
							int *i);
void					handle_pc(t_pipe *d_pipe);
void					handle_and(t_pipe *d_pipe);

void					cmd_pipe(t_tok *tdata, t_pipe *d_pipe, t_env *denv,
							int *i);
void					cmd_here(t_tok *tdata, t_pipe *d_pipe, t_env *denv,
							int *i);
int						cmd_redi(t_tok *tdata, t_pipe *d_pipe, t_env *denv,
							int *i);
void					cmd_reset_fd(t_pipe *d_pipe);
void					handle_cmd(t_tok *tdata, t_pipe *d_pipe, t_env *denv,
							int *i);

void					pipe_parse(t_tok *tdata, t_pipe *d_pipe, t_env *denv,
							int *i);
void					exec_pipe(t_tok *tdata, t_pipe *d_pipe, t_env *denv,
							int *i);
void					cmd_exec_pipe(t_tok *tdata, t_pipe *d_pipe, t_env *denv,
							int *i);
void					handle_cmd_pipe(t_tok *tdata, t_pipe *d_pipe,
							t_env *denv, int *i);

int						previous_ope(t_tok *tdata, int i);
int						next_ope(t_tok *tdata, int i);

void					p_count(t_tok *tdata, t_pipe *d_pipe);

void					p_redi(t_tok *tdata, t_pipe *d_pipe, int *i);
void					handle_pc_paran(t_pipe *d_pipe);
void					p_redi(t_tok *tdata, t_pipe *d_pipe, int *i);
void					p_while(t_tok *tdata, t_pipe *d_pipe, t_env *denv,
							int *i);

void					ms_h_unlink(t_pipe *d_pipe);
void					ms_place_h(t_tok *tdata, char *f_name, int i);
char					*ms_getlast(t_env *denv);
void					reset_history(t_env *denv);

void					print_history(t_env *denv);
void					print_tokens(t_tok *tdata);
void					print_tok(t_tok *tdata);

int						ft_strlenlen(char **str);

void					handle_built(t_tok *tdata, t_pipe *d_pipe, t_env *denv,
							int *i);
void					b_redi(t_tok *tdata, t_pipe *d_pipe, int i);
void					b_parse(t_tok *tdata, t_env *denv, int *i);
void					b_parse_nf(t_tok *tdata, t_env *denv, int *i,
							t_pipe *d_pipe);
char					*ms_form_prompt(t_env *denv);
char					**remove_first(t_tok *dt, int skip_type, int c, int i);
int						handle_append(char *token, t_pipe *d_pipe);
int						handle_output(char *token, t_pipe *d_pipe);
int						handle_heredoc(t_tok *tdata, t_pipe *d_pipe,
							t_env *denv, int *i);
int						cmd_return(t_pipe *d_pipe, t_tok *tdata);
int						count_cmd(char **string, int *type);
int						check_next(int signe);
int						handle_input(char *token, t_pipe *d_pipe);
/*_.-=-._.-=-._.-=-._.-=-._.- HEREDOC -._.-=-._.-=-._.-=-._.-=-._.-=-._*/

char					*h_exec(t_pipe *d_pipe, char *save, char *limiter);
char					*h_redo(t_pipe *d_pipe, t_tok *tdata, char *limiter);
char					*h_handle(t_pipe *d_pipe, t_tok *tdata, t_env *denv,
							int *i);
int						heredoc(t_pipe *d_pipe, t_tok *dt, t_env *denv, int *i);

void					t_heredoc(t_tok *tdata, int *i, char *limiter);

char					*h_create_file(t_pipe *d_pipe);
int						check_here(char ***tokens, int i);
void					reset_history(t_env *denv);
void					ms_h_unlink(t_pipe *d_pipe);
void					ms_place_h(t_tok *tdata, char *f_name, int i);
char					*ms_getlast(t_env *denv);

void					c_execve(t_tok *tdata, t_pipe *d_pipe, t_env *denv,
							int *i);
void					r_parse_error(t_pipe *d_pipe, t_tok *tdata);
void					b_redi_out(t_tok *tdata, t_pipe *d_pipe, int i);

/*_.-=-._.-=-._.-=-._.-=-._.- FREE && EXIT -._.-=-._.-=-._.-=-._.-=-._.-=-._*/

void					ms_free_history(t_h_lst **head);
void					ms_free_env(t_env *denv);
void					ms_free_pipe(t_pipe *d_pipe);
void					free_tpe(t_tok *dt, t_pipe *dp, t_env *de);
void					ms_reset_fd(t_pipe *d_pipe);

/*_.-=-._.-=-._.-=-._.-=-._.--._.-=-._.--._.-=-._.-=-._.-=-._.-=-._.-=-._*/
/*_.-=-._.-=-._.-=-._.-=-._.--._.-=-._.--._.-=-._.-=-._.-=-._.-=-._.-=-._*/

void					init_sig(void);

void					prompt(t_env *denv, t_tok *tdata, int i);
t_env					*update_env(t_env *denv);
void					ms_lst_b(t_h_lst **lst, t_h_lst *newlst);
int						ms_main_pipe(t_tok *tdata, t_env *denv);

void					free_tab(char **tab);
void					free_tdata(t_tok *tdata);

int						check_here(char ***tokens, int i);
void					b_redi(t_tok *tdata, t_pipe *d_pipe, int i);
void					p_while(t_tok *tdata, t_pipe *d_pipe, t_env *denv,
							int *i);
void					w_exec_pipe(t_tok *tdata, t_pipe *d_pipe, t_env *denv,
							int *i);
void					exec_cmd(t_tok *tdata, t_pipe *d_pipe, t_env *denv,
							int *i);
int						apply_redi(t_tok *tdata, t_pipe *d_pipe, int i);
char					*h_before(t_pipe *d_pipe, t_tok *tdata, t_env *denv,
							int *i);
void					ms_place_h(t_tok *tdata, char *f_name, int i);
void					parse_type(t_tok *tdata, t_pipe *d_pipe, t_env *denv,
							int *i);
int						next_ope(t_tok *tdata, int i);
int						previous_ope(t_tok *tdata, int i);

void					print_tokens(t_tok *tdata);
void					p_parse_type(t_tok *tdata, t_pipe *d_pipe, t_env *denv,
							int *i);

void					cut_here(t_tok *tdata, int *i);
char					*ms_getlast(t_env *denv);
void					reset_history(t_env *denv);
void					tprint(char ***string);
#endif
