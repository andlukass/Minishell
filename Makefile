GREEN := \033[32m
RED := \033[31m
END := \033[0m

SRCS = src/main.c src/utils/ft_strjoin.c src/utils/ft_strlen.c \
		src/utils/ft_itoa.c src/utils/ft_strchr.c src/utils/ft_strdup.c \
		src/utils/free_double_array.c src/utils/ft_split.c \
		src/utils/ft_strcmp.c src/utils/ft_strncmp.c \
		src/structs/data.c \
		src/prompt/prompt.c src/builtins/ft_exit.c src/builtins/ft_echo.c \
		src/builtins/ft_pwd.c src/builtins/ft_env.c src/builtins/ft_export.c \
		src/builtins/ft_unset.c src/builtins/ft_cd.c src/builtins/is_builtin.c \
		src/env/get_env.c src/env/free_env.c \
		src/env/add_next_node.c src/env/get_env_value.c \
		src/env/get_env_key.c src/env/remove_env_value.c \
		src/env/env_to_array.c \
		src/executor/executor.c src/executor/open_files.c \
		src/executor/close_fds.c src/executor/executor_router.c \
		src/.parsing_test/parsing_test.c

CFLAGS = -lreadline -g #-Wall -Wextra -Werror

NAME = minishell

all: $(NAME)

$(NAME): $(SRCS)
	@$(CC) $(SRCS) -o $(NAME) $(CFLAGS)
	@echo "\n$(GREEN)> Compilation done!\n$(END)"

clean:
		@echo "\n$(RED)> Cleaned!\n$(END)"

fclean:	clean
		@$(RM) $(NAME)

re:		fclean all

v: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --suppressions=readline.supp ./$(NAME)

.PHONY:	all clean fclean re