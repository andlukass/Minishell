/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llopes-d <llopes-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 19:40:21 by llopes-d          #+#    #+#             */
/*   Updated: 2023/12/05 20:33:50 by llopes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_pwd(char **command)
{
	if (command[1] != (void *)0)
		printf("pwd doesn't take any arguments!\n");
	else if (get_env_value("PWD"))
		printf("%s\n", get_env_value("PWD"));
	else
		printf("PWD is not set!\n");
	ft_exit(NULL);
}
