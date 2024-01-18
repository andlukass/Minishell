/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 16:59:14 by user              #+#    #+#             */
/*   Updated: 2024/01/18 10:52:44 by user             ###   ########.fr       */
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

int		ft_isalpha(int c);

void	init_vars(int *a, int *b, int *c, int *d);

/* --------------------------------------- */

#endif