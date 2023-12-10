/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llopes-d <llopes-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 19:14:55 by llopes-d          #+#    #+#             */
/*   Updated: 2023/12/10 19:38:21 by llopes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_ls()
{
	DIR* dir= opendir(".");

	struct dirent* entity;
	
	entity = readdir(dir);
	while(entity != NULL)
	{
		printf("%s\n",entity->d_name);
		entity = readdir(dir);
	}
	closedir(dir);
	return 0;
}

void	ft_cd()
{
	char currentDirectory[1024];

	if (!get_data()->input_array[1])
	{
		if (!get_env_value("HOME"))
		{
			printf("HOME is not set!\n");
			return ;
		}
		chdir(get_env_value("HOME"));
		return ;
	}
	if (get_data()->input_array[2])
	{
		printf("cd only take one argument!\n");
		return ;
	}
	if (chdir(get_data()->input_array[1]) == 0)
		printf("Changed directory to: %s\n", get_data()->input_array[1]);
	else
	{
		perror(get_data()->input_array[1]);
		return ;
	}

	if (getcwd(currentDirectory, sizeof(currentDirectory)) != NULL) {
		printf("Current directory after chdir: %s\n", currentDirectory);
	 } else {
		perror("Error getting current directory before chdir");
		return ; // Return an error code, if needed
	 }
}
