CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
RM = rm -f

NAME = minishell
CFILES = main.c new_len.c add_spaces.c type_check.c get_cmd.c get_tokens.c \
libft/functs_1.c libft/functs_2.c libft/functs_3.c remove_quotes.c
OFILES = $(CFILES:.c=.o)
INCLUDES = minishell.h
# READLINEDIR = /Users/$(USER)/homebrew/Cellar/readline/8.2.7

all: $(NAME)
	@printf "\033[32m[ ✔ ] %s\n\033[0m" "Program Created"

$(NAME): $(OFILES)
	@$(CC) $(CFLAGS) $^ -o $@ -lreadline
# -L$(READLINEDIR)/lib

%.o: %.c $(INCLUDES)
	@$(CC) $(CFLAGS) -c $< -o $@
#-I$(READLINEDIR)/include

clean:
	@$(RM) $(OFILES) $(OFILES_BONUS)

fclean: clean
	@$(RM) $(NAME) $(NAME_BONUS)
	@printf "\033[32m[ ✔ ] %s\n\033[0m" "Cleaning Done"

re: fclean all

.PHONY: all clean fclean re bonus