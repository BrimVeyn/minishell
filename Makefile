NAME			:= minishell

LIBFT			:= libft/libft.a
CC 				:= cc
CFLAGS 			:= -Wall -Wextra -Werror -lreadline
SRC 			:= source/main.c source/prompt.c source/get_env.c source/ms_utils_free.c
OBJ 			:= $(SRC:source/%.c=objects/%.o)
OBJDIR 			:= objects

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
	@$(CC) $(OBJ) $(LIBFT) $(CFLAGS) -o $(NAME)
	@printf "Done !$(DEF_COLOR)\n"

$(OBJDIR)/%.o: source/%.c
	@printf '$(YELLOW)Compiling : %-25s $(CYAN)-->	$(YELLOW)%-30s\n' "$<" "$@";
	@printf "$(BLUE)"
	@$(CC) -c $< -o $@
	@printf "$(DEF_COLOR)"

clean:
	@rm -rf $(OBJDIR) $(OBJ) 
	@printf "$(RED)Objects deleted !$(DEF_COLOR)\n"

fclean: clean
	@rm -rf $(NAME)
	@printf "$(RED)Binary deleted !$(DEF_COLOR)\n"

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(LIBFT) :
	@make -C libft/

re: fclean all

.PHONY: all clean fclean re 
