/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llopes-d <llopes-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 18:54:15 by llopes-d          #+#    #+#             */
/*   Updated: 2023/11/26 16:10:44 by llopes-d         ###   ########.fr       */
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

# define GLOBAL_WARMING_DONT_EXIST 1
# define DO_FREE 1
# define NO_FREE 0

typedef struct s_data{
	char	*input;
	char	*prompt;
	char	*username;
	int		test;
}	t_data;

/**
 * @brief	Static struct accessible from any point of the code.
 * @return	the adress of the static struct.
 */
t_data	*get_data(void);

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

#endif