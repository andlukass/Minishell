/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 18:47:57 by user              #+#    #+#             */
/*   Updated: 2023/12/25 12:57:55 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	executor_router(char **command)
{
	if (!ft_strcmp(command[0], "exit"))
		ft_exit(command);
	else if (!ft_strcmp(command[0], "pwd"))
		ft_pwd(command);
	else if (!ft_strcmp(command[0], "echo"))
		ft_echo(command);
	else if (!ft_strcmp(command[0], "env"))
		ft_env(command);
	else if (!ft_strcmp(command[0], "export"))
		ft_export(command);
	else if (!ft_strcmp(command[0], "unset"))
		ft_unset(command);
	else if (!ft_strcmp(command[0], "cd"))
		ft_cd(command);
	else
		execvp(command[0], command);
}

static int is_multable_builtin(char **command)
{
	if (!ft_strcmp(command[0], "exit"))
		return (1);
	else if (!ft_strcmp(command[0], "export"))
		return (1);
	else if (!ft_strcmp(command[0], "unset"))
		return (1);
	else if (!ft_strcmp(command[0], "cd"))
		return (1);
	else
		return (0);
}

void	executor(t_commands **commands, int *fd)
{
	int next_fd[2]; // trocar o stdout ou in para o arquivo ou proximo comando
	int file; // arquivo para possivel redirect
	int pid; // id do fork
	t_commands	*current;

	current = *commands;

	// return;


	if(current->is_pipe) { // se tem | abre o pipe
		if (pipe(next_fd) < 0) // cria o next_fd
			return ;
	}
	file = open_files(current, &next_fd); // se tiver redirect vai trocar o fd
	if (is_multable_builtin(current->command) && get_data()->number_of_commands == 1)
	{
		if (file)
			dup2(file, STDOUT_FILENO);
		executor_router(current->command);
		if (file) {
			dup2(STDOUT_FILENO, file);
			close(file);
		}
		return ;
	}
	pid = fork();
	if (pid < 0)
		return;
	if (pid == 0) {//child process
		if(current->is_pipe || file) // se tem redirect ou pipe |
		{
			dup2(next_fd[1], STDOUT_FILENO); // cancelar o proprio stdout e escrever para o proximo commando (next_fd)
			close(next_fd[0]);
			close(next_fd[1]); // close next_fd
		}

		if (fd) // se recebeu algum fd
		{
			dup2(fd[0], STDIN_FILENO); // cancelar o proprio in e receber o do comando anterior (fd recebido)
			close(fd[0]);
			close(fd[1]); // close fd recebido
		}
		executor_router(current->command);
	}
	if (fd) {
		close(fd[0]);
		close(fd[1]);
	}
	waitpid(pid, NULL, 0);
	if (file)
		close(file);
	if (current->is_pipe) {// se tem pipe
		current = current->next;
		executor(&current, next_fd);// parent chama executor novamente com o proximo nodo e passando o next_fd
	}
}
