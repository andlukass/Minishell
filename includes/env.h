/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llopes-d <llopes-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 16:58:42 by user              #+#    #+#             */
/*   Updated: 2024/02/20 18:45:54 by llopes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "minishell.h"

typedef struct s_env	t_env;

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
 * @return	the value corresponding to the key.
 */
char	*get_env_value(char *key);

/**
 * @brief	Get a key in the t_env from a variable received as parameter
 * @param	variable the full variable to separe.
 * @return	the value corresponding to the key.
 */
char	*get_env_key(char *variable);

/**
 * @brief	Free all memory alocated by the t_env list
 * @param	stack stack to be freed
 */
void	free_env(t_env *stack);

/**
 * @brief	Transform our t_env in an array
 * @return	the array with the env data.
 */
char	**env_to_array(void);

/**
 * @brief	Remove a variable from env.
 * @param	key key corresponding to the variable to be removed.
 */
void	remove_env_value(char *key);
/* --------------------------------------- */

#endif