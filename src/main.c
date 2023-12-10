/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llopes-d <llopes-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 18:54:08 by llopes-d          #+#    #+#             */
/*   Updated: 2023/12/10 18:58:21 by llopes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief	Capture CTRL C command and give the prompt back
 */
void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	get_input_array(void)
{
	get_data()->input_array = ft_split(get_data()->input, ' ');
}

void	handle_input(void)
{
	get_input_array();
	if (get_data()->input == NULL || \
			!strcmp(get_data()->input_array[0], "exit"))
		ft_exit();
	else if (!strcmp(get_data()->input_array[0], "pwd"))
		ft_pwd();
	else if (!strcmp(get_data()->input_array[0], "echo"))
		ft_echo();
	else if (!strcmp(get_data()->input_array[0], "env"))
		ft_env();
	else if (!strcmp(get_data()->input_array[0], "export"))
		ft_export();
	else if (!strcmp(get_data()->input_array[0], "unset"))
		ft_unset();
	else if (!strcmp(get_data()->input_array[0], "ls"))
		ft_ls();
	else if (!strcmp(get_data()->input_array[0], "cd"))
		ft_cd();
	free_double_array(get_data()->input_array);
}

int	main(int argc, char *argv[], char *env[])
{
	t_data	*data;

	(void)argv;
	(void)env;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler);
	if (argc != 1)
		return (write(1, "too many arguments", 1));
	data = get_data();
	get_env(env);
	get_username();
	while (GLOBAL_WARMING_DONT_EXIST)
	{
		get_prompt();
		data->input = readline(data->prompt);
		free(data->prompt);
		handle_input();
		add_history(data->input);
	}
	return (0);
}

// execve use
	// char *args[] = {
	// 	ft_strjoin(data->path, "ping", NO_FREE),
	// 	"-c",
	// 	"2",
	// 	NULL
	// };
	// printf("%s\n", ft_strjoin(data->path, "ping", NO_FREE));
	// execve(ft_strjoin(data->path, "ping", NO_FREE), args, env);