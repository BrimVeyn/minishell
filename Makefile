NAME			:= minishell

LIBFT			:= libftprintf/libftprintf.a
CC 				:= cc
LDFLAGS			:= -lreadline -lncurses
CFLAGS 			:= -Wall -Wextra -Werror -g
SRC 			:= source/main.c source/prompt.c \
				   source/ms_h_lst.c \
				   source/exec_pipe.c \
				   source/signals.c \
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
				   source/builtins/b_exec.c \
				   source/builtins/unset.c \
				   source/builtins/export.c \
				   source/builtins/env.c \
				   source/builtins/pwd.c \
				   source/builtins/cd.c \
				   source/builtins/exit.c \
				   source/builtins/robin.c \
				   source/parsing/parse_input.c \
				   source/parsing/ft_splitm.c \
				   source/parsing/fill_splitm.c \
				   source/parsing/expands.c \
				   source/parsing/utils_two.c \
				   source/parsing/replace_env.c \
				   source/parsing/path_parse.c \
				   source/parsing/path_errors.c \
				   source/builtins/echo.c \
				   source/parsing/get_env.c \
				   source/parsing/missing_delimiter_check.c \
				   source/parsing/quotes_position_check.c \
				   source/parsing/quotes_parity_check.c \
				   source/parsing/start_check.c \
				   source/parsing/end_check.c \
				   source/parsing/delimiter_check.c \
				   source/parsing/fill_tokens.c \
				   source/parsing/add_to_cmd.c \
				   source/parsing/parenthesis_check.c \
				   source/parsing/utils.c \
				   source/parsing/count_tokens.c \
				   source/parsing/count_tokens_helpers.c \
				   source/exec/type_parse.c \
				   source/exec/handle_cmds.c \
				   source/exec/handle_type.c \
				   source/exec/handle_pipe.c \
				   source/exec/handle_paran.c \
				   source/exec/heredoc.c \
				   source/exec/heredoc_utils.c \
				   source/exec/heredoc_utils2.c \
				   source/exec/exec_cmd.c \
				   source/exec/paran_utils.c \
				   source/exec/pipe_utils.c \
				   source/exec/free_exec.c \
				   source/utils_exec/debug.c \
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
	@make --no-print-directory clean -C libftprintf/
	@printf "$(RED)Objects deleted !$(DEF_COLOR)\n"

fclean: clean
	@rm -rf $(NAME)
	@make --no-print-directory fclean -C libftprintf/
	@printf "$(RED)Binary deleted !$(DEF_COLOR)\n"

$(OBJDIR):
	@mkdir -p $(OBJDIR) $(OBJDIR)/$(STAR_DIR) $(OBJDIR)/$(DOUBLE_DIR) $(OBJDIR)/$(STRING_DIR) $(OBJDIR)/$(MISC_DIR) $(OBJDIR)/$(BUILTINS)  $(OBJDIR)/$(PARSING_DIR) $(OBJDIR)/$(EXEC) $(OBJDIR)/$(UTILS_EXEC)

$(LIBFT) :
	@make --no-print-directory -C libftprintf/

re: fclean all

.PHONY: all clean fclean re 
