/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 18:54:08 by llopes-d          #+#    #+#             */
/*   Updated: 2023/12/21 19:03:50 by user             ###   ########.fr       */
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
		if (*data->input)
		{
			handle_input();//parser
			if (!strcmp("exit", get_data()->commands->command[0]) && \
				!get_data()->commands->next)
				ft_exit(get_data()->commands->command);
			//expander
			executor(&get_data()->commands, NULL);
			get_data()->commands = NULL;
			add_history(data->input);
		}
	}
	return (0);
}

// execve use
	// char *args[] = {
	// 	ft_strjoin(data->path, "ping", NO_FREE),
	// 	"-c",
	// 	"2",
	// 	(void *)0
	// };
	// printf("%s\n", ft_strjoin(data->path, "ping", NO_FREE));
	// execve(ft_strjoin(data->path, "ping", NO_FREE), args, env);