NAME			:= minishell

LIBFT			:= libftprintf/libftprintf.a
CC 				:= cc
LDFLAGS			:= -lreadline -lncurses
CFLAGS 			:= -Wall -Werror -Wextra
DEBUG 			:= -DDEBUG
SRC 			:= source/main.c source/prompt.c \
				   source/ms_h_lst.c \
				   source/signals.c \
				   source/prompt2.c \
				   source/double_linked_list/ms_dlstaddback.c \
				   source/double_linked_list/ms_dlstclear.c \
				   source/double_linked_list/ms_dlstdelone.c \
				   source/double_linked_list/ms_dlstmap.c \
				   source/double_linked_list/ms_dlstnew.c \
				   source/double_linked_list/ms_dlstjoin.c \
				   source/double_linked_list/ms_dlstmatchs.c \
				   source/double_linked_list/ms_dswapstr.c \
				   source/double_linked_list/ms_dlstlen.c \
				   source/double_linked_list/ms_dlsort.c \
				   source/star_list/ms_starlclear.c \
				   source/star_list/ms_starlnew.c \
				   source/star_list/ms_starsplit.c \
				   source/star_list/ms_startlab.c \
				   source/star_list/ms_starjoin.c \
				   source/string_utils/ms_strtolower.c \
				   source/string_utils/ms_findstar.c \
				   source/string_utils/ms_strstrchr.c \
				   source/string_utils/ms_isws.c \
				   source/string_utils/ms_cut_at.c \
				   source/string_utils/ms_strtrimfree.c \
				   source/string_utils/ms_getenv.c \
				   source/string_utils/ms_join_tab.c \
				   source/string_utils/ms_joinstarstar.c \
				   source/string_utils/ms_tablen.c \
				   source/string_utils/ms_replace_value.c \
				   source/builtins/echo.c \
				   source/builtins/b_exec.c \
				   source/builtins/unset.c \
				   source/builtins/export.c \
				   source/builtins/export_helper1.c \
				   source/builtins/export_no_args.c \
				   source/builtins/export_plus.c \
				   source/builtins/env.c \
				   source/builtins/pwd.c \
				   source/builtins/cd.c \
				   source/builtins/cd_minus.c \
				   source/builtins/exit.c \
				   source/parsing/ms_add_path.c \
				   source/parsing/ms_count_tokens.c \
				   source/parsing/ms_expand.c \
				   source/parsing/ms_expand_manager.c \
				   source/parsing/ms_joinparts.c \
				   source/parsing/ms_get_env.c \
				   source/parsing/ms_parse_input.c \
				   source/parsing/ms_parsing_errors.c \
				   source/parsing/ms_path_errors.c \
				   source/parsing/ms_split.c \
				   source/parsing/ms_split_utils.c \
				   source/parsing/ms_token_errors.c \
				   source/parsing/ms_unclosed_quotes_error.c \
				   source/parsing/ms_var_expand.c \
				   source/parsing/ms_whitelist.c \
				   source/parsing/ms_wildcards.c \
				   source/parsing/parenthesis_check.c \
				   source/parsing/utils.c \
				   source/parsing/utils_two.c \
				   source/parsing/utils_three.c \
				   source/exec/main_exec.c \
				   source/exec/type_parse.c \
				   source/exec/handle_cmds.c \
				   source/exec/handle_type.c \
				   source/exec/handle_pipe.c \
				   source/exec/handle_paran.c \
				   source/exec/heredoc.c \
				   source/exec/heredoc_utils.c \
				   source/exec/heredoc_utils2.c \
				   source/exec/heredoc_utils3.c \
				   source/exec/exec_cmd.c \
				   source/exec/paran_utils.c \
				   source/exec/pipe_utils.c \
				   source/exec/free_exec.c \
				   source/exec/redirect.c\
				   source/exec/redirect2.c\
				   source/exec/cmd_redi.c \
				   source/exec/redirect_helper.c \
				   source/utils_exec/utils.c \
				   source/misc/ms_setint.c \
				   source/misc/ms_setchar.c \
				   source/misc/ms_inits.c \
				   source/misc/ms_free.c \

OBJ 			:= $(SRC:source/%.c=objects/%.o)

OBJDIR 			:= objects
DOUBLE_DIR		:= double_linked_list
STRING_DIR		:= string_utils
STAR_DIR		:= star_list
MISC_DIR		:= misc
BUILTINS		:= builtins
PARSING_DIR		:= parsing
EXEC			:= exec
UTILS_EXEC      := utils_exec

DEF_COLOR		:= \033[0;39m
GRAY			:= \033[0;90m
RED				:= \033[0;91m
GREEN			:= \033[0;92m
YELLOW			:= \033[0;93m
BLUE			:= \033[0;94m
MAGENTA			:= \033[0;95m
CYAN			:= \033[0;96m
WHITE			:= \033[0;97m

all: $(NAME)

$(NAME): $(LIBFT) $(OBJDIR) $(OBJ)
	@echo "$(GREEN)Making binary: $(NAME)"
	@printf "$(MAGENTA)"
	@$(CC) $(OBJ) $(LIBFT) $(CFLAGS) $(LDFLAGS) -o $(NAME)
	@printf "Done !$(DEF_COLOR)\n"

$(OBJDIR)/%.o: source/%.c
	@printf '$(YELLOW)Compiling : %-45s $(CYAN)-->	$(YELLOW)%-30s\n' "$<" "$@";
	@printf "$(BLUE)"
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "$(DEF_COLOR)"

clean:
	@rm -rf $(OBJDIR)
	@make --no-print-directory -C libftprintf/ clean 
	@printf "$(RED)Objects deleted !$(DEF_COLOR)\n"

fclean: clean
	@rm -rf $(NAME)
	@make --no-print-directory -C libftprintf/ fclean
	@printf "$(RED)Binary deleted !$(DEF_COLOR)\n"

$(OBJDIR):
	@mkdir -p $(OBJDIR) $(OBJDIR)/$(STAR_DIR) $(OBJDIR)/$(DOUBLE_DIR) $(OBJDIR)/$(STRING_DIR) $(OBJDIR)/$(MISC_DIR) $(OBJDIR)/$(BUILTINS)  $(OBJDIR)/$(PARSING_DIR) $(OBJDIR)/$(EXEC) $(OBJDIR)/$(UTILS_EXEC)

$(LIBFT) :
	@make --no-print-directory -C libftprintf/

re: fclean all

.PHONY: all clean fclean re 
