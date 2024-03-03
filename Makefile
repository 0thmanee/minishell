CC = cc
CFLAGS = -Wall -Wextra -Werror
READLINE = -lreadline -I ~/brew/opt/readline/include
RM = rm -f

NAME = minishell
CFILES = main.c utils_1.c utils_2.c libft/functs_1.c libft/functs_2.c
OFILES = $(CFILES:.c=.o)
INCLUDES = minishell.h

all: $(NAME)
	@printf "\033[32m[ ✔ ] %s\n\033[0m" "Program Created"

$(NAME): $(OFILES)
	@$(CC) $(CFLAGS) $(READLINE) $^ -o $@

%.o: %.c $(INCLUDES)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OFILES) $(OFILES_BONUS)

fclean: clean
	@$(RM) $(NAME) $(NAME_BONUS)
	@printf "\033[32m[ ✔ ] %s\n\033[0m" "Cleaning Done"

re: fclean all

.PHONY: all clean fclean re bonus