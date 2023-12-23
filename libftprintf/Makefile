NAME = libftprintf.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = sources/ft_atoi.c \
       sources/ft_itoa_u.c \
       sources/ft_memset.c \
       sources/ft_strmapi.c \
       sources/ft_bzero.c \
       sources/ft_lstadd_back.c \
       sources/ft_printf.c \
       sources/ft_strncmp.c \
       sources/ft_calloc.c \
       sources/ft_lstadd_front.c \
       sources/ft_putchar_fd.c \
       sources/ft_strnstr.c \
       sources/ft_exec_d.c \
       sources/ft_lstclear.c \
       sources/ft_putendl_fd.c \
       sources/ft_strrchr.c \
       sources/ft_exec_flags.c \
       sources/ft_lstdelone.c \
       sources/ft_putnbr_fd.c \
       sources/ft_strtrim.c \
       sources/ft_fcustoms.c \
       sources/ft_lstiter.c \
       sources/ft_putstr_fd.c \
       sources/ft_substr.c \
       sources/ft_flags.c \
       sources/ft_lstlast.c \
       sources/ft_split.c \
       sources/ft_tohexa.c \
       sources/ft_fsource.c \
       sources/ft_lstmap.c \
       sources/ft_strchr.c \
       sources/ft_tolower.c \
       sources/ft_isalnum.c \
       sources/ft_lstnew.c \
       sources/ft_strdup.c \
       sources/ft_tools2.c \
       sources/ft_isalpha.c \
       sources/ft_lstsize.c \
       sources/ft_striteri.c \
       sources/ft_tools.c \
       sources/ft_isascii.c \
       sources/ft_memchr.c \
       sources/ft_strjoin.c \
       sources/ft_toupper.c \
       sources/ft_isdigit.c \
       sources/ft_memcmp.c \
       sources/ft_strlcat.c \
       sources/ft_isprint.c \
       sources/ft_memcpy.c \
       sources/ft_strlcpy.c \
       sources/ft_itoa.c \
       sources/ft_memmove.c \
	   sources/ft_printf.c \
	   sources/ft_sprintf.c \
	   sources/ms_utils_free.c \
       sources/ft_strlen.c
OBJS = $(SRCS:sources/%.c=objets/%.o)
AR = ar rcs
LIB = ranlib
OBJDEST = ./objets

all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) $(NAME) $(OBJS)
	@$(LIB) $(NAME)

$(OBJDEST)/%.o: sources/%.c
	@mkdir -p $(OBJDEST)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

progress: fclean
	@TOTAL_FILES=$$(echo $(SRCS) | wc -w); \
	COMPLETED_FILES=0; \
	GREEN='\033[0;32m'; \
	YELLOW='\033[0;33m'; \
	NC='\033[0m'; \
	FILLED_BLOCK='▓'; \
	EMPTY_BLOCK='░'; \
	echo "$${GREEN}"; \
	echo " ___       ___  ________  ________ _________  ________  ________  ___  ________   _________  ________ " ;\
	echo "|\  \     |\  \|\   __  \|\  _____\\\\\\___   ___\\\\\\   __  \|\   __  \|\  \|\   ___  \|\___   ___\\\\\\  _____\\" ;\
	echo "\ \  \    \ \  \ \  \|\ /\ \  \__/\|___ \  \_\ \  \|\  \ \  \|\  \ \  \ \  \\\\\\ \  \|___ \  \_\ \  \__/ " ;\
	echo " \ \  \    \ \  \ \   __  \ \   __\    \ \  \ \ \   ____\ \   _  _\ \  \ \  \\\\\\ \  \   \ \  \ \ \   __\\" ;\
	echo "  \ \  \____\ \  \ \  \|\  \ \  \_|     \ \  \ \ \  \___|\ \  \\\\\\  \\\\\\ \  \ \  \\\\\\ \  \   \ \  \ \ \  \_|" ;\
	echo "   \ \_______\ \__\ \_______\ \__\       \ \__\ \ \__\    \ \__\\\\\\ _\\\\\\ \__\ \__\\\\\\ \__\   \ \__\ \ \__\\" ;\
	echo "    \|_______|\|__|\|_______|\|__|        \|__|  \|__|     \|__|\|__|\|__|\|__| \|__|    \|__|  \|__| " ;\
	echo "                                                                                                      " ;\
	echo "$${NC}"; \
	draw_progress_bar() { \
		PERCENT=$$(( 100 * $$COMPLETED_FILES / $$TOTAL_FILES )); \
		FILLED=$$(( $$PERCENT / 2 )); \
		UNFILLED=$$(( 50 - $$FILLED )); \
		printf "\r$$(tput el)"; \
		printf "$${NC}%3d%% $${YELLOW}[" $$PERCENT; \
		printf "$${GREEN}%0.s$${FILLED_BLOCK}" $$(seq 1 $$FILLED); \
		printf "$${NC}%0.s$${EMPTY_BLOCK}" $$(seq 1 $$UNFILLED); \
		printf "$${YELLOW}]"; \
		if [ $$COMPLETED_FILES -gt 0 ]; then \
			printf " $${GREEN}$${LAST_SRC} compiled$${NC}"; \
		fi; \
	}; \
	for SRC in $(SRCS); do \
		OBJ=$$(echo $$SRC | sed 's/sources\//objets\//' | sed 's/\.c$$/.o/'); \
		if [ ! -f $$OBJ ] || [ $$SRC -nt $$OBJ ]; then \
			$(CC) $(CFLAGS) -c $$SRC -o $$OBJ; \
		fi; \
		LAST_SRC=$$(basename $$SRC .c); \
		COMPLETED_FILES=$$((COMPLETED_FILES + 1)); \
		draw_progress_bar; \
	done; \
	printf "\r$$(tput el)"; \
	printf "$${NC}%3d%% $${YELLOW}[" $$PERCENT; \
	printf "$${GREEN}%0.s$${FILLED_BLOCK}" $$(seq 1 $$FILLED); \
	printf "$${YELLOW}]"; \
	echo "\n$${GREEN}Compilation terminée.$${NC}\n"
	@$(AR) $(NAME) $(OBJS)

.PHONY: all clean fclean re bonus progress


