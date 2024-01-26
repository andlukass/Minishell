/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_key.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 20:21:22 by llopes-d          #+#    #+#             */
/*   Updated: 2024/01/26 12:35:52 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_key(char *variable)
{
	char	*env_key;

	if (ft_strchr(variable, '='))
		env_key = ft_strndup(variable, ft_strchr(variable, '=') - variable);
	else
		env_key = ft_strndup(variable, ft_strlen(variable));
	return (env_key);
}
