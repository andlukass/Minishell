/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 18:54:15 by llopes-d          #+#    #+#             */
/*   Updated: 2023/12/23 17:29:08 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# include <readline/readline.h>
# include <readline/history.h>

# include <sys/wait.h>
# include <fcntl.h>

# include <signal.h>

# include <string.h>

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

/* ---------------HEADERS--------------- */
# include "env.h"
# include "executor.h"
# include "parser.h"
# include "builtins.h"
# include "prompt.h"
# include "utils.h"
/* ------------------------------------- */

/**
 * @brief	Static struct accessible from any point of the code.
 * @return	the adress of the static struct.
 */
t_data	*get_data(void);

#endif