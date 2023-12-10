/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 18:54:15 by llopes-d          #+#    #+#             */
/*   Updated: 2023/12/10 23:50:31 by user             ###   ########.fr       */
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

# include <dirent.h>

# define GLOBAL_WARMING_DONT_EXIST 1
# define DO_FREE 1
# define NO_FREE 0

typedef struct s_env{
	char			*variable;
	struct s_env	*next;
}	t_env;

typedef struct s_data{
	char	**input_array;
	char	*input;
	char	*prompt;
	char	*username;
	char	*path;
	t_env	*env;
}	t_data;

/**
 * @brief	Static struct accessible from any point of the code.
 * @return	the adress of the static struct.
 */
t_data	*get_data(void);

char	**ft_split(char const *s, char c);
void	free_double_array(char **array);
void	ft_pwd(void);
void	ft_env(void);
void	ft_export(void);
void	ft_unset(void);
char	*ft_strrchr(const char *s, int c);
char	*get_env_key(char *variable);
void	*update_env_value(char *key, char *variable);

int ft_ls();
void ft_cd();

char	*ft_itoa(int n);

/**
 * @param	s the string in which to search.
 * @param	c the char to search in 's'.
 * @return	the adress of the last occurence of 'c' in 's'.
 * 0 if nothing is found.
 */
char	*ft_strrchr(const char *s, int c);

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

/**
 * @brief	Prints exit message, free what is needed and exit program.
 */
void	ft_exit(void);

/**
 * @brief	Prints whats was the input.
 */
void	ft_echo(void);

/**
 * @brief	Copy then env to a linked list stored in the global data
 */
void	get_env(char *env[]);
/**
 * @brief	Add a new t_env allocated node in a t_env stack
 */
void	add_next_node(t_env **list, t_env *new);
/**
 * @brief	Create a new allocated node for t_env
 */
t_env	*create_new_value(char *variable);
/**
 * @brief	Get a value in the t_env from a key received as parameter
 */
char	*get_env_value(char *key);
/**
 * @brief	Free all memory alocated by the t_env list
 */
void	free_env(t_env *stack);

#endif