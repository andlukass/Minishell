/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 18:47:57 by user              #+#    #+#             */
/*   Updated: 2023/12/21 19:09:47 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void executor_router(char **command)
{
	if (command == (void *)0 || \
			!strcmp(command[0], "exit"))
		ft_exit(command);
	else if (!strcmp(command[0], "pwd"))
		ft_pwd(command);
	else if (!strcmp(command[0], "echo"))
		ft_echo(command);
	else if (!strcmp(command[0], "env"))
		ft_env(command);
	else if (!strcmp(command[0], "export"))
		ft_export(command);
	else if (!strcmp(command[0], "unset"))
		ft_unset(command);
	else if (!strcmp(command[0], "cd"))
		ft_cd(command);
	else
		execvp(command[0], command);
}

void executor(t_commands **commands, int *fd)
{
	// declarar tudo que seja possivel de ser utilizado em uma execucao
	int next_fd[2]; // trocar o stdout ou in para o arquivo ou proximo comando
	int file; // arquivo para possivel redirect
	int pid; // id do fork
	t_commands	*current;

	current = *commands;

	// printf("command: %s, is_pipe: %d\n", current->command[0], current->is_pipe);
	// se tem redirect
	// file = open("teste.txt", O_WRONLY | O_CREAT, 0777);

	// se tem redirect ou pipe |
	if(current->is_pipe) { // falta verificar se tem redirect
		if (pipe(next_fd) < 0) return ; // cria o next_fd
	}

	pid = fork();
	if (pid < 0) return;
	if (pid == 0) {
		// se tem redirect ou pipe |
		if(current->is_pipe)
		{
			dup2(next_fd[1], STDOUT_FILENO); // cancelar o proprio stdout e escrever para o proximo commando (next_fd)
			close(next_fd[0]);close(next_fd[1]); // close next_fd
		}

		// se recebeu algum fd
		if (fd)
		{
			dup2(fd[0], STDIN_FILENO); // cancelar o proprio in e receber o do comando anterior (fd recebido)
			close(fd[0]);close(fd[1]); // close fd recebido
		}
		executor_router(current->command);
	}

	if (fd) {
		close(fd[0]);close(fd[1]);
	}

	// se tem redirect 
	// close next_fd

	// se tem pipe
	// chamar executor novamente com o proximo nodo e passando o next_fd
	if (current->is_pipe) {
		current = current->next;
		executor(&current, next_fd);
	}
	waitpid(pid, NULL, 0);
}