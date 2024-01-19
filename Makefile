NAME			:= minishell

LIBFT			:= libftprintf/libftprintf.a
CC 				:= cc
LDFLAGS			:= -lreadline -lncurses -fsanitize=address
CFLAGS 			:= -Wall -Wextra -Werror -g
SRC 			:= source/main.c source/prompt.c source/get_env.c \
				   source/free.c source/parse.c source/ms_h_lst.c \
				   source/exec_pipe.c source/path_parse.c source/inits.c \
				   source/ft_strtrimfree.c source/ft_splitm.c source/signals.c \
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
				   source/misc/ms_setint.c

OBJ 			:= $(SRC:source/%.c=objects/%.o)

OBJDIR 			:= objects
DOUBLE_DIR		:= double_linked_list
STRING_DIR		:= string_utils
STAR_DIR		:= star_list
MISC_DIR		:= misc

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
	@mkdir -p $(OBJDIR) $(OBJDIR)/$(STAR_DIR) $(OBJDIR)/$(DOUBLE_DIR) $(OBJDIR)/$(STRING_DIR) $(OBJDIR)/$(MISC_DIR) 

$(LIBFT) :
	@make --no-print-directory -C libftprintf/

re: fclean all

.PHONY: all clean fclean re 
