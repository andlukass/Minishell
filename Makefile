GREEN := \033[32m
RED := \033[31m
END := \033[0m

SRCS = src/main.c src/utils/ft_strjoin.c src/utils/ft_strlen.c \
		src/utils/ft_split.c src/utils/ft_strrchr.c \
		src/utils/free_double_array.c src/utils/ft_itoa.c \
		src/structs/data.c \
		src/prompt/prompt.c src/builtins/ft_exit.c src/builtins/ft_echo.c \
		src/builtins/ft_pwd.c src/builtins/ft_env.c src/builtins/ft_echo.c \
		src/env/env.c \

CFLAGS = -lreadline #-Wall -Wextra -Werror

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