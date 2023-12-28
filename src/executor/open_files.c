/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 12:37:06 by user              #+#    #+#             */
/*   Updated: 2023/12/28 17:22:14 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	do_heredocs(t_commands *current)
{
	int		temp_file;
	int		index;
	char	*input;
	char	*text;

	index = 0;
	temp_file = -1;
	while (current->heredocs[index])
	{
		if (temp_file)
			close(temp_file);
		temp_file = open(".temp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0777);
		text = NULL;
		while (1)
		{
			input = readline("> ");
			if (input == NULL) // Verifica se a entrada é nula (geralmente indica Ctrl+D)
			{
				printf("wanted terminador: '%s'.\n", current->heredocs[index]);
				break ;
			}
			if (!ft_strcmp(input, current->heredocs[index]))
			{
				free(input);
				break ;
			}
			text = ft_strjoin(text, input, 1);
			text = ft_strjoin(text, "\n", 1);
			free(input);
		}
		write(temp_file, text, ft_strlen(text));
		free(text);
		index++;
	}
	if (temp_file)
	{
		close(temp_file);
		temp_file = open(".temp.txt", O_RDONLY, 0777);
	}
	return (temp_file);
}

static int	do_greater_than(t_commands *current)
{
	int		index;
	int		fd;
	int		flag;

	if (!current->greater_than)
		return (0);
	if (!ft_strcmp(current->greater_than, ">"))
		flag = O_TRUNC;
	else
		flag = O_APPEND;
	index = 0;
	while (current->gt_files[index])
	{
		fd = open(current->gt_files[index], O_WRONLY | O_CREAT | flag, 0777);
		index++;
		if (current->gt_files[index])
			close(fd);
	}
	return (fd);
}

static int	do_less_than(t_commands *current)
{
	int	index;
	int	file;

	index = 0;
	file = -1;
	if (current->less_than && !ft_strcmp(current->less_than, "<"))
	{
		while (current->lt_files[index])
		{
			if (!current->lt_files[index + 1])
				file = open(current->lt_files[index], O_RDONLY, 0777);
			index++;
		}
	}
	if (current->less_than && !ft_strcmp(current->less_than, "<<"))
		file = do_heredocs(current);
	if (is_builtin(current->command))
	{
		close(file);
		file = 0;
	}
	return (file);
}

void	open_files(t_commands *current, int **fd, int (*next_fd)[2])
{
	if (current->greater_than)
		(*next_fd)[1] = do_greater_than(current);
	if (current->less_than)
		(*next_fd)[0] = -1;
	// (*files)[0] = -1;
	// (*files)[0] = do_less_than(current);
}
// O_TRUNC - para substituir ||| O_APPEND -- para concatenar
