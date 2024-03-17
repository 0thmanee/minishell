builtins_files = cd.c env_utils.c echo.c pwd.c env.c set.c export.c
parsing_files = main.c new_len.c add_spaces.c type_check.c get_cmd.c get_tokens.c remove_quotes.c join_args.c expanding_init_1.c expanding_init_2.c signals.c 
libft_files = ft_str_1.c ft_str_2.c ft_lst_1.c ft_lst_2.c ft_lst_3.c ft_char.c ft_split.c 
execution_files = execution_1.c execution_utils_1.c execv_utils.c expanding.c

builtins_srcs = $(addprefix builtins/,$(builtins_files))
parsing_srcs = $(addprefix parsing/,$(parsing_files))
libft_srcs = $(addprefix libft/,$(libft_files))
execution_srcs = $(addprefix execution/,$(execution_files))

builtins_objects = $(addprefix object_files/,$(builtins_srcs:.c=.o))
parsing_objects = $(addprefix object_files/,$(parsing_srcs:.c=.o))
libft_objects = $(addprefix object_files/,$(libft_srcs:.c=.o))
execution_objects = $(addprefix object_files/,$(execution_srcs:.c=.o))

CFLAGS = -Wall -Werror -Wextra -fsanitize=address -g
READLINEDIR = $(shell brew --prefix readline)
NAME = minishell

all: $(NAME)
$(NAME): $(builtins_objects) $(parsing_objects) $(libft_objects) $(execution_objects)
	@cc $(CFLAGS) $(builtins_objects) $(parsing_objects) $(libft_objects) $(execution_objects) -o $(NAME) -L$(READLINEDIR)/lib -lreadline
	@printf "\033[32m[ ✔ ] %s\n\033[0m" "Program Created"

object_files/builtins/%.o: builtins/%.c minishell.h
	@mkdir -p object_files/builtins
	@cc $(CFLAGS) -c $< -I . -o $@

object_files/parsing/%.o: parsing/%.c minishell.h
	@mkdir -p object_files/parsing
	@cc $(CFLAGS) -c $< -I . -o $@ -I$(READLINEDIR)/include

object_files/libft/%.o: libft/%.c minishell.h
	@mkdir -p object_files/libft
	@cc $(CFLAGS) -c $< -I . -o $@

object_files/execution/%.o: execution/%.c minishell.h
	@mkdir -p object_files/execution
	@cc $(CFLAGS) -c $< -I . -o $@


clean:
	@rm -rf  object_files

fclean: clean
	@rm -rf $(NAME)
	@printf "\033[32m[ ✔ ] %s\n\033[0m" "Cleaning Done"

re: fclean all