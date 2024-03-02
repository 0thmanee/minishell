builtins_files = cd.c ft_lst.c ft_str.c
builtins_srcs = $(addprefix builtins/,$(builtins_files))
builtins_objects = $(addprefix object_files/,$(builtins_srcs:.c=.o))

NAME = minishell

all: $(NAME)
$(NAME): $(builtins_objects)
	cc $(CFLAGS) -lreadline $(builtins_objects) -o $(NAME)

object_files/builtins/%.o: builtins/%.c
	mkdir -p object_files/builtins
	cc  -c $< -I . -o $@

clean:
	rm -rf  object_files

fclean: clean
	rm -rf $(NAME)

re: fclean all