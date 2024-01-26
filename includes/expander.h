/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 14:46:45 by isbraz-d          #+#    #+#             */
/*   Updated: 2024/01/26 12:43:35 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"

char	**expander(char **strs);

char	*manipulate_str(char **new_str, char *add, int size);

char	**rm_quotes(char **strs);

char	*get_sendable(char *str);

int		find_string(char **strs);

int		there_is_expansion(char *str);

void	expander_heredoc(char **str);

char	**manipulate_array(char **strs, int index);

int		count_strs(char **strs);

int		check_str(char *str);

#endif