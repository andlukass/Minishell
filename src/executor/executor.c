/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 18:47:57 by user              #+#    #+#             */
/*   Updated: 2023/12/25 15:48:01 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	close_fds(int *fd, int file)
{
	if (fd)
	{
		close(fd[0]);
		close(fd[1]);
	}
	if (file)
		close(file);
}

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

static int	is_multable_builtin(char **command, int file)
{
	if (!get_data()->number_of_commands == 1)
		return (0);
	if (!ft_strcmp(command[0], "exit") || !ft_strcmp(command[0], "export") || \
		!ft_strcmp(command[0], "unset") || !ft_strcmp(command[0], "cd"))
	{
		if (file)
			dup2(file, STDOUT_FILENO);
		executor_router(command);
		if (file)
		{
			dup2(STDOUT_FILENO, file);
			close(file);
		}
		return (1);
	}
	else
		return (0);
}

static void	child_routine(t_commands *current, int file, int *next_fd, int *fd)
{
	if (current->is_pipe || file)
	{
		dup2(next_fd[1], STDOUT_FILENO);
		close_fds(next_fd, 0);
	}
	if (fd)
	{
		dup2(fd[0], STDIN_FILENO);
		close_fds(fd, 0);
	}
	executor_router(current->command);
}
/*
 verifica se tem pipe ou se foi criado um arquivo por
 meio de um redirect, e troca o STDOUT pelo arquivo 
 ou pelo pipe.

 verifica se recebeu um fd, o que significa que terá 
 de ignorar o STDIN e escutar o o que vem do fd
*/

void	executor(t_commands **commands, int *fd)
{
	t_commands	*current;
	int			next_fd[2];
	int			file;
	int			pid;

	current = *commands;
	if (current->is_pipe)
		if (pipe(next_fd) < 0)
			return ;
	file = open_files(current, &next_fd);
	if (is_multable_builtin(current->command, file))
		return ;
	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
		child_routine(current, file, next_fd, fd);
	close_fds(fd, file);
	waitpid(pid, NULL, 0);
	if (current->is_pipe)
	{
		current = current->next;
		executor(&current, next_fd);
	}
}
/*
 OBS: ainda falta lidar com os redirects '<'
 (que ignoram o stdin que receberiam, recebendo
 apenas o que foi passado pelo redirect '<')

 se o comando possuir pipe, criamos o pipe de comunicação

 se o comando possuir redirects criamos os arquivos 
 necessarios e trocamos o STDOUT do next_fd.

 são executador comandos especiais que nao podem 
 passar por fork e damos return

 cria o fork para ser chamado o execve, trocando 
 os STDIN e OUT com base em ter pipes ou redirects

 encerra os fds e aguarda o fork terminar a execucão

 ao final de cada execução, verifica se o comando
 tem pipe, caso seja verdadeiro, é chamanda a funcao
 executor de forma recursiva com o proximo nodo e o 
 array de fds contendo qual será o STDIN do proximo comando.
*/
