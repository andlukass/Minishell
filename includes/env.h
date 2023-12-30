/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 16:58:42 by user              #+#    #+#             */
/*   Updated: 2023/12/30 22:19:56 by user             ###   ########.fr       */
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
 */
char	*get_env_value(char *key);
/**
 * @brief	Free all memory alocated by the t_env list
 * @param	stack stack to be freed
 */
void	free_env(t_env *stack);

char	**env_to_array(void);
char	*get_env_key(char *variable);
void	remove_env_value(char *key);
/* --------------------------------------- */

#endif