/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 18:54:15 by llopes-d          #+#    #+#             */
/*   Updated: 2023/12/21 13:55:12 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

//waitpid & pipe
# include <sys/wait.h>
# include <fcntl.h>

# include <dirent.h>

# define GLOBAL_WARMING_DONT_EXIST 1
# define DO_FREE 1
# define NO_FREE 0

typedef struct s_env{
	char			*variable;
	struct s_env	*next;
}	t_env;

typedef struct s_commands{
	char				**command;
	int					is_pipe;
	struct s_commands	*next;
}	t_commands;

typedef struct s_data{
	char		**input_array;
	char		*input;
	char		*prompt;
	char		*username;
	char		*path;
	t_env		*env;
	t_commands	*commands;
	int			number_of_commands;
}	t_data;

/**
 * @brief	Static struct accessible from any point of the code.
 * @return	the adress of the static struct.
 */
t_data	*get_data(void);

/* ---------------BUILTINS---------------- */

/**
 * @brief	Prints the current directory.
 * @param command a command formed from an array of tokens.
 */
void	ft_pwd(char **command);

/**
 * @brief	Prints the system environment.
 * @param command a command formed from an array of tokens.
 */
void	ft_env(char **command);

/**
 * @brief	Prints the system environment or adds to it based on the
 * number of commands provided.
 * @param command a command formed from an array of tokens.
 */
void	ft_export(char **command);

/**
 * @brief	Remove from the system environment.
 * @param command a command formed from an array of tokens.
 */
void	ft_unset(char **command);

/**
 * @brief	Prints exit message, free what is needed and exit program.
 * @param command a command formed from an array of tokens.
 */
void	ft_exit(char **command);

/**
 * @brief	Prints whats was the input.
 * @param command a command formed from an array of tokens.
 */
void	ft_echo(char **command);

/**
 * @brief	Change the current directory.
 * @param command a command formed from an array of tokens.
 */
void	ft_cd(char **command);
/* --------------------------------------- */

/* ---------------EXECUTOR---------------- */

/**
 * @brief	Execute all the commands received, handling pipes
 * and "> and >>" redirections.
 * @param commands an array of commands
 * @param fd pipe generated array of fds. NULL if don't have a pipe
 */
void	executor(t_commands **commands, int *fd);
/* --------------------------------------- */

/* ----------------PARSER----------------- */

void	handle_input(void);
void	free_commands(t_commands *stack);
/* --------------------------------------- */

/* ------------------ENV------------------ */

/**
 * @brief	Copy then env to a linked list stored in the global data
 * @param	env the env of the program
 */
void	get_env(char *env[]);
/**
 * @brief	Add a new t_env allocated node in a t_env stack
 */
int		add_next_node(t_env **list, char *variable);

/**
 * @brief	Get a value in the t_env from a key received as parameter
 * @param	key key to be searched
 */
char	*get_env_value(char *key);
/**
 * @brief	Free all memory alocated by the t_env list
 * @param	stack stack to be freed
 */
void	free_env(t_env *stack);

char	*get_env_key(char *variable);
void	remove_env_value(char *key);
/* --------------------------------------- */

/* ----------------PROMPT----------------- */
/**
 * @brief	Compares home directory with the current PWD
 * and returns the portion of the actual directory path 
 * that is beyond the home directory.
 */
char	*get_dir(void);

/**
 * @brief	Concatenates the username with the current directory
 * and end the terminal stylization.
 * The prompt is stored in the global data.
 */
void	get_prompt(void);

/**
 * @brief	Gets the username and initiates the terminal stylization.
 * The username is stored in the global data.
 */
void	get_username(void);
/* --------------------------------------- */

/* -----------------UTILS----------------- */

/**
 * @brief	Separate the string 's' using 'c', creating an array 
 * of string with each new string createad after the separation.
 * @param	s the string in which to split.
 * @param	c the char to delimit the strings.
 * @return	an array of strings terminated with a NULL pointer.
 */
char	**ft_split(char const *s, char c);

/**
 * @param	n number to transform into a string.
 * @return	the number n, into a dinamic allocated string.
 */
char	*ft_itoa(int n);

/**
 * @param	s the string in which to search.
 * @param	c the char to search in 's'.
 * @return	the adress of the first occurence of 'c' in 's'.
 * 0 if nothing is found.
 */
char	*ft_strchr(const char *s, int c);

/**
 * @brief	Concatenates two strings.
 * @param	is_free is used to determine whether you
 * want to free s1 or not. Passing 0 indicate that
 * it should not be freed.
 * @return	the new concatenated string, which should be
 * freed afer use.
 */
char	*ft_strjoin(char *s1, char *s2, int is_free);

/**
 * @param	s string in which to get size.
 * @return	the size of 's'.
 */
int		ft_strlen(const char *s);

/**
 * @brief	Cleanly frees a double char pointer array.
 * @param	array the array to be freed.
 */
void	free_double_array(char **array);
/* --------------------------------------- */

#endif