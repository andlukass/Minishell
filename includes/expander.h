/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isbraz-d <isbraz-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 14:46:45 by isbraz-d          #+#    #+#             */
/*   Updated: 2024/01/21 23:18:17 by isbraz-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"

char	**expander(char **strs);

void	manipulate_str(char **new_str, char *add, int size);

char	**rm_quotes(char **strs);

char	*get_sendable(char *str);

int		find_string(char **strs);

int	there_is_expansion(char *str);

void	expander_heredoc(char **str, char *sendable);

#endif