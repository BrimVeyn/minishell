NAME			:= libft.a

CC 				:= cc
CFLAGS 			:= -Wall -Wextra -Werror
AR				:= ar rc
RAN 			:= ranlib 
SRC 			:= source/ft_atoi.c source/ft_bzero.c source/ft_calloc.c source/ft_isalnum.c \
				   source/ft_isalpha.c source/ft_isascii.c source/ft_isdigit.c source/ft_isprint.c source/ft_itoa.c \
				   source/ft_lstadd_back.c source/ft_lstadd_front.c source/ft_lstclear.c source/ft_lstdelone.c source/ft_lstiter.c \
				   source/ft_lstlast.c source/ft_lstmap.c source/ft_lstnew.c source/ft_lstsize.c source/ft_memccpy.c source/ft_memchr.c \
				   source/ft_memcmp.c source/ft_memcpy.c source/ft_memmove.c source/ft_memset.c source/ft_putchar_fd.c \
				   source/ft_putendl_fd.c source/ft_putnbr_fd.c source/ft_putstr_fd.c source/ft_split.c source/ft_strchr.c source/ft_strdup.c \
				   source/ft_striteri.c source/ft_strjoin.c source/ft_strlcat.c \
				   source/ft_strlcpy.c source/ft_strlen.c source/ft_strmapi.c source/ft_strncmp.c source/ft_strnstr.c source/ft_strrchr.c \
				   source/ft_strtrim.c source/ft_substr.c source/ft_tolower.c source/ft_toupper.c 
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

$(NAME): $(OBJDIR) $(OBJ)
	@echo "$(GREEN)Making library : $(NAME)"
	@printf "$(MAGENTA)"
	@$(AR) $(NAME) $(OBJ)
	@$(RAN) $(NAME)
	@printf "Done !$(DEF_COLOR)\n"

$(OBJDIR)/%.o: source/%.c
	@printf '$(YELLOW)Compiling : %-25s $(CYAN)-->	$(YELLOW)%-30s\n' "$<" "$@";
	@printf "$(BLUE)"
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "$(DEF_COLOR)"

clean:
	@rm -rf $(OBJDIR) $(OBJ) 
	@printf "$(RED)Objects deleted !$(DEF_COLOR)\n"

fclean: clean
	@rm -rf $(NAME)
	@printf "$(RED)Library deleted !$(DEF_COLOR)\n"

$(OBJDIR):
	@mkdir -p $(OBJDIR)

re: fclean all

.PHONY: all clean fclean re 
