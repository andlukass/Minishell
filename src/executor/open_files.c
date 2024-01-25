/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 12:37:06 by user              #+#    #+#             */
/*   Updated: 2024/01/25 17:26:54 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_heredoc_input(t_commands *current, int index)
{
	char	*text;
	char	*input;

	text = NULL;
	while (1)
	{
		input = readline("> ");
		if (get_data()->quit)
			break ;
		if (input == NULL)
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
	return (text);
}

static void	create_temp_file(t_commands *current, t_exec *exec, int index)
{
	char	*text;
	int		fd;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler_heredoc);
	fd = open(".temp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	text = get_heredoc_input(current, index);
	expander_heredoc(&text);
	write(fd, text, ft_strlen(text));
	close(fd);
	free(text);
	if (get_data()->quit)
		exit_executor(exec, 1);
	exit_executor(exec, 0);
}

static int	do_heredocs(t_commands *current, t_exec *exec)
{
	int		temp_file;
	int		pid;
	int		index;

	index = 0;
	temp_file = -1;
	while (current->heredocs && current->heredocs[index] && !get_data()->quit)
	{
		pid = fork();
		if (pid == 0)
			create_temp_file(current, exec, index);
		waitpid(pid, &get_data()->quit, 0);
		index++;
	}
	if (!get_data()->quit)
		temp_file = open(".temp.txt", O_RDONLY, 0777);
	return (temp_file);
}

int	do_less_than(t_commands *current, t_exec *exec)
{
	int	index;
	int	red_fd;
	int	heredoc_fd;

	index = -1;
	red_fd = -1;
	if (!current->less_than)
		return (-1);
	heredoc_fd = do_heredocs(current, exec);
	if (get_data()->quit)
		return (-1);
	while (current->lt_files && current->lt_files[++index] && red_fd != -2)
	{
		close_fd(red_fd);
		red_fd = open(current->lt_files[index], O_RDONLY, 0777);
		if (red_fd == -1)
			red_fd = -2;
	}
	if (red_fd == -2)
		printf("%s: no such file or directory\n", current->lt_files[index - 1]);
	if (!ft_strcmp(current->less_than, "<<") && red_fd != -2)
		return (close_fd(red_fd), heredoc_fd);
	return (close_fd(heredoc_fd), red_fd);
}

int	do_greater_than(t_commands *current)
{
	int		index;
	int		fd;
	int		flag;

	if (!current->greater_than)
		return (-1);
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
