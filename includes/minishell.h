/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 18:54:15 by llopes-d          #+#    #+#             */
/*   Updated: 2023/12/30 21:35:31 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ---------------HEADERS--------------- */
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# include <readline/readline.h>
# include <readline/history.h>

# include <sys/wait.h>
# include <fcntl.h>

# include <signal.h>

# include "env.h"
# include "executor.h"
# include "parser.h"
# include "builtins.h"
# include "prompt.h"
# include "utils.h"
/* ------------------------------------- */

typedef struct s_env{
	char			*variable;
	struct s_env	*next;
}	t_env;

typedef struct s_commands{
	char				**command;
	char				**gt_files;
	char				*greater_than;
	char				**heredocs;
	char				**lt_files;
	char				*less_than;
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

#endif