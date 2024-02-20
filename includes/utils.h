/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llopes-d <llopes-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 16:59:14 by user              #+#    #+#             */
/*   Updated: 2024/02/20 18:51:46 by llopes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# define DO_FREE 1
# define NO_FREE 0

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
 * @param	str string to transform into a number.
 * @return	the string str, into a number.
 */
int		ft_atoi(const char *str);

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

/**
 * @brief	Copy a string to a new dinamic allocated string.
 * @param	s1 the string to be copied.
 * @return	the new dinamic allocated string, which should be
 * freed afer use.
 */
char	*ft_strdup(char const *s1);

/**
 * @brief	Copy a string to a new dinamic allocated string
 * until the size 'n'.
 * @param	s1 the string to be copied.
 * @param	n size of the new string.
 * @return	the new dinamic allocated string, which should be
 * freed afer use.
 */
char	*ft_strndup(char const *s1, unsigned int n);

/**
 * @brief	Compare 2 strings until the limit 'n'.
 * @param	s1 the string to be compared.
 * @param	s2 the string to be compared.
 * @param	n the limit to be compared.
 * @return	the ascii diference between the first different char,
 * 0 if they are all equal
 */
int		ft_strncmp(const char *s1, const char *s2, unsigned int n);

/**
 * @brief	Compare 2 strings.
 * @param	s1 the string to be compared.
 * @param	s2 the string to be compared.
 * @return	the ascii diference between the first different char,
 * 0 if they are all equal
 */
int		ft_strcmp(const char *s1, const char *s2);

/**
 * @brief	Checks if the ascii is an alphabetic char.
 * @param	c the ascii to be checked.
 * @return	returns 1 if it is an alphabetic char and 0 if its not.
 */
int		ft_isalpha(int c);

/**
 * @brief	Init all variables passed as parameter to 0.
 */
void	init_vars(int *a, int *b, int *c, int *d);

/**
 * @brief	Do a fork to get the value of the actual proccess.
 * @return	the value of the actual proccess.
 */
int		get_process(void);

/**
 * @brief	Checks if the string is a redirection.
 * @param	str the string to be checked.
 * @return	returns 1 if it is a redirection and 0 if its not.
 */
int		is_redirection(char *str);

/**
 * @brief	Checks if the ascii is a whitespace.
 * @param	c the ascii to be checked.
 * @return	returns 1 if it is a whitespace and 0 if its not.
 */
int		is_whitespace(int c);
/* --------------------------------------- */

#endif