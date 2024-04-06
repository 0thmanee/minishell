builtins_files =  env_utils.c env.c export.c export_utils.c cd.c cd_utils.c echo.c pwd.c unset.c  exit.c exit_utils.c \
env_utils1.c
parsing_files = main.c new_len.c trim_input.c add_spaces.c type_check.c get_cmd_1.c get_cmd_2.c get_tokens.c \
remove_quotes.c join_args.c expanding_1.c expanding_2.c expanding_init_1.c expanding_init_2.c expanding_utils.c expanding_cases_1.c expanding_cases_2.c signals.c \
final_cmd.c final_cmd_1.c final_cmd_2.c final_cmd_3.c syntax_error.c check_braces.c ft_malloc.c

libft_files = ft_str_1.c ft_str_2.c ft_str_3.c ft_lst_1.c ft_lst_2.c ft_char.c ft_split.c ft_atoi.c
execution_files = execution_1.c execution_2.c execution_3.c execv_utils.c execute1.c execute2.c heredoc.c \
heredoc1.c execv_utils1.c execute2_1.c io.c

builtins_srcs = $(addprefix builtins/,$(builtins_files))
parsing_srcs = $(addprefix parsing/,$(parsing_files))
libft_srcs = $(addprefix libft/,$(libft_files))
execution_srcs = $(addprefix execution/,$(execution_files))

builtins_objects = $(addprefix object_files/,$(builtins_srcs:.c=.o))
parsing_objects = $(addprefix object_files/,$(parsing_srcs:.c=.o))
libft_objects = $(addprefix object_files/,$(libft_srcs:.c=.o))
execution_objects = $(addprefix object_files/,$(execution_srcs:.c=.o))

CFLAGS = -Wall -Werror -Wextra
READLINEDIR = $(shell brew --prefix readline)
NAME = minishell

all: $(NAME)
$(NAME): $(parsing_objects) $(libft_objects) $(builtins_objects) $(get_next_line_objects) $(execution_objects)
	@cc $(CFLAGS) $^ -o $(NAME) -L$(READLINEDIR)/lib -lreadline
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
	@cc $(CFLAGS) -c $< -I . -o $@ -I$(READLINEDIR)/include


clean:
	@rm -rf  object_files

fclean: clean
	@rm -rf $(NAME)
	@printf "\033[32m[ ✔ ] %s\n\033[0m" "Cleaning Done"

re: fclean all