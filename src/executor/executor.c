/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 18:47:57 by user              #+#    #+#             */
/*   Updated: 2023/12/27 18:15:50 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	close_fds(int *fd, int *files)
{
	if (fd)
	{
		close(fd[0]);
		close(fd[1]);
	}
	if (files && files[0])
		close(files[0]);
	if (files && files[1])
		close(files[1]);
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

static int	is_multable_builtin(char **command, int *files)
{
	if (!get_data()->number_of_commands == 1)
		return (0);
	if (!ft_strcmp(command[0], "exit") || !ft_strcmp(command[0], "export") || \
		!ft_strcmp(command[0], "unset") || !ft_strcmp(command[0], "cd"))
	{
		if (files[1])
			dup2(files[1], STDOUT_FILENO);
		executor_router(command);
		if (files[1])
		{
			dup2(STDOUT_FILENO, files[1]);
			close(files[1]);
		}
		if (files[0])
			close(files[0]);
		return (1);
	}
	else
		return (0);
}

static void	child_routine(t_commands *current, int *files, int *next_fd, int *fd)
{
	if (current->is_pipe || files[1])
	{
		dup2(next_fd[1], STDOUT_FILENO);
		close_fds(next_fd, 0);
	}
	if (fd || files[0])
	{
		if (files[0])
			dup2(files[0], STDIN_FILENO);
		else
			dup2(fd[0], STDIN_FILENO);
		close_fds(fd, files);
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
	int			files[2];
	int			pid;
	
	// return;
	current = *commands;
	if (current->is_pipe)
		if (pipe(next_fd) < 0)
			return ;
	open_files(current, &next_fd, &files);
	if (is_multable_builtin(current->command, files))
		return ;
	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
		child_routine(current, files, next_fd, fd);
	close_fds(fd, files);
	if (current->is_pipe)
	{
		current = current->next;
		executor(&current, next_fd);
	}
	else
		waitpid(pid, NULL, 0);
}
/*
 OBS: ainda falta lidar com os redirects '<'
 (que ignoram o stdin que receberiam, recebendo
 apenas o que foi passado pelo redirect '<')

 se o comando possuir pipe, criamos o pipe de comunicação

 se o comando possuir redirects criamos os arquivos 
 necessarios e trocamos o STDOUT do next_fd.

 são executados comandos especiais que nao podem 
 passar por fork e damos return

 cria o fork para ser chamado o execve, trocando 
 os STDIN e OUT com base em ter pipes ou redirects

 encerra os fds e aguarda o fork terminar a execucão

 ao final de cada execução, verifica se o comando
 tem pipe, caso seja verdadeiro, é chamanda a funcao
 executor de forma recursiva com o proximo nodo e o 
 array de fds contendo qual será o STDIN do proximo comando.
*/
